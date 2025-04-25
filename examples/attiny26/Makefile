RX=rx
TX=tx

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -I../../ -mmcu=attiny26

RECEIVER_SOURCES = ../../rftiny.c rftiny.c
TRANSMITTER_SOURCES = ../../rftiny.c rftiny_send.c
#TRANSMITTER_SOURCES = rftiny_send.c

.PHONY: all clean flash_%

all: $(TX).hex $(RX).hex

flash_%: %.hex
	avrdude -c usbasp -p t26 -U flash:w:$<:i

clean:
	rm -r $(TX).elf $(TX).hex $(RX).elf $(RX).hex

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

tx.elf: $(TRANSMITTER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

rx.elf: $(RECEIVER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@