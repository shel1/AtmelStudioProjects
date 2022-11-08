/*
 * SeedGenerator.c
 *
 * Created: 11/6/2022 12:10:15 PM
 * Author : crash
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SEED1_ON		PORTB |= (1<<PORTB0)
#define SEED2_ON		PORTB |= (1<<PORTB1)
#define SEED3_ON		PORTB |= (1<<PORTB2)
#define SEED4_ON		PORTB |= (1<<PORTB3)
#define SEED5_ON		PORTB |= (1<<PORTB4)
#define SEED6_ON		PORTB |= (1<<PORTB5)
#define SEED7_ON		PORTB |= (1<<PORTB6)
#define SEED8_ON		PORTD |= (1<<PORTD6)
#define REGCLEAR_OFF	PORTD |= (1<<PORTD4)
#define REG_DISABLE		PORTD |= (1<<PORTD5)

#define SEED1_OFF		PORTB &= ~(1<<PORTB0)
#define SEED2_OFF		PORTB &= ~(1<<PORTB1)
#define SEED3_OFF		PORTB &= ~(1<<PORTB2)
#define SEED4_OFF		PORTB &= ~(1<<PORTB3)
#define SEED5_OFF		PORTB &= ~(1<<PORTB4)
#define SEED6_OFF		PORTB &= ~(1<<PORTB5)
#define SEED7_OFF		PORTB &= ~(1<<PORTB6)
#define SEED8_OFF		PORTD &= ~(1<<PORTD6)
#define REGCLEAR_ON		PORTD &= ~(1<<PORTD4)
#define REG_ENABLE		PORTD &= ~(1<<PORTD5)

#define SEED1_TOGGLE		PORTB ^= (1<<PORTB0)
#define SEED2_TOGGLE		PORTB ^= (1<<PORTB1)
#define SEED3_TOGGLE		PORTB ^= (1<<PORTB2)
#define SEED4_TOGGLE		PORTB ^= (1<<PORTB3)
#define SEED5_TOGGLE		PORTB ^= (1<<PORTB4)
#define SEED6_TOGGLE		PORTB ^= (1<<PORTB5)
#define SEED7_TOGGLE		PORTB ^= (1<<PORTB6)
#define SEED8_TOGGLE		PORTD ^= (1<<PORTD6)

#define MASK0	0b1

/*	PB0	seed1
	PB1	seed2
	PB2	seed3
	PB3	seed4
	PB4	seed5
	PB5	seed6
	PB6	seed7
	PD6	seed8
	PD4 reg_clear (ACTIVE LOW)
	PD5	reg_enable
	
*/
uint8_t counter = 0;
uint8_t seed1	=	0b10101010;
uint8_t seed2	=	0b01010101;
uint8_t seed3	=	0b11100011;
uint8_t seed4	=	0b00011100;
uint8_t seed5	=	0b11101010;
uint8_t seed6	=	0b00101010;
uint8_t seed7	=	0b00010100;
uint8_t seed8	=	0b10101010;


ISR(INT0_vect)
{
	if (counter < 0x8){
		if(seed1 & MASK0){
			SEED1_ON;
		}else{
			SEED1_OFF;
			}
		if(seed2 & MASK0){
			SEED2_ON;
		}else{
			SEED2_OFF;
			}		
		if(seed3 & MASK0){
			SEED3_ON;
		}else{
			SEED3_OFF;
			}
		if(seed4 & MASK0){
			SEED4_ON;
		}else{
			SEED4_OFF;
			}			
		if(seed5 & MASK0){
			SEED5_ON;
		}else{
			SEED5_OFF;
			}
		if(seed6 & MASK0){
			SEED6_ON;
		}else{
			SEED6_OFF;
			}		
		if(seed7 & MASK0){
			SEED7_ON;
		}else{
			SEED7_OFF;
			}		
		if(seed8 & MASK0){
			SEED8_ON;
		}else{
			SEED8_OFF;
			}		
		//increment counter and shift seeds
		counter++;
		seed1 = seed1>>1;
		seed2 = seed2>>1;
		seed3 = seed3>>1;
		seed4 = seed4>>1;
		seed5 = seed5>>1;
		seed6 = seed6>>1;
		seed7 = seed7>>1;
		seed8 = seed8>>1;
		}else{
			//once seeds are loaded, enable all the shift registers
			REG_ENABLE;
		}
	}


int main (void){
	
	
	//enable ports as outputs
	DDRB |= (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB4)|(1<<PORTB5)|(1<<PORTB6);
	DDRD |= (1<<PORTD6)|(1<<PORTD4)|(1<<PORTD5);
	//set starting states
	REG_DISABLE;
	REGCLEAR_ON;
	_delay_ms(100);
	REGCLEAR_OFF;
	SEED1_OFF;
	SEED1_OFF;
	SEED3_OFF;
	SEED4_OFF;
	SEED5_OFF;
	SEED6_OFF;
	SEED7_OFF;
	SEED8_OFF;
	
	sei();
	
	// turn on interrupts!
	GIMSK  |= (1<<INT0);

	// interrupt on INT0 pin rising edge (sensor triggered)
	MCUCR = (1<<ISC01) | (1<<ISC00);
	
	
	
	while (1) {
		
	}
}

