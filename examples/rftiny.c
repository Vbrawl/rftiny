#include "../rftiny.h"

int main() {
	if(rftiny_find_packet() == 1)
		return 0;
	else
		return 1;
}

uint8_t rftiny_get_bit() {
	static uint32_t sequence = ((uint32_t)SYNGID << 8) | 0b00000001;
	static uint8_t offset = 31;
	uint8_t bit = (sequence >> offset--) & 1;
	return bit;
}

void rftiny_put_buf(rftiny_buf data) {}
