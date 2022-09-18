#ifndef __UARTDRV__
#define __UARTDRV__

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_drv_init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);


#endif __UARTDRV__
