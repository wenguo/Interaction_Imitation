/*
 *      Created on: 01/2012
 *          Author: Wenguo Liu (wenguo.liu@brl.ac.uk)
 *
*/
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include "ipc.hh"

namespace IPC{

int IPC::index = 0;
IPC::IPC(int _ipc_txbuffer_size, int _ipc_lolbuffer_size, int _ipc_block_size)
{
    callback = NULL;
    sockfd = -1;
    clientsockfd = -1;
    port = 10000;
    host = NULL;
    server = true;
    user_data = NULL;
    id = index;
    index++;

    ipc_txbuffer_size = _ipc_txbuffer_size;
    ipc_lolbuffer_size = _ipc_lolbuffer_size;
    ipc_block_size = _ipc_block_size;
    
    txbuffer = new uint8_t[ipc_txbuffer_size];
    BQInit(&txq, txbuffer, ipc_txbuffer_size);
}

bool IPC::Start(const char* h, int p, bool s)
{
    port = p;
    server = s;
    if(h)
        host=strdup(h);
    else
        host=NULL;

    mutex_txq=PTHREAD_MUTEX_INITIALIZER; 
   // pthread_mutex_init(&mutex_txq,NULL);
    //create monitoring thread
    pthread_create(&monitor_thread, 0, Monitoring, this);
    return true;
}

bool IPC::Exit()
{
    if(server)
	close(sockfd);
    else
        close(clientsockfd);
}

void * IPC::Monitoring(void * ptr)
{
    IPC* ipc = (IPC*)ptr;
    printf("%d start monitroing\n", ipc->id);

    bool ret=false;
    if(ipc->server)
        ret = ipc->StartServer(ipc->port);
    else
        ret = ipc->ConnectToServer(ipc->host, ipc->port);

    if(ret)
    {
        pthread_create(&ipc->receiving_thread, 0, Receiving, ptr);
        pthread_create(&ipc->transmiting_thread, 0, Transmiting, ptr);
    }

    return NULL;
}

void * IPC::Receiving(void * ptr)
{
    IPC* ipc = (IPC*)ptr;

    printf("create receiving thread\n");

    //main loop, keep reading
    uint8_t rx_buffer[ipc->ipc_block_size];

    lolmsgParseInit(&ipc->parseContext, new uint8_t[ipc->ipc_lolbuffer_size], ipc->ipc_lolbuffer_size);

    while(1)
    {
        //reading
        memset(rx_buffer, 0, ipc->ipc_block_size);
        int received = read(ipc->clientsockfd,rx_buffer, ipc->ipc_block_size);
        if (received <= 0) 
        {
            printf("ERROR read to socket : %d -- it seems connection lost\n", received);
            ipc->connected = false;
            break;
        }
        else
        {

            int parsed = 0;
            while (parsed < received)
            {
                parsed += lolmsgParse(&ipc->parseContext, rx_buffer + parsed, received - parsed);
                LolMessage* msg = lolmsgParseDone(&ipc->parseContext);
                if(msg!=NULL && ipc->callback)
                    ipc->callback(msg, ipc->user_data);
            }
        }
    }

    printf("Exit receiving thread\n");

    pthread_exit(NULL);
}

void * IPC::Transmiting(void *ptr)
{
    printf("create transmiting thread\n");
    IPC * ipc = (IPC*) ptr;
    uint8_t txBuf[ipc->ipc_block_size];

    while(1)
    {
        if(BQCount(&ipc->txq) > 0 )
        {
            pthread_mutex_lock(&ipc->mutex_txq);
            register int byteCount = BQPopBytes(&ipc->txq, txBuf, ipc->ipc_block_size);
            pthread_mutex_unlock(&ipc->mutex_txq);

            int n = write(ipc->clientsockfd, txBuf, byteCount);
            if(n<0)
                printf("write error %d\n", n);
        }

        //usleep(100000);
    }
    pthread_exit(NULL);
}

bool IPC::StartServer(int port)
{
    printf("%d Start Server @ port: %d\n", id, port);
    struct sockaddr_in serv_addr;

    bool binded = false;
    //start server
    while(!binded)
    {
        sockfd = socket(AF_INET, SOCK_STREAM,0);
        if(sockfd <0)
        {
            binded =false;
            continue;
        }

        memset((char*) &serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        {
            printf("ERROR on binding, try again in 1 second\n");
            binded = false;
            close(sockfd);
            usleep(1000000);
        }
        else
            binded  = true;
    }

    return ListenForConnection(sockfd);
}

bool IPC::ListenForConnection(int sockfd)
{
    if(sockfd<0)
        return false;

    printf("Listening on port %d\n", port);

    socklen_t clilen;
    //listening for connection
    listen(sockfd,5);

    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    clientsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    printf("accept\n");
    if (clientsockfd < 0) 
    {
        printf("ERROR on accept\n");
        return false;
    }
    else
        return true;

}

bool IPC::ConnectToServer(const char * host, int port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;
    server = gethostbyname(host);

    printf("Trying to connect to Server [%s:%d]\n", host, port);

    clientsockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsockfd < 0) 
    {
        printf("ERROR opening socket, exit monitor thread\n");
        return false;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(clientsockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        printf("ERROR connecting, exit monitor thread\n");
        return false;
    }
    printf("Success to connect to Server [%s:%d]\n", host, port);

    return true;
}

bool IPC::SendData(const uint8_t type, uint8_t *data, int data_size)
{
    printf("send data\n");
    LolMessage msg;
    lolmsgInit(&msg, 0, type, data, data_size);
    int len = lolmsgSerializedSize(&msg);
    uint8_t buf[len];
    lolmsgSerialize(&msg, buf);

    // pthread_mutex_lock(&mutex_txq);
    int write = BQSize(&txq) - BQCount(&txq);
    if (len < write)
        write = len;
    BQPushBytes(&txq, buf, write);       

    // pthread_mutex_unlock(&mutex_txq);
    return write == len;

}

}//end of namespace
