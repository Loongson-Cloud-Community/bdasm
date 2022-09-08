#define seqlock_mfence() {__asm__ __volatile ("mfence" ::: "memory");}
#define seqlock_lfence() {__asm__ __volatile ("lfence" ::: "memory");}
#define seqlock_sfence() {__asm__ __volatile ("sfence" ::: "memory");}

//loongarch64代码如下
#define seqlock_mfence() {__asm__ __volatile ("dbar 0" ::: "memory");}
#define seqlock_lfence() {__asm__ __volatile ("dbar 0" ::: "memory");}
#define seqlock_sfence() {__asm__ __volatile ("dbar 0" ::: "memory");}


static inline void cpu_relax() {
	asm volatile("rep; nop" ::: "memory");
}
// loongarch64 代码如下
static inline void cpu_relax() {
	asm volatile("dbar 0" ::: "memory");
}
