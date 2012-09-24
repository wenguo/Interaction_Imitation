/*
 * InterfaceTypes.h
 *
 *	All types and value declarations that are used across MSP and Blackfin.
 * 
 *      Author: schwarzer
 */
 
#ifndef INTERFACETYPES_H_
#define INTERFACETYPES_H_

#include <stdint.h>

// Message ids used from the Blackfin to the MSP
typedef enum Commands
{
	CMD_MOTOR 				= 0x00,
	CMD_HINGE				= 0x01,
	CMD_DOCKING				= 0x02,
	CMD_HINGE_ANGLE			= 0x03,
	CMD_RGB_LED 			= 0x10,
	CMD_POWER_CTRL			= 0x14,
	CMD_RGBSENSE_CALIBRATE	= 0x20,
	CMD_RGBSENSE_CAPS		= 0x21,
	CMD_RGBSENSE_INT_RED	= 0x22,		// CMD_RGBSENSE_INT_RED + RGBSRED
	CMD_RGBSENSE_INT_GREEN	= 0x23,		// CMD_RGBSENSE_INT_RED + RGBSGREEN
	CMD_RGBSENSE_INT_BLUE	= 0x24,		// CMD_RGBSENSE_INT_RED + RGBSBLUE
	CMD_RGBSENSE_INT_CLEAR	= 0x25,		// CMD_RGBSENSE_INT_RED + RGBSCLEAR
	CMD_RGBSENSE_CONF		= 0x26,
	CMD_PRINT				= 0x31,
	CMD_REMOTE_PROTOCOL		= 0x40,
	CMD_DOCKING_SWITCH		= 0x50,
	CMD_IR_LED				= 0x60,
	CMD_IR_COMM				= 0x62,
	CMD_PRINT_ENABLE		= 0x61,
	CMD_IDENTIFY			= 0xff,
} Commands;

// Message ids used from the MSP to the Blackfin
typedef enum Data
{
	DATA_INFRARED			= 0x08,
	DATA_ACCELEROMETER		= 0x10,
	DATA_POWER				= 0x14,
	DATA_ESHARINGISENSE		= 0x15,
	DATA_POWERBUSCURRENT	= 0x16,
	DATA_RGB				= 0x20,
	DATA_PRINT				= 0x30,
	DATA_REMOTECONTROL		= 0x40,
	DATA_IR_COMM			= 0x50,
	DATA_AMBIENTLIGHT		= 0x80,
	DATA_DSCREW_ISENSE		= 0x84,
	DATA_DSCREW_REVOLUTION	= 0x88,
	DATA_ID					= 0xfc

} Sensors;

typedef struct acceleration
{
	int16_t x;
	int16_t y;
	int16_t z;
} acceleration_t;

typedef struct rgb
{
	uint16_t red;
	uint16_t green;
	uint16_t blue;
	uint16_t clear;
} rgb_t;

typedef enum rc_protocol
{
	SIRC,
	PANASONIC,
} rc_protocol_t;

typedef struct IRSensorValues
{
	int16_t ambient;
	int16_t reflective;
	int16_t proximity;
	int16_t docking;
} IRSensorValues;

typedef struct IRValues
{
	uint8_t nb_sensors;
	IRSensorValues sensor[2];
} IRValues;

typedef enum IRLEDMode 
{
        IRLEDOFF = 0,           // LED off.
        IRLEDREFLECTIVE,        // Use LED to detect obstacles by reflection,
                                                //  this is included in higher modes.
        IRLEDPROXIMITY,         // Pulse LEDs so this robot can be detected.
        IRLEDDOCKING            // Pulse LEDs differently as docking beacons.
} IRLEDMode;

#define LED_RED 	0b00000001
#define LED_GREEN 	0b00000100
#define LED_BLUE 	0b00010000
#define LED_OFF 	0

#define IRLED0	0x1
#define IRLED1	0x2
#define IRLED2	0x4
#define IRPULSE0	0x1
#define IRPULSE1	0x2

// please keep synchronized with the battery pack
typedef struct __attribute__((packed)) BatteryPackData {
	uint16_t BPStatus;
	int16_t voltage;
	int16_t current;
	uint16_t rmCapacity;
	int16_t time;
} BatteryPackData;


typedef enum
{
	PM_SW1,
	PM_SW2,
	PM_ESHARING,
	PM_HIGHVOLTAGE,
	PM_CHARGER
} PowerFunction;

#endif
