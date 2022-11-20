/*
 * OutputReader.c
 *
 * Created: 11/19/2022 11:02:25 AM
 * Author : crash
 */ 

#define F_CPU	1e6
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t out = 0;

//handler for PCINT0-7 changes (whenever the shift register shifts, this interrupt should fire and read the value of each pin
ISR(PCINT0_vect){
	
	//debug, only when the PCINT fires
	PORTD ^= (1<<PORTD5);
	uint8_t msk1 = 0b00000001;
	uint8_t msk2 = 0b00000010;
	uint8_t msk3 = 0b00000100;
	uint8_t msk4 = 0b00001000;
	uint8_t msk5 = 0b00010000;
	uint8_t msk6 = 0b00100000;
	uint8_t msk7 = 0b01000000;
	uint8_t msk8 = 0b10000000;
	uint8_t out = 0;
	
	uint8_t val = PINB;
	
	//detect bit 0
	if ((PINB>>0) & msk1){
		out = out + msk1;
		}
	//detect bit 1
	if ((PINB>>1) & msk2){
		out = out + msk2;
	}
	//detect bit 2
	if ((PINB>>2) & msk3){
		out = out + msk3;
	}
	//detect bit 3
	if ((PINB>>3) & msk4){
		out = out + msk4;
	}
	//detect bit 4
	if ((PINB>>4) & msk5){
		out = out + msk5;
	}
	//detect bit 5
	if ((PINB>>5) & msk6){
		out = out + msk6;
	}
	//detect bit 6
	if ((PINB>>6) & msk7){
		out = out + msk7;
	}
	//detect bit 7
	if ((PINB>>7) & msk8){
		out = out + msk4;
	}	
	
	//TBD clear GIFR PCIF0 flag
}


int main(void)
{
	DDRB = 0x0; //define all port B pins as inputs	
	DDRD |= (1<<DDD6)|(1<<DDD5); //enable PD6 as an output
	
	PORTD &= ~(1<<PORTD6);
	PORTD &= ~(1<<PORTD5);
	
	
	
	PCMSK |= (1<<PCINT7)|(1<<PCINT6)|(1<<PCINT5)|(1<<PCINT4)|(1<<PCINT3)|(1<<PCINT2)|(1<<PCINT1)|(1<<PCINT0);// = 0xFF, spelled out for clarity.
	GIMSK  |= (1<<PCIE0);// turn on interrupts!
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD ^= (1<<PORTD6);
		_delay_ms(100);
    }
}

