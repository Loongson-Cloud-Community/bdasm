void cmpxchag() {
#ifdef __x86_64__
	T ret;
	__asm__ __volatile__("lock; cmpxchg %1, (%2);"
											:"=a"(ret)
											 // GCC may produces %sil or %dil for
											 // constraint "r", but some of apple's gas
											 // dosn't know the 8 bit registers.
											 // We use "q" to avoid these registers.
											:"q"(newval), "q"(ptr), "a"(oldval)
											:"memory", "cc");
	return ret;
#else
	return __sync_val_compare_and_swap(ptr,newval,oldval);
#endif

// loongarch64 可直接使用 else 中的实现 
}
