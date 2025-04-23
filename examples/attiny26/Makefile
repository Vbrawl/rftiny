RX=rx
TX=tx

CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Os -I../../ -mmcu=attiny26

RECEIVER_SOURCES = ../../rftiny.c rftiny.c
TRANSMITTER_SOURCES = ../../rftiny.c rftiny_send.c

.PHONE: all clean

all: $(TX) $(TX).hex $(RX) $(RX).hex
flash_tx: all
	avrdude -c usbasp -p t26 -U flash:w:tx.hex:i

clean:
	rm -r $(TX) $(TX).hex $(RX) $(RX).hex

$(TX).hex: $(TX)
	$(OBJCOPY) -j .text -j .data -O ihex $(TX) $(TX).hex

$(RX).hex: $(RX)
	$(OBJCOPY) -j .text -j .data -O ihex $(RX) $(RX).hex

$(TX): $(TRANSMITTER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

$(RX): $(RECEIVER_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
