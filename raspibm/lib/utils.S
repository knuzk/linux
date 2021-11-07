#include <linux/linkage.h>
#include <asm/assembler.h>

SYM_CODE_START(loop_delay)
1:  subs    x0, x0, #1
    bne     1b
    ret
SYM_CODE_END(loop_delay)