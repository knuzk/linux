#pragma once

#include <raspi/common.h>

struct gpio_pin_data {
    reg32 reserved;
    reg32 data[2];
};

struct gpio_regs {
    reg32                   func_select[6];
    struct gpio_pin_data    output_set;
    struct gpio_pin_data    output_clear;
    struct gpio_pin_data    level;
    struct gpio_pin_data    ev_detect_status;
    struct gpio_pin_data    re_detect_enable;
    struct gpio_pin_data    fe_detect_enable;
    struct gpio_pin_data    hi_detect_enable;
    struct gpio_pin_data    lo_detect_enable;
    struct gpio_pin_data    async_re_detect;
    struct gpio_pin_data    async_fe_detect;
    reg32                   reserved;
    reg32                   pupd_enable;
    reg32                   pupd_enable_clocks[2];
};

enum gpio_func {
    GFInput     = 0,
    GFOutput    = 1,
    GFAlt0      = 4,
    GFAlt1      = 5,
    GFAlt2      = 6,
    GFAlt3      = 7,
    GFAlt4      = 3,
    GFAlt5      = 2
};

void gpio_pin_set_func(struct gpio_regs *regs, u8 pin, enum gpio_func func);
void gpio_pin_enable(struct gpio_regs *regs, u8 pin);
