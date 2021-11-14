// SPDX-License-Identifier: GPL-2.0-only
/*
 * Contains CPU feature definitions
 *
 * Copyright (C) 2015 ARM Ltd.
 *
 * A note for the weary kernel hacker: the code here is confusing and hard to
 * follow! That's partly because it's solving a nasty problem, but also because
 * there's a little bit of over-abstraction that tends to obscure what's going
 * on behind a maze of helper functions and macros.
 *
 * The basic problem is that hardware folks have started gluing together CPUs
 * with distinct architectural features; in some cases even creating SoCs where
 * user-visible instructions are available only on a subset of the available
 * cores. We try to address this by snapshotting the feature registers of the
 * boot CPU and comparing these with the feature registers of each secondary
 * CPU when bringing them up. If there is a mismatch, then we update the
 * snapshot state to indicate the lowest-common denominator of the feature,
 * known as the "safe" value. This snapshot state can be queried to view the
 * "sanitised" value of a feature register.
 *
 * The sanitised register values are used to decide which capabilities we
 * have in the system. These may be in the form of traditional "hwcaps"
 * advertised to userspace or internal "cpucaps" which are used to configure
 * things like alternative patching and static keys. While a feature mismatch
 * may result in a TAINT_CPU_OUT_OF_SPEC kernel taint, a capability mismatch
 * may prevent a CPU from being onlined at all.
 *
 * Some implementation details worth remembering:
 *
 * - Mismatched features are *always* sanitised to a "safe" value, which
 *   usually indicates that the feature is not supported.
 *
 * - A mismatched feature marked with FTR_STRICT will cause a "SANITY CHECK"
 *   warning when onlining an offending CPU and the kernel will be tainted
 *   with TAINT_CPU_OUT_OF_SPEC.
 *
 * - Features marked as FTR_VISIBLE have their sanitised value visible to
 *   userspace. FTR_VISIBLE features in registers that are only visible
 *   to EL0 by trapping *must* have a corresponding HWCAP so that late
 *   onlining of CPUs cannot lead to features disappearing at runtime.
 *
 * - A "feature" is typically a 4-bit register field. A "capability" is the
 *   high-level description derived from the sanitised field value.
 *
 * - Read the Arm ARM (DDI 0487F.a) section D13.1.3 ("Principles of the ID
 *   scheme for fields in ID registers") to understand when feature fields
 *   may be signed or unsigned (FTR_SIGNED and FTR_UNSIGNED accordingly).
 *
 * - KVM exposes its own view of the feature registers to guest operating
 *   systems regardless of FTR_VISIBLE. This is typically driven from the
 *   sanitised register values to allow virtual CPUs to be migrated between
 *   arbitrary physical CPUs, but some features not present on the host are
 *   also advertised and emulated. Look at sys_reg_descs[] for the gory
 *   details.
 *
 * - If the arm64_ftr_bits[] for a register has a missing field, then this
 *   field is treated as STRICT RES0, including for read_sanitised_ftr_reg().
 *   This is stronger than FTR_HIDDEN and can be used to hide features from
 *   KVM guests.
 */

#define pr_fmt(fmt) "CPU features: " fmt

#include <linux/types.h>
#include <asm/cpufeature.h>

#define __ARM64_FTR_BITS(SIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	{						\
		.sign = SIGNED,				\
		.visible = VISIBLE,			\
		.strict = STRICT,			\
		.type = TYPE,				\
		.shift = SHIFT,				\
		.width = WIDTH,				\
		.safe_val = SAFE_VAL,			\
	}

/* Define a feature with unsigned values */
#define ARM64_FTR_BITS(VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	__ARM64_FTR_BITS(FTR_UNSIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL)

/* Define a feature with a signed value */
#define S_ARM64_FTR_BITS(VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL) \
	__ARM64_FTR_BITS(FTR_SIGNED, VISIBLE, STRICT, TYPE, SHIFT, WIDTH, SAFE_VAL)

#define ARM64_FTR_END					\
	{						\
		.width = 0,				\
	}

static const struct arm64_ftr_bits ftr_ctr[] = {
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_EXACT, 31, 1, 1), /* RES1 */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_DIC_SHIFT, 1, 1),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_IDC_SHIFT, 1, 1),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_HIGHER_OR_ZERO_SAFE, CTR_CWG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_HIGHER_OR_ZERO_SAFE, CTR_ERG_SHIFT, 4, 0),
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_DMINLINE_SHIFT, 4, 1),
	/*
	 * Linux can handle differing I-cache policies. Userspace JITs will
	 * make use of *minLine.
	 * If we have differing I-cache policies, report it as the weakest - VIPT.
	 */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_NONSTRICT, FTR_EXACT, CTR_L1IP_SHIFT, 2, ICACHE_POLICY_VIPT),	/* L1Ip */
	ARM64_FTR_BITS(FTR_VISIBLE, FTR_STRICT, FTR_LOWER_SAFE, CTR_IMINLINE_SHIFT, 4, 0),
	ARM64_FTR_END,
};

struct arm64_ftr_reg arm64_ftr_reg_ctrel0 = {
	.name		= "SYS_CTR_EL0",
	.ftr_bits	= ftr_ctr
};