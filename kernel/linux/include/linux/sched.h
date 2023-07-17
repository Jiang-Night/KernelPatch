#ifndef _LINUX_SCHED_H
#define _LINUX_SCHED_H

#include <ktypes.h>
#include <init/ksyms.h>
#include <linux/spinlock.h>
#include <linux/rwlock.h>
#include <linux/pid.h>
#include <linux/init_task.h>

struct task_struct; // __randomize_layout
struct cpumask;
struct sched_param;
struct sched_attr;
struct pid_namespace;

/* Task command name length: */
#define TASK_COMM_LEN 16

extern rwlock_t *kvar(tasklist_lock);
extern spinlock_t *kvar(mmlist_lock);

extern void scheduler_tick(void);

#define MAX_SCHEDULE_TIMEOUT LONG_MAX

extern long schedule_timeout(long timeout);
extern long schedule_timeout_interruptible(long timeout);
extern long schedule_timeout_killable(long timeout);
extern long schedule_timeout_uninterruptible(long timeout);
extern long schedule_timeout_idle(long timeout);
asmlinkage void schedule(void);
extern void schedule_preempt_disabled(void);
asmlinkage void preempt_schedule_irq(void);

extern int __must_check io_schedule_prepare(void);
extern void io_schedule_finish(int token);
extern long io_schedule_timeout(long timeout);
extern void io_schedule(void);

// todo:
struct task_struct_offset
{
    int16_t pid_offset;
    int16_t tgid_offset;
    int16_t thread_pid_offset;
    int16_t ptracer_cred_offset;
    int16_t real_cred_offset;
    int16_t cred_offset;
    int16_t fs_offset;
    int16_t files_offset;
    int16_t loginuid_offset;
    int16_t sessionid_offset;
    int16_t seccomp_offset;
    int16_t security_offset;
    int16_t stack_offset;
};

extern struct task_struct_offset task_struct_offset;

extern struct mm_struct *kvar(init_mm);
extern struct pid_namespace *kvar(init_pid_ns);

extern int cpuset_cpumask_can_shrink(const struct cpumask *cur, const struct cpumask *trial);
extern int task_can_attach(struct task_struct *p, const struct cpumask *cs_effective_cpus);
extern void do_set_cpus_allowed(struct task_struct *p, const struct cpumask *new_mask);
extern int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask);
extern int yield_to(struct task_struct *p, bool preempt);
extern void set_user_nice(struct task_struct *p, long nice);
extern int task_prio(const struct task_struct *p);
extern int can_nice(const struct task_struct *p, const int nice);
extern int task_curr(const struct task_struct *p);
extern int idle_cpu(int cpu);
extern int available_idle_cpu(int cpu);
extern int sched_setscheduler(struct task_struct *, int, const struct sched_param *);
extern int sched_setscheduler_nocheck(struct task_struct *, int, const struct sched_param *);
extern void sched_set_fifo(struct task_struct *p);
extern void sched_set_fifo_low(struct task_struct *p);
extern void sched_set_normal(struct task_struct *p, int nice);
extern int sched_setattr(struct task_struct *, const struct sched_attr *);
extern int sched_setattr_nocheck(struct task_struct *, const struct sched_attr *);
extern struct task_struct *idle_task(int cpu);
extern struct task_struct *curr_task(int cpu);
extern void ia64_set_curr_task(int cpu, struct task_struct *p);
void yield(void);

extern int wake_up_state(struct task_struct *tsk, unsigned int state);
extern int wake_up_process(struct task_struct *tsk);
extern void wake_up_new_task(struct task_struct *tsk);
extern void kick_process(struct task_struct *tsk);
extern void __set_task_comm(struct task_struct *tsk, const char *from, bool exec);
extern unsigned long wait_task_inactive(struct task_struct *, long match_state);

extern pid_t kfunc_def(__task_pid_nr_ns)(struct task_struct *task, enum pid_type type, struct pid_namespace *ns);
extern struct pid_namespace *kfunc_def(task_active_pid_ns)(struct task_struct *tsk);
extern struct task_struct *kfunc_def(find_task_by_vpid)(pid_t nr);
extern struct task_struct *kfunc_def(find_task_by_pid_ns)(pid_t nr, struct pid_namespace *ns);
extern struct task_struct *kfunc_def(find_get_task_by_vpid)(pid_t nr);

static inline pid_t __task_pid_nr_ns(struct task_struct *task, enum pid_type type, struct pid_namespace *ns)
{
    kfunc_call(__task_pid_nr_ns, task, type, ns);
    kfunc_not_found();
    return 0;
}

static inline pid_t task_pid_nr_ns(struct task_struct *tsk, struct pid_namespace *ns)
{
    return __task_pid_nr_ns(tsk, PIDTYPE_PID, ns);
}

static inline pid_t task_pid_vnr(struct task_struct *tsk)
{
    return __task_pid_nr_ns(tsk, PIDTYPE_PID, NULL);
}

static inline struct pid_namespace *task_active_pid_ns(struct task_struct *tsk)
{
    kfunc_call(task_active_pid_ns, tsk);
    kfunc_not_found();
    return 0;
}

static inline struct task_struct *find_task_by_vpid(pid_t nr)
{
    kfunc_call(find_task_by_vpid, nr);
    kfunc_not_found();
    return 0;
}
static inline struct task_struct *find_task_by_pid_ns(pid_t nr, struct pid_namespace *ns)
{
    kfunc_call(find_task_by_pid_ns, nr, ns);
    kfunc_not_found();
    return 0;
}
static inline struct task_struct *find_get_task_by_vpid(pid_t nr)
{
    kfunc_call(find_get_task_by_vpid, nr);
    kfunc_not_found();
    return 0;
}

#endif