#include "rftiny.h"

void rftiny_add_buf(uint8_t bit, rftiny_buf *buf) {
	*buf = (*buf << 1) | (bit & 1);
}

rftiny_buf rftiny_find_packet() {
	rftiny_buf buf = 0;

	while(1) {
		while(buf != SYNGID)
			rftiny_add_buf(rftiny_get_bit(), &buf);

		/* read CODE */
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		rftiny_add_buf(rftiny_get_bit(), &buf);
		return buf;
	}
}

void rftiny_put_packet(rftiny_buf data) {
	rftiny_put_buf(SYNGID);
	rftiny_put_buf(data);
}
