
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../include/rftiny.h"

#define TIMER_CHECK_FOR (unsigned long long)5000
#define TIMER_PRESCALER 0

static volatile uint8_t rx_data_len = 0; // How many bits are available at rx_data_buf
static volatile rftiny_buf rx_data_buf = 0; // Data buf

void _start() {
	// Timer 0 configuration
	TCCR0A = 0
		| (1 << WGM01) // CTC (Clear Timer on Compare match)
		| (1 << CS00); // No prescaler

	// Timer 0 timer value for interrupt
	OCR0AH = (TIMER_CHECK_FOR >> 8);
	OCR0AL = (TIMER_CHECK_FOR & 0x00FF);

	// Enable Timer 0 interrupt for compare match
	TIMSK0 = (1 << OCIE0A);

	// Enable interrupts
	sei();

	while(1);
}

ISR(__vector_TIM0_COMPA) {
	rx_data_buf = (rx_data_buf << 1) | ((PINB >> PB0) & 1);
	rx_data_len += 1;
}

uint8_t rftiny_get_bit() {
	while(rx_data_len == 0);
	return (rx_data_buf >> rx_data_buf--) & 1;
}