#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../rftiny.h"

// #define TIMER_CHECK_FOR (unsigned int)145
// #define TIMER_PRESCALER 6
#define TIMER_CHECK_FOR (unsigned int)0b01111111
#define TIMER_PRESCALER 0b0001

// #define TIMER_CHECK_FOR 156
// #define TIMER_PRESCALER 6

static volatile uint8_t tx_data_len = 0; // How many bits are available in tx_data_buf
static volatile rftiny_buf tx_data_buf = 0; // Data buf

void main() {
	DDRB = _BV(PB0);

	// Configure timer1 for CTC mode
	TIMSK |= _BV(OCIE1A);

	OCR1A = TIMER_CHECK_FOR;
	OCR1C = TIMER_CHECK_FOR;

	TCCR1B = 0
		| _BV(CTC1)
		| ((TIMER_PRESCALER & 0b0001) << CS10)
		| (((TIMER_PRESCALER & 0b0010) >> 1) << CS11)
		| (((TIMER_PRESCALER & 0b0100) >> 2) << CS12)
		| (((TIMER_PRESCALER & 0b1000) >> 3) << CS13);

	// Enable interrupts
	sei();

	rftiny_buf data = 0b00000010;
	rftiny_put_packet(data);

	while(1);
}

ISR(TIMER1_CMPA_vect) {
	if(tx_data_len == 0) return;
	uint8_t bit = (tx_data_buf >> (tx_data_len - 1)) & 1;
	tx_data_len -= 1;

	PORTB = (bit << PB0);
}

void rftiny_put_buf(rftiny_buf data) {
	while(tx_data_len > 0);
	tx_data_buf = (tx_data_buf << sizeof(data) * 8) | data;
	tx_data_len += sizeof(data) * 8;
}

uint8_t rftiny_get_bit() { return 0; }
