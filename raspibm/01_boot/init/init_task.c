// SPDX-License-Identifier: GPL-2.0
#include <linux/init_task.h>

/*
 * Set up the first task table, touch at your own risk!. Base=0,
 * limit=0x1fffff (=2MB)
 */
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