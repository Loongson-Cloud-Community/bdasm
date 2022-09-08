void rdtsc() {
#if defined(__x86_64__)
	uint64_t a, d;
	__asm__ volatile("rdtsc" : "=a"(a), "=d"(d));
	return (d << 32) | a;
#else
	return byte::GetCurrentTimeInNs();
#endif
}
