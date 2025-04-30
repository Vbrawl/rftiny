#ifndef RFTINY_H
#define RFTINY_H

#include <stdint.h>

typedef uint8_t rftiny_buf;

#define SYNGID 0b11101101

#define rftiny_add_buf(bit, buf) (buf = (buf << 1) | (bit & 1))

void rftiny_put_preamble();
rftiny_buf rftiny_find_packet();
void rftiny_put_asksyn();
void rftiny_put_packet(rftiny_buf data);
uint8_t rftiny_get_bit();
void rftiny_put_buf(rftiny_buf buf);


#endif
