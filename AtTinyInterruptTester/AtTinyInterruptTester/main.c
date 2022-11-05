
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	//DDRB = 0x01;
	PORTB ^= (1<<PORTB0);

}


int main (void){
	
	
	DDRD = 1<<PORTD2;		// Set PD2 as input (Using for interupt INT0)
	PORTD = 1<<PORTD2;
	
	sei();
	
	// turn on interrupts!
	GIMSK  |= (1<<INT0);

	// interrupt on INT0 pin falling edge (sensor triggered)
	MCUCR = (1<<ISC01) | (1<<ISC00);
	
	
	
	while (1) {
		
	}
}
/*
 * AtTinyInterruptTester.c
 *
 * Created: 11/2/2022 9:45:00 PM
 * Author : crash


#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
	MCUCR |= (1<<ISC01)|(1<<ISC00);
	//set pull up
	PORTD |= (1<PORTD2);
	DDRD |= (0<<PORTD2);
    DDRB = (1<<PORTB0);
	PORTB = (1<<PORTB0);
	GIMSK = (1<<INT0);
	
	sei();

}

ISR(INT0_vect){
	PORTB ^= (1<<PORTB0);
}

 */ 