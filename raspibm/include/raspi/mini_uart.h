#pragma once

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

#define REGS_AUX ((struct aux_regs *)(PBASE + 0x00215000))