#include "UART.h"

volatile uint8_t UARTNumber = 0;
volatile int8_t x_offset = 0;
volatile int8_t y_offset = 0;
volatile int8_t celebrate = 0;
volatile int8_t crab = 0;

void initUART2(uint32_t baud_rate) {
  uint32_t divisor, bus_clock;

  SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
  SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

  PORTE->PCR[UART_RX_PORTE23] &= ~PORT_PCR_MUX_MASK;
  PORTE->PCR[UART_RX_PORTE23] |= PORT_PCR_MUX(4);

  UART2->C2 &= ~((UART_C2_TE_MASK) | (UART_C2_RE_MASK));

  bus_clock = (DEFAULT_SYSTEM_CLOCK) / 2;
  divisor = bus_clock / (baud_rate * 16);
  UART2->BDH = UART_BDH_SBR(divisor >> 8);
  UART2->BDL = UART_BDL_SBR(divisor);

  UART2->C1 = 0;
  UART2->S2 = 0;
  UART2->C3 = 0;

  UART2->C2 |= UART_C2_RE_MASK;

  NVIC_SetPriority(UART2_IRQn, 128);
  NVIC_ClearPendingIRQ(UART2_IRQn);
  NVIC_EnableIRQ(UART2_IRQn);

  UART2->C2 |= UART_C2_RIE_MASK;
}


void UART2_IRQHandler() {
  NVIC_ClearPendingIRQ(UART2_IRQn);
  
  // Receiver Interrupt Handler
  if(UART2->S1 & UART_S1_RDRF_MASK)
		UARTNumber = UART2->D;

	// Extract first group: bits 0–2 (rightmost 3 bits)
	uint8_t h_offset_group = UARTNumber & 0x07; // 0b00000111

	// Extract second group: bits 3–6
	uint8_t speed_group = (UARTNumber >> 3) & 0x07; // shift right 3, then mask
	
	// Extract third group: bits 7
	celebrate = (UARTNumber >> 7) & 0x01; // shift right 3, then mask
	
	crab = (UARTNumber >> 6) & 0x01; // shift right 3, then mask

	// Decode: MSB is sign, remaining 2 bits are value
	x_offset = ((h_offset_group & 0x04) ? -1 : 1) * (h_offset_group & 0x03);
	// Decode: MSB is sign, remaining 3 bits are value
	y_offset = ((speed_group & 0x04) ? -1 : 1) * (speed_group & 0x03);
	
	
	osSemaphoreRelease(brainSemaphore);

  // Error Cases
  if (UART2->S1 & (UART_S1_OR_MASK 
                  | UART_S1_NF_MASK
                  | UART_S1_FE_MASK 
                  | UART_S1_PF_MASK)) {
    // handle the error
    
    // clear the flag
  }
}
