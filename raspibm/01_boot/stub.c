#include <linux/cache.h>
#include <linux/debugobjects.h>
#include <linux/export.h>
#include <linux/jump_label.h>
#include <linux/linkage.h>
#include <linux/memory.h>
#include <linux/percpu-defs.h>
#include <linux/preempt.h>
#include <linux/preempt.h>
#include <linux/proc_ns.h>
#include <linux/sched/debug.h>
#include <generated/compile.h>
#include <generated/utsrelease.h>

#include <asm/cputype.h>
#include <asm/kprobes.h>
#include <asm/kvm_host.h>
#include <asm/traps.h>

// file: arch/arm64/kernel/smp.c

DEFINE_PER_CPU_READ_MOSTLY(int, cpu_number);
EXPORT_PER_CPU_SYMBOL(cpu_number);

// file: archar/m64/mm/fault.c

void do_el0_irq_bp_hardening(void)
{
    printk("!!!!!!!!!!!!! do_el0_irq_bp_hardening stub\n");
    while (1) {
    }
}

// file: arch/arm64/mm/mmu.c

u64 idmap_t0sz = TCR_T0SZ(VA_BITS_MIN);
u64 idmap_ptrs_per_pgd = PTRS_PER_PGD;

u64 __section(".mmuoff.data.write") vabits_actual;
EXPORT_SYMBOL(vabits_actual);

u64 kimage_voffset __ro_after_init;
EXPORT_SYMBOL(kimage_voffset);

// file: arch/arm64/kernel/cpufeature.c

DEFINE_STATIC_KEY_FALSE(arm64_const_caps_ready);
EXPORT_SYMBOL(arm64_const_caps_ready);

DEFINE_STATIC_KEY_ARRAY_FALSE(cpu_hwcap_keys, ARM64_NCAPS);
EXPORT_SYMBOL(cpu_hwcap_keys);

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

// file: arch/arm64/kernel/entry-common.c

asmlinkage void noinstr exit_to_user_mode(void)
{
    printk("!!!!!!!!!!!!! exit_to_user_mode stub\n");
    while (1) {
    }
}

asmlinkage void noinstr enter_from_user_mode(void)
{
    printk("!!!!!!!!!!!!! enter_from_user_mode stub\n");
    while (1) {
    }
}

asmlinkage void noinstr el0_sync_handler(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! el0_sync_handler stub\n");
    while (1) {
    }
}

asmlinkage void noinstr el1_sync_handler(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! el1_sync_handler stub\n");
    while (1) {
    }
}

asmlinkage void noinstr enter_el1_irq_or_nmi(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! enter_el1_irq_or_nmi stub\n");
    while (1) {
    }
}

asmlinkage void noinstr exit_el1_irq_or_nmi(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! exit_el1_irq_or_nmi stub\n");
    while (1) {
    }
}

#ifdef CONFIG_COMPAT

asmlinkage void noinstr el0_sync_compat_handler(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! el0_sync_compat_handler stub\n");
    while (1) {
    }
}

#endif

// file: arch/arm64/kernel/irq.c

DEFINE_PER_CPU(unsigned long *, irq_stack_ptr);

// file: arch/arm64/kernel/proton-pack.c

/* This is the per-cpu state tracking whether we need to talk to firmware */
DEFINE_PER_CPU_READ_MOSTLY(u64, arm64_ssbd_callback_required);

/*
 * Patch a branch over the Spectre-v4 mitigation code with a NOP so that
 * we fallthrough and check whether firmware needs to be called on this CPU.
 */
void __init spectre_v4_patch_fw_mitigation_enable(struct alt_instr *alt,
						  __le32 *origptr,
						  __le32 *updptr, int nr_inst)
{
    printk("!!!!!!!!!!!!! sepctre_v4_patch_fw_mitigation_enable stub\n");
    while (1) {
    }
}

/*
 * Patch a NOP in the Spectre-v4 mitigation code with an SMC/HVC instruction
 * to call into firmware to adjust the mitigation state.
 */
void __init spectre_v4_patch_fw_mitigation_conduit(struct alt_instr *alt,
						   __le32 *origptr,
						   __le32 *updptr, int nr_inst)
{
    printk("!!!!!!!!!!!!! spectre_v4_patch_fw_mitigation_conduit stub\n");
    while (1) {
    }
}

// file: arch/arm64/kernel/smp_spin_table.c

volatile unsigned long __section(".mmuoff.data.read")
secondary_holding_pen_release = INVALID_HWID;

// file: arch/arm64/kernel/process.c

/*
 * We store our current task in sp_el0, which is clobbered by userspace. Keep a
 * shadow copy so that we can restore this upon entry from userspace.
 *
 * This is *only* for exception entry from EL0, and is not valid until we
 * __switch_to() a user task.
 */
DEFINE_PER_CPU(struct task_struct *, __entry_task);

// file: arch/arm64/kernel/signal.c

asmlinkage void do_notify_resume(struct pt_regs *regs,
				 unsigned long thread_flags)
{
    printk("!!!!!!!!!!!!! do_notify_resume stub\n");
    while (1) {
    }
}

asmlinkage void __sched arm64_preempt_schedule_irq(void)
{
    printk("!!!!!!!!!!!!! arm64_preempt_schedule_irq stub\n");
    while (1) {
    }
}

// file: arch/arm64/kernel/smp.c

struct secondary_data secondary_data;

asmlinkage notrace void secondary_start_kernel(void)
{
    printk("!!!!!!!!!!!!! secondary_start_kernel stub\n");
    while (1) {
    }
}

// file: arch/arm64/kernel/traps.c

#ifdef CONFIG_VMAP_STACK

DEFINE_PER_CPU(unsigned long [OVERFLOW_STACK_SIZE/sizeof(long)], overflow_stack)
	__aligned(16);

#endif

asmlinkage void noinstr do_serror(struct pt_regs *regs, unsigned int esr)
{
    printk("!!!!!!!!!!!!! do_serror stub\n");
    while (1) {
    }
}

/*
 * bad_mode handles the impossible case in the vectors.  If you see one of
 * these, then it's extremely serious, and could mean you have buggy hardware.
 * It never returns, and never tries to sync.  We hope that we can at least
 * dump out some state information...
 */
asmlinkage void bad_mode(struct pt_regs *regs, int reason)
{
    printk("!!!!!!!!!!!!! bad_mode stub\n");
    while (1) {
    }
}

asmlinkage void noinstr handle_bad_stack(struct pt_regs *regs)
{
    printk("!!!!!!!!!!!!! handle_bad_stack stub\n");
    while (1) {
    }
}

// file: arch/arm64/kvm/va_layout.c

void kvm_patch_vector_branch(struct alt_instr *alt,
			     __le32 *origptr, __le32 *updptr, int nr_inst)
{
    printk("!!!!!!!!!!!!! preempt_count_add stub\n");
    while (1) {
    }
}

void arm64_skip_faulting_instruction(struct pt_regs *regs, unsigned long size)
{
    printk("!!!!!!!!!!!!! preempt_count_add stub\n");
    while (1) {
    }
}

// file: arch/arm64/kvm/hyp/nvhe/switch.c

/* Non-VHE specific context */
DEFINE_PER_CPU(struct kvm_host_data, __kvm_nvhe_kvm_host_data);
DEFINE_PER_CPU(struct kvm_cpu_context, __kvm_nvhe_kvm_hyp_ctxt);

asmlinkage void __kvm_nvhe_kvm_unexpected_el2_exception(void)
{
    printk("!!!!!!!!!!!!! kvm_unexpected_el2_exception stub\n");
    while (1) {
    }
}

void __noreturn __kvm_nvhe_hyp_panic(void)
{
    printk("!!!!!!!!!!!!! hyp_panic stub\n");
    while (1) {
    }
}

// file: arch/arm64/kvm/hyp/vhe/switch.c

/* VHE specific context */
DEFINE_PER_CPU(struct kvm_host_data, kvm_host_data);
DEFINE_PER_CPU(struct kvm_cpu_context, kvm_hyp_ctxt);

asmlinkage void kvm_unexpected_el2_exception(void)
{
    printk("!!!!!!!!!!!!! kvm_unexpected_el2_exception stub\n");
    while (1) {
    }
}

void __noreturn hyp_panic(void)
{
    printk("!!!!!!!!!!!!! hyp_panic stub\n");
    while (1) {
    }
}

// file: kernel/cpu.c

#ifdef CONFIG_INIT_ALL_POSSIBLE
struct cpumask __cpu_possible_mask __read_mostly
	= {CPU_BITS_ALL};
#else
struct cpumask __cpu_possible_mask __read_mostly;
#endif
EXPORT_SYMBOL(__cpu_possible_mask);

struct cpumask __cpu_online_mask __read_mostly;
EXPORT_SYMBOL(__cpu_online_mask);

struct cpumask __cpu_present_mask __read_mostly;
EXPORT_SYMBOL(__cpu_present_mask);

struct cpumask __cpu_active_mask __read_mostly;
EXPORT_SYMBOL(__cpu_active_mask);

atomic_t __num_online_cpus __read_mostly;
EXPORT_SYMBOL(__num_online_cpus);

#ifdef CONFIG_SMP
int __boot_cpu_id;
#endif

void set_cpu_online(unsigned int cpu, bool online)
{
	/*
	 * atomic_inc/dec() is required to handle the horrid abuse of this
	 * function by the reboot and kexec code which invoke it from
	 * IPI/NMI broadcasts when shutting down CPUs. Invocation from
	 * regular CPU hotplug is properly serialized.
	 *
	 * Note, that the fact that __num_online_cpus is of type atomic_t
	 * does not protect readers which are not serialized against
	 * concurrent hotplug operations.
	 */
	if (online) {
		if (!cpumask_test_and_set_cpu(cpu, &__cpu_online_mask))
			atomic_inc(&__num_online_cpus);
	} else {
		if (cpumask_test_and_clear_cpu(cpu, &__cpu_online_mask))
			atomic_dec(&__num_online_cpus);
	}
}

/*
 * Activate the first processor.
 */
void __init boot_cpu_init(void)
{
	int cpu = smp_processor_id();

	/* Mark the boot cpu "present", "online" etc for SMP and UP case */
	set_cpu_online(cpu, true);
	set_cpu_active(cpu, true);
	set_cpu_present(cpu, true);
	set_cpu_possible(cpu, true);

#ifdef CONFIG_SMP
	__boot_cpu_id = cpu;
#endif
}

// file: kernel/fork.c

void set_task_stack_end_magic(struct task_struct *tsk)
{
	unsigned long *stackend;

	stackend = end_of_stack(tsk);
	*stackend = STACK_END_MAGIC;	/* for overflow detection */
}

// file: kernel/panic.c

#ifdef CONFIG_STACKPROTECTOR

/*
 * Called when gcc's -fstack-protector feature is used, and
 * gcc detects corruption of the on-stack canary value
 */
__visible noinstr void __stack_chk_fail(void)
{
    while (1) {
    }
}

#endif

// file: kernel/printk/printk.c

int __printk_ratelimit(const char *func)
{
	return 0;
}
EXPORT_SYMBOL(__printk_ratelimit);

// file: init/init_task.c

struct task_struct init_task
#ifdef CONFIG_ARCH_TASK_STRUCT_ON_STACK
	__init_task_data
#endif
	__aligned(L1_CACHE_BYTES)
= {
#ifdef CONFIG_THREAD_INFO_IN_TASK
	.thread_info	= INIT_THREAD_INFO(init_task),
	.stack_refcount	= REFCOUNT_INIT(1),
#endif
    .state		= 0,
	.stack		= init_stack,
	.usage		= REFCOUNT_INIT(2),
	.flags		= PF_KTHREAD,
	.prio		= MAX_PRIO - 20,
	.static_prio	= MAX_PRIO - 20,
	.normal_prio	= MAX_PRIO - 20,
	.policy		= SCHED_NORMAL,
	.cpus_ptr	= &init_task.cpus_mask,
	.cpus_mask	= CPU_MASK_ALL,
	.nr_cpus_allowed= NR_CPUS,
	.mm		= NULL,
};

/*
 * Initial thread structure. Alignment of this is handled by a special
 * linker map entry.
 */
#ifndef CONFIG_THREAD_INFO_IN_TASK
struct thread_info init_thread_info __init_thread_info = INIT_THREAD_INFO(init_task);
#endif

// file: kernel/irq/handle.c

#ifdef CONFIG_GENERIC_IRQ_MULTI_HANDLER
void (*handle_arch_irq)(struct pt_regs *) __ro_after_init;
#endif


// file: kernel/sched/core.c

/**
 * schedule_tail - first thing a freshly forked thread must call.
 * @prev: the thread we just switched away from.
 */
asmlinkage __visible void schedule_tail(struct task_struct *prev)
	__releases(rq->lock)
{
    printk("!!!!!!!!!!!!! schedule_tail stub\n");
    while (1) {
    }
}

void preempt_count_add(int val)
{
    printk("!!!!!!!!!!!!! preempt_count_add stub\n");
    while (1) {
    }
}

void preempt_count_sub(int val)
{
    printk("!!!!!!!!!!!!! preempt_count_sub stub\n");
    while (1) {
    }
}

#ifdef CONFIG_PREEMPTION
/*
 * This is the entry point to schedule() from in-kernel preemption
 * off of preempt_enable.
 */
asmlinkage __visible void __sched notrace preempt_schedule(void)
{
    printk("!!!!!!!!!!!!! preempt_schedule stub\n");
    while (1) {
    }
}

#endif

// file: kernel/trace/trace_preemptirq.c

void trace_hardirqs_on(void)
{
    printk("!!!!!!!!!!!!! trace_hardirqs_on stub\n");
    while (1) {
    }
}

void trace_hardirqs_off(void)
{
    printk("!!!!!!!!!!!!! trace_hardirqs_off stub\n");
    while (1) {
    }
}

// file: kernel/cgroup/cgroup.c

int __init cgroup_init_early(void)
{
    return 0;
}

// file: drivers/irqchip/irq-gic-v3.c

DEFINE_STATIC_KEY_FALSE(gic_nonsecure_priorities);
EXPORT_SYMBOL(gic_nonsecure_priorities);

// file: lib/dump_stack.c

#ifdef CONFIG_SMP
asmlinkage __visible void dump_stack(void)
{
    printk("!!!!!!!!!!!!! dump_stack stub\n");
    while (1) {
    }
}
#endif

// file: init/version.c

/* FIXED STRINGS! Don't touch! */
const char linux_banner[] =
	"Linux version " UTS_RELEASE " (" LINUX_COMPILE_BY "@"
	LINUX_COMPILE_HOST ") (" LINUX_COMPILER ") " UTS_VERSION "\n";

// file: kernel/user.c

/*
 * userns count is 1 for root user, 1 for init_uts_ns,
 * and 1 for... ?
 */
struct user_namespace init_user_ns = {
	.uid_map = {
		.nr_extents = 1,
		{
			.extent[0] = {
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			},
		},
	},
	.gid_map = {
		.nr_extents = 1,
		{
			.extent[0] = {
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			},
		},
	},
	.projid_map = {
		.nr_extents = 1,
		{
			.extent[0] = {
				.first = 0,
				.lower_first = 0,
				.count = 4294967295U,
			},
		},
	},
	.count = ATOMIC_INIT(3),
	.owner = GLOBAL_ROOT_UID,
	.group = GLOBAL_ROOT_GID,
	.ns.inum = PROC_USER_INIT_INO,
#ifdef CONFIG_USER_NS
	.ns.ops = &userns_operations,
#endif
	.flags = USERNS_INIT_FLAGS,
#ifdef CONFIG_KEYS
	.keyring_name_list = LIST_HEAD_INIT(init_user_ns.keyring_name_list),
	.keyring_sem = __RWSEM_INITIALIZER(init_user_ns.keyring_sem),
#endif
};
EXPORT_SYMBOL_GPL(init_user_ns);

// kernel/user_namespace.c

const struct proc_ns_operations userns_operations = {
	.name		= "user",
	.type		= CLONE_NEWUSER,
	.get		= NULL,
	.put		= NULL,
	.install	= NULL,
	.owner		= NULL,
	.get_parent	= NULL,
};
