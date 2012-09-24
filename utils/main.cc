#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "lolmsg.h"
#include "bytequeue.h"

#define BUFFERSIZE 1024
#define PARSE_BUFFERSIZE 256
uint8_t buf[BUFFERSIZE];
ByteQueue bq;


LolParseContext parseContext;

int main(int argc, char **argv)
{
    BQInit(&bq, buf, BUFFERSIZE);
    uint8_t *lolbuffer = new uint8_t[PARSE_BUFFERSIZE];
    lolmsgParseInit(&parseContext, lolbuffer, PARSE_BUFFERSIZE);


    printf("size LolMessage --- %d\n", sizeof(LolMessage));
    printf("size uint8_t* --- %d\n", sizeof(uint8_t *));
    
    int size=10;
    uint8_t *data = new uint8_t[size];
    for(int i=0;i<size;i++) 
        data[i]=0x30 + i;
    
    LolMessage msg;
    lolmsgInit(&msg, 0x1, 0x2, data, 10);

    int size2 = lolmsgSerializedSize(&msg);
    uint8_t *outbytes = new uint8_t[size2];
    lolmsgSerialize(&msg, outbytes);

    printf("");
    for(int i=0;i<size2;i++)
        printf("%#x\t", outbytes[i]);
    printf("\n");

    int parsed=0,read=size2 -5;
    while (parsed < read)
    {
        printf("--- parsed %d --\n", parsed);
        parsed += lolmsgParse(&parseContext, outbytes + parsed, size2 - 5);
        printf("--- parsed %d --\n", parsed);
        parsed += lolmsgParse(&parseContext, outbytes + parsed, size2 - 5);
        printf("--- parsed %d --\n", parsed);
        LolMessage* msg = lolmsgParseDone(&parseContext);
        if(msg!=NULL)
        {
            LolMessage*tt=(LolMessage*)parseContext.buf;
            printf("length: %d %#x %d\n", msg->length, msg->data, sizeof(ParseState));
            for(int i=0;i<msg->length;i++)
                printf("%#x\n", msg->data[i]);
        }

    }    
    

    return 1;
}
