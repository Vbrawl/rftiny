
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../rftiny.h"

#define TIMER_CHECK_FOR 156
#define TIMER_PRESCALER 6

static volatile uint8_t rx_data_len = 0; // How many bits are available at rx_data_buf
static volatile rftiny_buf rx_data_buf = 0; // Data buf

void main() {
	// Timer 1 configuration
	TCCR1A = 0
		// CTC (Clear Timer on Compare match)
		| (1 << CTC1)
		// Setup prescaler
		| ((TIMER_PRESCALER & 0b0001) << CS10)
		| (((TIMER_PRESCALER & 0b0010) >> 1) << CS11)
		| (((TIMER_PRESCALER & 0b0100) >> 2) << CS12)
		| (((TIMER_PRESCALER & 0b1000) >> 3) << CS13);

	// Timer 1 value for interrupt
	OCR1A = TIMER_CHECK_FOR;

	// Enable Timer 1 interrupt for compare match
	TIMSK = (1 << OCIE1A);

	// Enable interrupts
	sei();

	rftiny_buf data = rftiny_find_packet();

	while(1);
}

ISR(__vector_TIM1_COMPA) {
	rx_data_buf = (rx_data_buf << 1) | ((PINB >> PB0) & 1);
	rx_data_len += 1;
}

uint8_t rftiny_get_bit() {
	while(rx_data_len == 0);
	return (rx_data_buf >> rx_data_buf--) & 1;
}

void rftiny_put_buf(rftiny_buf buf) {}