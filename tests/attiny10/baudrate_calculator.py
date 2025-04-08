
# The number of bits available to the timer
timer_bits = 16
max_timer = 2**timer_bits

# Values need to be on their specific index
prescaler_options = [
        1,
        8,
        64,
        256,
        1024
]


def main(clock_frequency: int, baudrate: int):
        baudrate_interval = 1/baudrate

        for index, prescaler in enumerate(prescaler_options):
                timer_frequency = clock_frequency / prescaler
                OCR = timer_frequency * baudrate_interval
                if(OCR < max_timer):
                        break

        print(f"OCR = {OCR}")
        print(f"PRESCALER = {prescaler}, selector = {index}")

main(12_000_000, 2400)
# main(12_000_000, 96000)