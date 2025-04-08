#include "../../include/rftiny.h"
#include <pico/stdlib.h>
#include <stdio.h>


#define LED_PIN PICO_DEFAULT_LED_PIN

static uint8_t led_status = 0;
static volatile uint8_t pin_data = 0; // How many bits to read from pin_buf
static volatile uint8_t pin_buf = 0;

bool timer_callback() {
	static uint32_t sequence = SYN << 16 | GID << 8 | 0b00000000;
	static uint8_t offset = 31;
	uint8_t bit = (sequence >> offset--) & 1;

	pin_buf = (pin_buf << 1) | bit;
	pin_data += 1;
	return true;
}

void main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	struct repeating_timer timer;
	add_repeating_timer_ms(-1, timer_callback, NULL, &timer);
	rftiny_buf buf = rftiny_find_packet();
	cancel_repeating_timer(&timer);

	gpio_put(LED_PIN, 1);
	sleep_ms(500);
	gpio_put(LED_PIN, 0);

	gpio_put(LED_PIN, buf);
	while(1);
}

uint8_t rftiny_get_bit() {
	while(pin_data == 0);
	return (pin_buf >> pin_data--) & 1;
}