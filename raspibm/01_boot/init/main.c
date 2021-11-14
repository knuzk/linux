// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/init/main.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  GK 2/5/95  -  Changed to support mounting root fs via NFS
 *  Added initrd & change_root: Werner Almesberger & Hans Lermen, Feb '96
 *  Moan early if gcc is old, avoiding bogus kernels - Paul Gortmaker, May '96
 *  Simplified starting of init:  Michael A. Griffith <grif@acm.org>
 */

#define DEBUG		/* Enable initcall_debug */

#include <linux/memory.h>
#include <linux/start_kernel.h>

#include <asm/cputype.h>
#include <asm/pgtable.h>
#include <asm/sysreg.h>

#include <raspi/peripherals.h>
#include <raspi/print.h>

/*
 * The recorded values of x0 .. x3 upon kernel entry.
 */
u64 __cacheline_aligned boot_args[4];

volatile unsigned long __section(".mmuoff.data.read")
secondary_holding_pen_release = INVALID_HWID;

asmlinkage __visible void __init __no_sanitize_address start_kernel(void)
{
    // disable MMU
    // write_sysreg(SCTLR_EL1_RES1 | ENDIAN_SET_EL1, sctlr_el1);
    raspi_4_io_base = RASPI_4_IO_VBASE;
    uart_init();

    print_s("\nHello, world.\n");

    while (1) {
        char c = uart_recv();
        if (c == '\r') {
            uart_send('\n');
        }
        uart_send(c);
    }
}
