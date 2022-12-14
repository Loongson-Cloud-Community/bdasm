inline int64_t rdtsc() {
#if defined(__aarch64__)
	uint64_t var;
	asm volatile("mrs %0, CNTVCT_EL0" : "=r"(var));
	return var;
#elif defined(__x86_64__)
	uint32_t __a, __d;
	__asm__ __volatile__("rdtsc" : "=a" (__a), "=d" (__d));
	return (static_cast<uint64_t>(__a)) | (static_cast<uint64_t>(__d) << 32);
#endif
}
