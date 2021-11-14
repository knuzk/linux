// SPDX-License-Identifier: GPL-2.0-only
/*
 * Based on arch/arm/mm/mmu.c
 *
 * Copyright (C) 1995-2005 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#include <linux/cache.h>
#include <linux/memory.h>

#include <asm/mmu_context.h>

u64 idmap_t0sz = TCR_T0SZ(VA_BITS_MIN);
u64 idmap_ptrs_per_pgd = PTRS_PER_PGD;

u64 __section(".mmuoff.data.write") vabits_actual;
EXPORT_SYMBOL(vabits_actual);

u64 kimage_voffset __ro_after_init;
EXPORT_SYMBOL(kimage_voffset);
