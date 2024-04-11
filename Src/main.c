/* Libraries, Definitions and Global Declarations */
#include <stdint.h>
#include "main.h"
#include "uart.h"

/* Function prototypes */
void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

/* Superloop structure */
int main(void)
{
	/* Declarations and Initializations */
	USER_RCC_ClockEnable( );
	USER_GPIO_Init( );
	USER_USART1_Init( );

    	/* Repetitive block */
    	for(;;){
    		printf("Presiona la tecla 't' para encender el LED...\r\n");
    		uint8_t recv_char = USER_USART1_Read_8bit();

    		// ascii: 	t
    		// decimal: 116
    		// hex:		0x74
    		// binary:	01110100

    		if (recv_char == 116) {
    			GPIOA->ODR ^= ( 0x1UL << 5U );
    		}
    	}
}

void USER_RCC_ClockEnable( void ){
	RCC->APB2ENR	|=	 ( 0x1UL <<  2U )//	IO port A clock enable
					|	 ( 0x1UL << 14U );//	USART 1 clock enable
}
void USER_GPIO_Init( void ){
	/* USART */
	//pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz
	GPIOA->CRH	&=	~( 0x1UL <<  6U )
				&	~( 0x2UL <<  4U );

	GPIOA->CRH	|=	 ( 0x2UL <<  6U )
				|	 ( 0x1UL <<  4U );

	/* LED */
	// PA5 as reset
	GPIOA->BSRR	=	( 0x1UL << 21U );

	// clear bits to remove trash values
	GPIOA->CRL &= ~( 0x3UL << 22U ) & ~( 0x2UL << 20U );

	// set bits to configure
	GPIOA->CRL	|= ( 0x1UL << 20U ); // output, 10mhz
}
