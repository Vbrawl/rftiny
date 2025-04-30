#include "rftiny.h"

rftiny_buf rftiny_find_packet() {
	rftiny_buf buf = 0;

	while(1) {
		while(buf != SYNGID)
			rftiny_add_buf(rftiny_get_bit(), buf);

		/* read CODE */
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		rftiny_add_buf(rftiny_get_bit(), buf);
		return buf;
	}
}

void rftiny_put_preamble() {
	for(uint8_t i = 0; i < 12; i++) {
		rftiny_put_buf(0b10101010);
	}
}

void rftiny_put_packet(rftiny_buf data) {
	rftiny_put_preamble();
	rftiny_put_buf(SYNGID);
	rftiny_put_buf(data);
}
