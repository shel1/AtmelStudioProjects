/*
 * AtTinyInterruptTester.c
 *
 * Created: 11/2/2022 9:45:00 PM
 * Author : crash
*/

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	//DDRB = 0x01;
	PORTB ^= (1<<PORTB0);
	PORTB ^= (1<<PORTB1);
	PORTB ^= (1<<PORTB2);
	PORTB ^= (1<<PORTB3);
	PORTB ^= (1<<PORTB4);
	PORTB ^= (1<<PORTB5);	

}


int main (void){
	
	
	//enable ports as outputs
	DDRB |= (1<<PORTB0);
	DDRB |= (1<<PORTB2);
	DDRB |= (1<<PORTB4);
	DDRB |= (1<<PORTB1);
	DDRB |= (1<<PORTB3);
	DDRB |= (1<<PORTB5);
	//set starting states
	PORTB |= (1<<PORTB0);
	PORTB |= (1<<PORTB2);
	PORTB |= (1<<PORTB4);

	PORTB |= (0<<PORTB1);
	PORTB |= (0<<PORTB3);
	PORTB |= (0<<PORTB5);
	
	sei();
	
	// turn on interrupts!
	GIMSK  |= (1<<INT0);

	// interrupt on INT0 pin rising edge (sensor triggered)
	MCUCR = (1<<ISC01) | (1<<ISC00);
	
	
	
	while (1) {
		
	}
}

