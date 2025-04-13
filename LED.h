#ifndef LED_H
#define LED_H

#include "MKL25Z4.h"
#include "cmsis_os2.h"

#define GREEN_LED_1 3 // PortC Pin 3
#define GREEN_LED_2 4 // PortC Pin 4
#define GREEN_LED_3 5 // PortC Pin 5
#define GREEN_LED_4 6 // PortC Pin 6
#define GREEN_LED_5 10 // PortC Pin 10
#define GREEN_LED_6 11 // PortC Pin 11
#define GREEN_LED_7 12 // PortC Pin 12
#define GREEN_LED_8 13 // PortC Pin 13
#define RED_LED_1 16 // PortC Pin 16

#define MASK(x) (1 << (x))

extern int red_led_state;
extern int green_led_state;

/* Enum for LED colors */
typedef enum {
    green_led_1 = GREEN_LED_1,
    green_led_2 = GREEN_LED_2,
    green_led_3 = GREEN_LED_3,
		green_led_4 = GREEN_LED_4,
    green_led_5 = GREEN_LED_5,
    green_led_6 = GREEN_LED_6,
		green_led_7 = GREEN_LED_7,
    green_led_8 = GREEN_LED_8,
    red_led_1 = RED_LED_1,
} led_colors_t;

typedef enum {
    led_off = 0,
    led_on  = 1
} led_state_t;

/*
char led_mapping[9][2] = {{0, red_led}, {1, green_led}, {2, blue_led}};
*/

void onRGB(void);
void offGreen(void);
void ledControl(led_colors_t color, led_state_t state);
void led_green_thread (int led_state);
void InitGPIO(void);

#endif 
