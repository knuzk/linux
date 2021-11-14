#include <raspi/peripherals.h>

extern void loop_delay(int count);

u64 raspi_4_io_base = RASPI_4_IO_PBASE;

/*
 * GPIO
 */

void gpio_pin_set_func(u8 pin, enum gpio_func func)
{
    u8 offset = (pin * 3) % 30;
    u8 reg = pin / 10;

    u32 selector = REGS_GPIO->func_select[reg];
    selector &= ~(7 << offset);
    selector |= (func << offset);

    REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pin)
{
    REGS_GPIO->pupd_enable = 0;
    loop_delay(150);
    REGS_GPIO->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
    loop_delay(150);
    REGS_GPIO->pupd_enable = 0;
    REGS_GPIO->pupd_enable_clocks[pin / 32] = 0;
}

/*
 * AUX
 */

void uart_send(char c)
{
    while (1) {
        if (REGS_AUX->mu_lsr & 0x20) {
            break;
        }
    }
    REGS_AUX->mu_io = c;
}

char uart_recv(void)
{
    while (1) {
        if (REGS_AUX->mu_lsr & 0x01) {
            break;
        }
    }
    return REGS_AUX->mu_io & 0xFF;
}

#define TXD 14
#define RXD 15

void uart_init(void)
{
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    REGS_AUX->enables       = 1;        // Enable mini uart (this also enables access to its registers)
    REGS_AUX->mu_control    = 0;        // Disable auto flow control and disable receiver and transmiter (for now)
    REGS_AUX->mu_ier        = AUX_ENABLE_RECEIVE_INTERRUPT; // Enable receive interrupt
    REGS_AUX->mu_lcr        = 3;        // Enable 8 bit mode
    REGS_AUX->mu_mcr        = 0;        // Set RTS line to be always high
    REGS_AUX->mu_baud_rate  = SYS_CLOCK_FREQ / UART_BAND_RATE / 8 - 1;  // Set baud rate to 115200

    REGS_AUX->mu_control    = 3;        // Finally, enable transimitter and receiver
}
