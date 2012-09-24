#include <p30F6014A.h> 
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
//#include <uart.h>
#include <uart.h>

#include "./epfl/e_ad_conv.h"     // reads the A/D channels
#include "./epfl/e_acc.h"         // reads the 3 accelerometer channels (using e_ad_conv)
#include "./epfl/e_prox.h"        // reads the proximity sensors (using e_ad_conv)
#include "./epfl/e_micro.h"       // reads the 3 microphone volumes (using e_ad_conv)
#include "./epfl/e_epuck_ports.h"        // gives mnemonic names to pins, defines simple asm functions
#include "./epfl/e_init_port.h"          // initializes the port values and whether input or output
#include "./epfl/e_led.h"                // uses the LED's with interrupts, to allow blinking, etc.
#include "./epfl/e_motors.h"             // interrupt-driven motor routines (step every x millisecs, e.g.)
#include "./epfl/e_agenda.h"           // manages "agenda" (the interrupt routines)
#include "./epfl/e_batt.h"

#include "epuck.h"
#include "crc16.h"


struct rxbuf_t rx_buf;
struct txbuf_t tx_buf;

// used to keep track of steps on wheels.
int lm_steps;
int rm_steps;

static int timer_count = 10;
static int index = 0;
static int buffer_size = 0;

void count_down(){timer_count--;};  //using agenda as timers

void UpdateSensor();
void ProcessCommand();

void Init_SPI(void)
{
	// setup the SPI peripheral
	SPI2BUF = 0;//clear SPI2BUF
	SPI2STAT = 0;  // disable the SPI module (just in case)

	SPI2CON = 0;
	SPI2CONbits.MODE16 = 1;  //16bit mode on
	SPI2CONbits.CKE = 0;
	SPI2CONbits.CKP = 0;

	SPI2CONbits.SSEN = 0;
	SPI2CONbits.MSTEN = 0;
	SPI2CONbits.SMP = 0;
	SPI2STATbits.SPIROV = 0;
	SPI2STATbits.SPIEN = 1; // enable the SPI module

	//setup interrupt
	IPC6bits.SPI2IP = 6;//set priority level
	IFS1bits.SPI2IF = 0;//clear interrupt flag
	IEC1bits.SPI2IE = 1;//enable interrupts
}

void Init_UART(void)
{
	//We need to configure the UART. Uart 2, connected to linuxboard at 115200baud.
	ConfigIntUART2(UART_RX_INT_EN &
			UART_RX_INT_PR4 &
			UART_TX_INT_DIS &
			UART_TX_INT_PR4);

	OpenUART2(UART_EN &
			UART_IDLE_STOP &
			UART_DIS_WAKE &
			UART_DIS_LOOPBACK &
			UART_DIS_ABAUD &
			UART_NO_PAR_8BIT &
			UART_1STOPBIT,
			UART_INT_TX &
			UART_TX_PIN_NORMAL &
			UART_TX_ENABLE &
			UART_INT_RX_CHAR &
			UART_ADR_DETECT_DIS &
			UART_RX_OVERRUN_CLEAR,
			7); //115200 baud./OK.
}

int main(void)
{

	buffer_size = sizeof(tx_buf)/sizeof(int);

	e_init_port();                  // configure port pins

	Init_SPI();

	e_start_agendas_processing();   // start the motor interrupt service routines
	e_init_motors();

	e_init_ad_scan(ALL_ADC);
	e_acc_calibr();
	e_calibrate_ir();

	lm_steps = 0;
	rm_steps = 0;


	e_activate_agenda(UpdateSensor, 300);


	while (1){};


}


void UpdateSensor()
{
	int i;

	// IR
	for (i = 0;i < 8;i++)
		tx_buf.ir[i] = e_get_calibrated_prox(i);

	// Microphones
	for ( i = 0; i < 3; i++ )
		tx_buf.mic[i] = e_get_micro_average(i, FILTER_SIZE);

	// Ambient IR
	for (i = 0; i < 8; i++ )
		tx_buf.amb[i] =  e_get_prox_filtered(i);

	// Battery
	tx_buf.batt = e_read_batt();

	// Tachometer clicks
	tx_buf.tacl = lm_steps;
	tx_buf.tacr = rm_steps;
	// we will loose steps here, acceptable?
	lm_steps = rm_steps = 0;

	// Accelerometer
	tx_buf.acc[0] = e_read_acc_x();
	tx_buf.acc[1] = e_read_acc_y();
	tx_buf.acc[2] = e_read_acc_z();

	tx_buf.crc = crc16((unsigned char*)&tx_buf, sizeof(tx_buf) - 4, CRC16_INIT);
}

void ProcessCommand()
{
	int lspeed, rspeed;

	//check crc
	unsigned int checksum = crc16((unsigned int*)&rx_buf, sizeof(rx_buf) - 2, CRC16_INIT);
	if(checksum != rx_buf.crc)
	{
		BODY_LED = ~BODY_LED;
		index = 0; //so no need to reset dspic every time battery is changed
	}	
	//set motor speed
	if (rx_buf.cmd.set_motor)
	{
		lspeed = rx_buf.left_motor;
		rspeed = rx_buf.right_motor;

		if (lspeed > 800)
			lspeed = 800;
		if (lspeed < -800)
			lspeed = -800;
		if (rspeed > 800)
			rspeed = 800;
		if (rspeed < -800)
			rspeed = -800;

		e_set_speed_left(lspeed);
		e_set_speed_right(rspeed);

		//clear the flag so the speed will not be updated too frequently
		rx_buf.cmd.set_motor = 0;

	}

	if(rx_buf.cmd.reset)
	{
		index = 0;
		rx_buf.cmd.reset = 0;
		FRONT_LED = ~FRONT_LED;
	}

	// set leds
	if ( rx_buf.cmd.set_led )
	{
		// look up led state in packet
		e_set_led(0, rx_buf.led_cmd.led0);
		e_set_led(1, rx_buf.led_cmd.led1);
		e_set_led(2, rx_buf.led_cmd.led2);
		e_set_led(3, rx_buf.led_cmd.led3);
		e_set_led(4, rx_buf.led_cmd.led4);
		e_set_led(5, rx_buf.led_cmd.led5);
		e_set_led(6, rx_buf.led_cmd.led6);
		e_set_led(7, rx_buf.led_cmd.led7);
		e_set_body_led( rx_buf.led_cmd.bodyled );
		e_set_front_led( rx_buf.led_cmd.frontled ); 

		//clear the flag
		rx_buf.cmd.set_led = 0;
	}
        // set ir leds
        if ( rx_buf.cmd.set_ir_pulse )
        {
            e_set_ir_pulse_mask(0, rx_buf.led_cmd.ir0);
            e_set_ir_pulse_mask(1, rx_buf.led_cmd.ir1);
            e_set_ir_pulse_mask(2, rx_buf.led_cmd.ir2);
            e_set_ir_pulse_mask(3, rx_buf.led_cmd.ir3);
            rx_buf.cmd.set_ir_pulse = 0;
        }

	// check if we should be blinking
	if (rx_buf.cmd.blinking_led)
	{
		if ( rx_buf.led_cycle == 0 )
			e_stop_led_blinking();
		else
			e_start_led_blinking( rx_buf.led_cycle );

		rx_buf.cmd.blinking_led = 0;

	}


}

//known problem: linux side may recieved different data with error checksum, as write to buffer operation is suspended by other high priority interrupt routine
//SPI interrupt routine
void __attribute__((__interrupt__)) _SPI2Interrupt(void)
{
	_SPI2IF = 0;   // Reset interupt flag

	SPI2STATbits.SPIROV = 0;            // Clear the rx overflow flag
	((int*)&rx_buf)[index] = SPI2BUF;   //read the buffer
	SPI2BUF = ((int*) & tx_buf)[index]; //write the buffer
	
	index++;

	if (index >= buffer_size)
	{
		index = 0;
		ProcessCommand();
	}
}

void __attribute__ ((__interrupt__)) _U2TXInterrupt(void)
{
	//IFS0bits.U2TXIF = 0; //reset int flag.
}


