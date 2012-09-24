#ifndef SUPPORT_H
#define SUPPORT_H

#ifdef __cplusplus
extern "C" {
#endif

int get_switch();
int set_board_led(int led_no,int on);
int blink_board_led(int led_no,int delay_on, int delay_off);
int wait_btn_trigger(unsigned short code);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif
