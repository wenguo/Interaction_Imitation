#ifndef CRC16_HH
#define CRC16_HH

typedef unsigned int uint16_t;
typedef unsigned char uint8_t;

#define CRC16_INIT 0xFFFF

uint16_t crc16(const uint8_t *buffer, uint8_t len, uint16_t crc);

#endif 
