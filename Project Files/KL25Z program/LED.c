#include "LED.h"
#include "cmsis_os2.h"
unsigned int counter = 0;
int red_led_state = 0;
int green_led_state = 0;

/* GPIO Initialization Function */
void InitGPIO(void)
{
 SIM->SCGC5 |= ((SIM_SCGC5_PORTC_MASK));
 
 // Configure MUX settings to make all 3 pins GPIO
 
 PORTC->PCR[GREEN_LED_1] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_1] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_2] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_2] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_3] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_3] |= PORT_PCR_MUX(1);
	
 PORTC->PCR[GREEN_LED_4] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_4] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_5] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_5] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_6] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_6] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_7] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_7] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[GREEN_LED_8] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[GREEN_LED_8] |= PORT_PCR_MUX(1);
 
 PORTC->PCR[RED_LED_1] &= ~PORT_PCR_MUX_MASK;
 PORTC->PCR[RED_LED_1] |= PORT_PCR_MUX(1);
 
 // Set Data Direction Registers for PortB and PortD
 PTC->PDDR |= (MASK(GREEN_LED_1) | MASK(GREEN_LED_2) | 
							 MASK(GREEN_LED_3) | MASK(GREEN_LED_4) | MASK(GREEN_LED_5) |
							 MASK(GREEN_LED_6) | MASK(GREEN_LED_7) | MASK(GREEN_LED_8) |
							 MASK(RED_LED_1));
}

/* Switch OFF the RGB LED */
void onRGB(void)
{
 PTC->PCOR = (MASK(GREEN_LED_1) | MASK(GREEN_LED_2) | 
							 MASK(GREEN_LED_3) | MASK(GREEN_LED_4) | MASK(GREEN_LED_5) |
							 MASK(GREEN_LED_6) | MASK(GREEN_LED_7) | MASK(GREEN_LED_8));
ledControl(red_led_1, led_on);
 osDelay(250);
ledControl(red_led_1, led_off);
	osDelay(250);
}

void offGreen(void)
{
 PTC->PSOR = (MASK(GREEN_LED_1) | MASK(GREEN_LED_2) | 
							 MASK(GREEN_LED_3) | MASK(GREEN_LED_4) | MASK(GREEN_LED_5) |
							 MASK(GREEN_LED_6) | MASK(GREEN_LED_7) | MASK(GREEN_LED_8));
}

/* Control the behaviour of the RGB LED  */
void ledControl(led_colors_t color, led_state_t state) {
    switch (color) {
        case green_led_1:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_1);
            } else {
                PTC->PSOR = MASK(GREEN_LED_1);
            }
            break;
            
        case green_led_2:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_2);
            } else {
                PTC->PSOR = MASK(GREEN_LED_2);
            }
            break;
            
        case green_led_3:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_3);
            } else {
                PTC->PSOR = MASK(GREEN_LED_3);
            }
            break;
						
				case green_led_4:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_4);
            } else {
                PTC->PSOR = MASK(GREEN_LED_4);
            }
            break;
				case green_led_5:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_5);
            } else {
                PTC->PSOR = MASK(GREEN_LED_5);
            }
            break;
            
        case green_led_6:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_6);
            } else {
                PTC->PSOR = MASK(GREEN_LED_6);
            }
            break;
            
        case green_led_7:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_7);
            } else {
                PTC->PSOR = MASK(GREEN_LED_7);
            }
            break;
						
				case green_led_8:
            if (state == led_on) {
                PTC->PCOR = MASK(GREEN_LED_8);
            } else {
                PTC->PSOR = MASK(GREEN_LED_8);
            }
            break;
						
				case red_led_1:
            if (state == led_on) {
                PTC->PCOR = MASK(RED_LED_1);
            } else {
                PTC->PSOR = MASK(RED_LED_1);
            }
            break;
            
        default:
            // Optional: Handle error for invalid LED color
            break;
    }
}

/* Delay Function 

static void delay(volatile uint32_t nof) {
  while(nof!=0) {
    __asm("NOP");
    nof--;
  }
}
*/
 
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void led_green_thread (int led_state) {
switch (led_state) {
	case 0:
		ledControl(green_led_1, led_on);
		break;
	case 1:
		ledControl(green_led_1, led_off);
		break;
	case 2:
		ledControl(green_led_2, led_on);
		break;
	case 3:
		ledControl(green_led_2, led_off);
		break;
	case 4:
		ledControl(green_led_3, led_on);
		break;
	case 5:
		ledControl(green_led_3, led_off);
		break;
	case 6:
		ledControl(green_led_4, led_on);
		break;
	case 7:
		ledControl(green_led_4, led_off);
		break;
	case 8:
		ledControl(green_led_5, led_on);
		break;
	case 9:
		ledControl(green_led_5, led_off);
		break;
	case 10:
		ledControl(green_led_6, led_on);
		break;
	case 11:
		ledControl(green_led_6, led_off);
		break;
	case 12:
		ledControl(green_led_7, led_on);
		break;
	case 13:
		ledControl(green_led_7, led_off);
		break;
	case 14:
		ledControl(green_led_8, led_on);
		break;
	case 15:
		ledControl(green_led_8, led_off);
		break;
	default:
		break;
}

	}
 
