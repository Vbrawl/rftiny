
# The number of bits available to the timer
timer_bits = 8
max_timer = 2**timer_bits

# Values need to be on their specific index
prescaler_options = {
        1: 0b0001,
        2: 0b0010,
        4: 0b0011,
        8: 0b0100,
        16: 0b0101,
        32: 0b0110,
        64: 0b0111,
        128: 0b1000,
        256: 0b1001,
        512: 0b1010,
        1024: 0b1011,
        2048: 0b1100,
        4096: 0b1101,
        8192: 0b1110,
        16384: 0b1111
}


def main(clock_frequency: int, baudrate: int):
        baudrate_interval = 1/baudrate

        for prescaler, prescaler_selector in sorted(prescaler_options.items(), key=lambda x: x[0]):
                timer_frequency = clock_frequency / prescaler
                OCR = timer_frequency * baudrate_interval
                if(OCR < max_timer):
                        break

        print(f"OCR = {OCR}")
        print(f"PRESCALER = {prescaler}, selector = {prescaler_selector}")

main(1_200_000, 10)
#main(12_000_000, 2400)
# main(12_000_000, 96000)
