#pragma once

#include <linux/sizes.h>
#include <linux/types.h>

#define SYS_CLOCK_FREQ (500 * 1000 * 1000)      // 500 Mhz

#define RASPI_4_IO_PBASE        0x00000000FE000000
#define RASPI_4_IO_VBASE        0xFFFFFFB000000000
#define RASPI_4_IO_SIZE         SZ_4M


#ifndef __ASSEMBLY__

typedef volatile u32    reg32;

extern u64 raspi_4_io_base;

#define RASPI_4_GPIO_BASE       (raspi_4_io_base + 0x00200000)
#define RASPI_4_AUX_BASE        (raspi_4_io_base + 0x00215000)

/*
 * GPIO
 */

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

#define REGS_GPIO ((struct gpio_regs *)(RASPI_4_GPIO_BASE))

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

void gpio_pin_set_func(u8 pin, enum gpio_func func);
void gpio_pin_enable(u8 pin);

/*
 * AUX
 */

#define AUX_ENABLE_RECEIVE_INTERRUPT        0x0D
#define AUX_INTERRUPT_ID_BITS               (3 << 1)
#define AUX_RECEIVER_HOLDS_VALID_BYTE       (2 << 1)

struct aux_regs {
    reg32 irq_status;
    reg32 enables;
    reg32 reserved[14];
    reg32 mu_io;
    reg32 mu_ier;
    reg32 mu_iir;
    reg32 mu_lcr;
    reg32 mu_mcr;
    reg32 mu_lsr;
    reg32 mu_msr;
    reg32 mu_scratch;
    reg32 mu_control;
    reg32 mu_status;
    reg32 mu_baud_rate;
};

#define REGS_AUX ((struct aux_regs *)(RASPI_4_AUX_BASE))

#define UART_BAND_RATE  115200

void uart_init(void);
char uart_recv(void);
void uart_send(char c);

#endif // __ASSEMBLY__
