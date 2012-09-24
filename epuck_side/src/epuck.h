#ifndef EPUCK_H_
#define EPUCK_H_

//#define BUFFSIZE 27  	



// the number of 16 bit words in the tx/rx packet
struct cmd_t{
	unsigned int set_motor:1;
	unsigned int set_led:1;
	unsigned int reset:1;
	unsigned int cal_ir:1;
	unsigned int cal_acc:1;
	unsigned int read_ir:1;
	unsigned int read_light:1;
	unsigned int read_mic:1;
	unsigned int read_acc:1;
	unsigned int play_sound:1;
	unsigned int blinking_led:1;
        unsigned int set_ir_pulse:1;
	unsigned int reseverd:4;
};
struct led_cmd_t{
	unsigned int led0:1;
	unsigned int led1:1;
	unsigned int led2:1;
	unsigned int led3:1;
	unsigned int led4:1;
	unsigned int led5:1;
	unsigned int led6:1;
	unsigned int led7:1;
	unsigned int bodyled:1;
	unsigned int frontled:1;
        unsigned int ir0:1;
        unsigned int ir1:1;
        unsigned int ir2:1;
        unsigned int ir3:1;
	unsigned int reserved:2;
};


//note that the SPI works in full dulex mode, so better to keep the txbuf_t and rxbuf_t in the same size
struct rxbuf_t
{
	struct cmd_t cmd;		//first two bytes for commands
	int left_motor;	//speed of left motor
	int right_motor;	//speed of right motor
	struct led_cmd_t led_cmd;	//command for leds
	int led_cycle;
	int sound_num;
	int reserved[20];	//reserved, in order to makde the txbuf_t and rxbuf_t in the same size, now 26 16bits words
	unsigned int crc;
};


struct txbuf_t
{
	int ir[8];		// IR range values
	int acc[3];		// accelerometer readings
	int mic[3];		// microphones
	int amb[8];		// IR range values
	int tacl;			// stepper motor "clicks" l&r
	int tacr;
	int batt;		// battery
	unsigned int crc;
	int dummy;		//leave it empty
};

#endif

