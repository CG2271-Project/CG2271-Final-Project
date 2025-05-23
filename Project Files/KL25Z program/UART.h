#ifndef UART_H
#define UART_H

#include "MKL25Z4.h"
#include "cmsis_os2.h"

/* Default Core Clk Freq is 20.97152MHz */
// Current code will run at 48 MHz core clk freq and 24MHz Bus clk freq

#define BAUD_RATE 9600
#define UART_TX_PORTE22 22 // Page 162 datasheet
#define UART_RX_PORTE23 23 // Page 162 datasheet
#define UART2_INT_PRIO 128

#define Q_SIZE (32)

extern volatile int8_t x_offset;
extern volatile int8_t y_offset;
extern volatile int8_t crab;
extern volatile int8_t celebrate;
extern osSemaphoreId_t brainSemaphore;

typedef struct {
  unsigned char Data[Q_SIZE];
  unsigned int Head;
  unsigned int Tail; // points to next free space
  unsigned int Size; // quantity of elements in queue
} Q_T;

// Init UART2
void initUART2(uint32_t);

void UART2_IRQHandler(void);

#endif
