#ifndef BUZZER_H
#define BUZZER_H
#include "MKL25Z4.h"  // Device header for MKL25Z4
#include "cmsis_os2.h"

// Pin Definitions
#define RED_LED      18      // PortB Pin 18
#define GREEN_LED    19      // PortB Pin 19
#define BLUE_LED     1       // PortD Pin 1
#define SW_POS       6       // Switch connected to PTD6
#define PTE29_Pin    29

#define NOTE_D4  294
#define NOTE_D3  146
#define NOTE_F3  174
#define NOTE_E3  165
#define NOTE_E4  330
#define NOTE_C3  131
#define NOTE_C4  262
#define NOTE_A2  110
#define NOTE_A3  220
#define NOTE_A4  440
#define NOTE_B2  123
#define NOTE_B3  247
#define NOTE_B4  494
#define NOTE_F4  349
#define NOTE_G3	 196
#define NOTE_G4	 392
#define NOTE_G5  784
#define NOTE_A3S 233
#define NOTE_A4S 466
#define NOTE_NULL  0
#define NOTE_C5  523

//Celebratory Tune
#define NOTE_GS3 208
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_DS5 622
#define NOTE_E3 165
#define NOTE_E4 330
#define NOTE_E5 659
#define NOTE_E6 1318
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_A5 880
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_C6 1046
#define NOTE_CS5 554
#define NOTE_CS6 1108
#define NOTE_D5 587
#define NOTE_D6 1174


extern osSemaphoreId_t musicSemaphore;

extern uint16_t melody[];
extern uint16_t noteDurations[];
extern float noteVolume[];
extern uint16_t endMelody[];
extern uint16_t endNoteDurations[];
extern float endNoteVolume[];
extern const size_t melodySize;
extern const size_t endMelodySize;

void initBuzzer(void);
void playNote(uint32_t freq, uint32_t duration, float volume);
void playMelody(void);

#endif


