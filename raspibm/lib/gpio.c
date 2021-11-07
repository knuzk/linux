#include <raspi/gpio.h>

extern void loop_delay(int count);

void gpio_pin_set_func(struct gpio_regs *regs, u8 pin, enum gpio_func func)
{
    u8 offset = (pin * 3) % 30;
    u8 reg = pin / 10;

    u32 selector = regs->func_select[reg];
    selector &= ~(7 << offset);
    selector |= (func << offset);

    regs->func_select[reg] = selector;
}

void gpio_pin_enable(struct gpio_regs *regs, u8 pin)
{
    regs->pupd_enable = 0;
    loop_delay(150);
    regs->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
    loop_delay(150);
    regs->pupd_enable = 0;
    regs->pupd_enable_clocks[pin / 32] = 0;
}
