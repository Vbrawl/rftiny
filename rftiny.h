#ifndef RFTINY_H
#define RFTINY_H

#include <stdint.h>

typedef uint8_t rftiny_buf;

#define SYN 0b10110110
#define GID 0b00000000

void rftiny_add_buf(uint8_t bit, rftiny_buf *buf);
rftiny_buf rftiny_find_packet();
void rftiny_put_packet(rftiny_buf data);
uint8_t rftiny_get_bit();
void rftiny_put_buf(rftiny_buf buf);


#endif