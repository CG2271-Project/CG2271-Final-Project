#include "MKL25Z4.h"  // Device header for MKL25Z4
#include "cmsis_os2.h"
#include "Buzzer.h"

// Pin Definitions
#define PTE29_Pin    29

uint16_t melody[] = {
    NOTE_D3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_D3, NOTE_C3, NOTE_C3, NOTE_A2, NOTE_B2,
    NOTE_D3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_D3, NOTE_C3, NOTE_C3, NOTE_F3, NOTE_G3,
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3S, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_D3, NOTE_E3,
    NOTE_G3, NOTE_G3, NOTE_A3, NOTE_A3S, NOTE_G3, NOTE_F3, NOTE_F3, NOTE_A3S, NOTE_C4,
    NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_A3S, NOTE_G3, NOTE_A3, 
    NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_A3S, NOTE_AS4
};

uint16_t noteDurations[] = {
    30, 30, 10, 10, 40, 40, 40, 40, 70,
    30, 30, 10, 10, 40, 40, 40, 40, 70,
    30, 30, 10, 10, 40, 40, 40, 40, 70,
    30, 30, 10, 10, 40, 40, 40, 40, 70,
    30, 30, 30, 10, 10, 10, 10, 10, 10, 10, 30, 30, 10, 10, 100, 30
};

float noteVolume[] = {
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0
};




/*
uint16_t endMelody[] = {
    NOTE_A4, NOTE_E4, NOTE_CS5, NOTE_GS3, NOTE_E4, NOTE_C5,
    NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D4, NOTE_DS4, NOTE_CS4,
    NOTE_G4, NOTE_E4, NOTE_E4, NOTE_DS4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_D4
};*/

/*
uint16_t endNoteDurations[] = {
    8, 32, 64, 64, 64, 8,
    32, 64, 32, 8, 64, 64, 64, 
    64, 32, 64, 64, 64,
    64, 64, 64
}; */

/*
uint16_t endNoteDurations[] = {
    8, 32, 32, 64, 64, 64, 64, 8, 32,  
    32, 64, 32, 64, 8, 32, 64, 64, 64, 
    64, 16, 32, 64, 64, 64, 64, 64, 64, 
    64, 16, 64, 64, 32, 0
}; */

/*uint16_t endMelody[] = {
    NOTE_A4, NOTE_NULL, NOTE_E4, NOTE_CS5, NOTE_GS3, NOTE_E4, NOTE_NULL, NOTE_C5, NOTE_NULL, 
    NOTE_E5, NOTE_D5, NOTE_C5, NOTE_NULL, NOTE_A4, NOTE_NULL, NOTE_D4, NOTE_DS4, NOTE_CS4,
    NOTE_G4, NOTE_NULL, NOTE_E4, NOTE_NULL, NOTE_E4, NOTE_DS4, NOTE_NULL, NOTE_D4, NOTE_NULL,
    NOTE_C4, NOTE_NULL, NOTE_C4, NOTE_D4, NOTE_NULL, NOTE_NULL
};  */


uint16_t endMelody[] = {
    NOTE_A5, NOTE_A5, NOTE_E5, NOTE_CS6, NOTE_GS4, NOTE_E5, NOTE_A5, NOTE_C6, NOTE_A5, 
    NOTE_E6, NOTE_D6, NOTE_C6, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_D5, NOTE_DS5, NOTE_CS5,
    NOTE_G5, NOTE_A5, NOTE_E5, NOTE_A5, NOTE_E5, NOTE_DS5, NOTE_A5, NOTE_D5, NOTE_A5,
    NOTE_C5, NOTE_A5, NOTE_C5, NOTE_D5, NOTE_A5, NOTE_A5
};  

/*
uint16_t endNoteDurations[] = {
80, 20, 20, 10, 10, 10, 10, 80, 20,
20, 10, 20, 10, 80, 20, 10, 10, 10,
10, 40, 20, 10, 10, 10, 10, 10, 10,
40, 10, 10, 20, 0
};
*/

uint16_t endNoteDurations[] = {
100, 25, 25, 13, 13, 13, 8, 100, 25, 
25, 13, 25, 8, 100, 25, 13, 13, 13, 
13, 50, 25, 8, 13, 13, 8, 13, 8, 
50, 13, 13, 25, 0, 10
};

float endNoteVolume[] = {
    0.5, 0, 0.5, 0.5, 0.5, 0.5, 0, 0.5, 0, 
    0.5, 0.5, 0.5, 0, 0.5, 0, 0.5, 0.5, 0.5, 
    0.5, 0, 0.5, 0, 0.5, 0.5, 0, 0.5, 0, 
    0.5, 0, 0.5, 0.5, 0, 0
}; 




//without gap
/*
uint16_t endMelody[] = {
    NOTE_A4, NOTE_E4, NOTE_CS5, NOTE_GS3, NOTE_E4, NOTE_C5,
    NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D4, NOTE_DS4, NOTE_CS4,
    NOTE_G4, NOTE_E4, NOTE_E4, NOTE_DS4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_D4
}; */

/*
uint16_t endNoteDurations[] = {
    8, 32, 64, 64, 64, 8,
    32, 64, 32, 8, 64, 64, 64, 
    64, 32, 64, 64, 64,
    64, 64, 64
}; */

//Without gap
/*
uint16_t endNoteDurations[] = {
120, 30, 15, 15, 15, 120, 
30, 15, 30, 120, 15, 15, 15, 
15, 30, 15, 15, 15,
15, 15, 15
}; */

//without gap
/*float endNoteVolume[] = {
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 
    0.5, 0.5, 0.5, 0.5, 0.5,
    0.5, 0.5, 0.5, 
}; */

const size_t melodySize = sizeof(melody) / sizeof(melody[0]);
const size_t endMelodySize = sizeof(endMelody) / sizeof(endMelody[0]);

void initBuzzer(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; // Enable clock for PORTE
    
    PORTE->PCR[PTE29_Pin] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[PTE29_Pin] |= PORT_PCR_MUX(3); // Set PTE29 to TPM0_CH2
    
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; // Enable clock for TPM0
    
    SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // Select clock source
    
    TPM0->MOD = 1431;
    TPM0_C2V = 300;
    
    TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
    TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
    TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
    
    TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
    TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
}

void SysTick_Delay(uint32_t delay) {
    SysTick->LOAD = (SystemCoreClock / 1000) * delay - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
    
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    
    SysTick->CTRL = 0;
}

void playNote(uint32_t freq, uint32_t duration, float volume) {
/*	uint32_t clockSpeed = 48000000;
  uint32_t prescaler = 128;
  uint32_t modValue = (clockSpeed / (prescaler * freq)) - 1;
	TPM0_C2V = (uint32_t)(modValue * volume);
	TPM0->MOD = modValue;
	osDelay(150); */
	
    uint32_t clockSpeed = 48000000;
    uint32_t prescaler = 128;
    uint32_t modValue = (clockSpeed / (prescaler * freq)) - 1;
    
    TPM0->MOD = modValue;
    TPM0_C2V = (uint32_t)(modValue * volume); 
		osDelay(duration*14);
		TPM0_C2V = 0;
		osDelay(1);
		//SysTick_Delay(duration); 
    
    //osDelay(duration);
	//	osDelay(duration);
    //TPM0_C2V = 0; 
}

/*void playMelody() {
	
    uint16_t melody[] = {NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_NULL };
    uint16_t noteDurations[] = {40, 30, 15, 15, 30, 30, 30, 30, 50, 200};
		float noteVolume[] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0};
		
		
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
			//	osSemaphoreAcquire(musicSemaphore, osWaitForever);
        playNote(melody[i], noteDurations[i], noteVolume[i]);
		//		osSemaphoreRelease(musicSemaphore);
		//		osDelay(noteDurations[i] * 1.45); 
        //osDelay(10);  // Small pause between notes
				SysTick_Delay(10); 
   // } 
		}
} */

void playMelody() {
	 for (int i = 0; i < sizeof(melody)/sizeof(melody[0]) ; i++) {
				osSemaphoreAcquire(musicSemaphore, osWaitForever);
        playNote(melody[i], noteDurations[i], noteVolume[i]);
				osSemaphoreRelease(musicSemaphore);
				osDelay(noteDurations[i] * 1.45);
		}
}

