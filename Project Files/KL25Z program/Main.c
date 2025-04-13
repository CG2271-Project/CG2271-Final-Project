#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "MKL25Z4.h"  // Device header for MKL25Z4
#include "motors.h"
#include "UART.h"
#include "LED.h"
#include "Buzzer.h"
		
		


osSemaphoreId_t brainSemaphore, moveSemaphore, blinkSemaphore, musicSemaphore;
volatile double isMoving = 0.0;

const osThreadAttr_t priorityAbNormal = {
  .priority = osPriorityAboveNormal
};
const osThreadAttr_t priorityHigh = {
  .priority = osPriorityHigh
};
const osThreadAttr_t priorityMax = {
  .priority = osPriorityRealtime
};

void motor_thread (void *argument) {
  for (;;) {
    osSemaphoreAcquire(moveSemaphore, osWaitForever);
    speed(x_offset,y_offset, crab);//in motors.c
		isMoving = y_offset != 0;
		if(isMoving != 0) {
			osSemaphoreRelease(blinkSemaphore);
		} else {
			osSemaphoreRelease(blinkSemaphore);
		}
    x_offset = 0;
    y_offset = 0;
  }
}  

void brain_thread (void *argument) {
  for (;;) {
    osSemaphoreAcquire(brainSemaphore, osWaitForever);
    osSemaphoreRelease(moveSemaphore);
  }
}

/*Add new one */
void led_thread (void *argument) {
  for (;;) {
			osSemaphoreAcquire(blinkSemaphore, osWaitForever);
			if(isMoving > 0){
				if (green_led_state == 0){
				offGreen();
				}
				led_green_thread(green_led_state);
				green_led_state++;
				if(green_led_state % 2 == 1){
				red_led_state++;
				osDelay(50);
				}
				if (green_led_state == 15){
					green_led_state = 0;
				}
				if (red_led_state == 10){
					ledControl(red_led_1, led_on);
				}else if (red_led_state == 20 || red_led_state == 0){
					ledControl(red_led_1, led_off);
					red_led_state = 0;
				}
			}else {
				green_led_state = 0;
				red_led_state = 0;
				onRGB();
			}
			osSemaphoreRelease(blinkSemaphore);
  }
}

void sound_thread (void *argument) {
	for (;;) {
		if (!celebrate) {
			    for (int i = 0; i < melodySize && !celebrate ; i++) {
				osSemaphoreAcquire(musicSemaphore, osWaitForever);
        playNote(melody[i], noteDurations[i], noteVolume[i]);
				osSemaphoreRelease(musicSemaphore);
				osDelay(noteDurations[i] * 1.45);
			}
		}
		else {
				for (int i = 0; i < endMelodySize && celebrate; i++) {
					osSemaphoreAcquire(musicSemaphore, osWaitForever);
					playNote(endMelody[i], endNoteDurations[i], endNoteVolume[i]);
					osSemaphoreRelease(musicSemaphore);
					osDelay(noteDurations[i] * 1.45);
				}

			} 
	}
}


int main(void) {
			SystemCoreClockUpdate();
		initBuzzer(); //Added newer
    initPWM();
    onRGB(); //Added new
    InitGPIO(); //Added new
    initUART2(BAUD_RATE);
    osKernelInitialize();
	
		musicSemaphore = osSemaphoreNew(1,1,NULL); //must not release this thread
    brainSemaphore = osSemaphoreNew(1,0,NULL);
    moveSemaphore = osSemaphoreNew(1,0,NULL);
	  blinkSemaphore = osSemaphoreNew(1,0,NULL);
  
    osThreadNew(brain_thread, NULL, &priorityMax); // for the controller signals to come
    osThreadNew(sound_thread, NULL, &priorityHigh);
    osThreadNew(motor_thread, NULL, &priorityAbNormal);
    osThreadNew(led_thread, NULL, NULL);
  
    osKernelStart();
    for (;;){}
}
