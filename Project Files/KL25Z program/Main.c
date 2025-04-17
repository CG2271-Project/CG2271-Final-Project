#include "RTE_Components.h"
#include CMSIS_device_header   // Core device definitions for MKL25Z4
#include "cmsis_os2.h"        // CMSIS-RTOS2 API
#include "MKL25Z4.h"          // Device-specific header for KL25Z4
#include "motors.h"           // motor control functions
#include "UART.h"             // UART communication setup
#include "LED.h"              // RGB and LED control functions
#include "Buzzer.h"           // Buzzer and melody definitions

// Semaphores to synchronise the four threads
osSemaphoreId_t brainSemaphore, moveSemaphore, blinkSemaphore, musicSemaphore;

// Flag indicating whether the robot is currently moving
volatile double isMoving = 0.0;

// Thread attributes for prioritisation
const osThreadAttr_t priorityAbNormal = {
  .priority = osPriorityAboveNormal
};
const osThreadAttr_t priorityHigh = {
  .priority = osPriorityHigh
};
const osThreadAttr_t priorityMax = {
  .priority = osPriorityRealtime
};

/**
 * @brief    Thread that handles motor control.
 * @details  Waits for moveSemaphore, then calls `speed()` to drive motors
 *           based on global offsets; sets `isMoving` flag and signals LED thread.
 */
void motor_thread (void *argument) {
  for (;;) {
    osSemaphoreAcquire(moveSemaphore, osWaitForever);
    speed(x_offset, y_offset, crab);  // drive motors
    isMoving = (y_offset != 0);       // true if forward/backward motion
    // signal LED thread to update based on moving state
    osSemaphoreRelease(blinkSemaphore);
    // reset offsets for next command
    x_offset = 0;
    y_offset = 0;
  }
}

/**
 * @brief    “Brain” thread that triggers motion.
 * @details  Waits for an external event on brainSemaphore (e.g. UART input)
 *           then releases moveSemaphore to cause the robot to move.
 */
void brain_thread (void *argument) {
  for (;;) {
    osSemaphoreAcquire(brainSemaphore, osWaitForever);
    osSemaphoreRelease(moveSemaphore);
  }
}

/**
 * @brief    LED blinking thread.
 * @details  Toggles green and red LEDs in a pattern when moving,
 *           or turns on all RGB when stationary.
 */
void led_thread (void *argument) {
  for (;;) {
    osSemaphoreAcquire(blinkSemaphore, osWaitForever);
    if (isMoving) {
      // moving: cycle green LED, pulse red LED periodically
      if (green_led_state == 0) {
        offGreen();
      }
      led_green_thread(green_led_state);
      green_led_state++;
      if (green_led_state % 2 == 1) {
        red_led_state++;
        osDelay(50);  // short delay for red pulse timing
      }
      if (green_led_state == 15) {
        green_led_state = 0;
      }
      if (red_led_state == 10) {
        ledControl(red_led_1, led_on);
      } else if (red_led_state == 20 || red_led_state == 0) {
        ledControl(red_led_1, led_off);
        red_led_state = 0;
      }
    } else {
      // stationary: reset states and turn on full RGB
      green_led_state = 0;
      red_led_state = 0;
      onRGB();
    }
    osSemaphoreRelease(blinkSemaphore);
  }
}

/**
 * @brief    Sound thread to play melodies.
 * @details  Plays one melody when `celebrate` is false,
 *           and an end melody when `celebrate` becomes true.
 */
void sound_thread (void *argument) {
  for (;;) {
    if (!celebrate) {
      // play main melody
      for (int i = 0; i < melodySize && !celebrate; i++) {
        osSemaphoreAcquire(musicSemaphore, osWaitForever);
        playNote(melody[i], noteDurations[i], noteVolume[i]);
        osSemaphoreRelease(musicSemaphore);
        osDelay(noteDurations[i] * 1.45);
      }
    } else {
      // play celebration melody
      for (int i = 0; i < endMelodySize && celebrate; i++) {
        osSemaphoreAcquire(musicSemaphore, osWaitForever);
        playNote(endMelody[i], endNoteDurations[i], endNoteVolume[i]);
        osSemaphoreRelease(musicSemaphore);
        osDelay(endNoteDurations[i] * 1.45);
      }
    }
  }
}

int main(void) {
  SystemCoreClockUpdate();    // update core clock frequency
  initBuzzer();               // configure buzzer PWM
  initPWM();                  // configure general PWM for motors/LED
  onRGB();                    // turn on RGB LED initially
  InitGPIO();                 // configure I/O pins
  initUART2(BAUD_RATE);       // initialise UART2 for command input

  osKernelInitialize();       // prepare RTOS kernel

  // create semaphores (1 token max, initially brain has 0, move 0, blink 0)
  musicSemaphore = osSemaphoreNew(1, 1, NULL); 
  brainSemaphore = osSemaphoreNew(1, 0, NULL);
  moveSemaphore  = osSemaphoreNew(1, 0, NULL);
  blinkSemaphore = osSemaphoreNew(1, 0, NULL);

  // spawn the four threads with assigned priorities
  osThreadNew(brain_thread,  NULL, &priorityMax);
  osThreadNew(sound_thread,  NULL, &priorityHigh);
  osThreadNew(motor_thread,  NULL, &priorityAbNormal);
  osThreadNew(led_thread,    NULL, NULL);  // default priority

  osKernelStart();  // start thread scheduling

  // main thread does nothing; all work happens in the RTOS threads
  for (;;) { }
}
