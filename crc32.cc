// x86
//

void	crc32q() {
#if defined(__x86_64__)
	asm volatile(
			"crc32q %[buf], %[crc]\n\t"
			:[crc]"=r"(crc64)
			:"0"(crc64), [buf]"r"(*p)
	);
#elif __aarch64__
	asm volatile(
			"crc32cx %w[c], %w[c], %x[v]"
			:[c]"=r"(crc64)
			:"0"(crc64), [v]"r"(*p)
	);
#elif __loongarch__
	asm volatile(
			"crcc.w.d.w %0, %1, %0\n\t"
			: "+r" (crc64)
			: "r" (*p)
			: "memory"
	);
#else
	#error "Unknown Architecture"
#endif
}


void crc32b() {
#if defined(__x86_64__)
	asm volatile(
			"crc32b %[buf], %[crc]\n\t"
			:[crc]"=r"(crc)
			:"0"(crc), [buf]"r"(*buf)
	);
#elif __aarch64__
	asm volatile(
			"crc32cb %w[c], %w[c], %w[v]"
			:[c]"=r"(crc)
			:"0"(crc), [v]"r"(*buf)
	);
#elif __loongarch__
	asm volatile(
			"crcc.w.b.w %0, %1, %0\n\t"
			: "+r" (crc)
			: "r" (*buf)
			: "memory"
	);
#else
	#error "Unknown Architecture"
#endif
}

void xchg() {
#if defined(__x86_64__)
	static const uint32_t k_SSE4_2 = (1 << 20);
	int level = 1;
	uint64_t a, b, c, d;
	asm (
			"xchg %%rbx, %1\n\t"
			"cpuid\n\t"
			"xchg %%rbx, %1\n\t"
			:"=a"(a), "=r"(b), "=c"(c), "=d"(d)
			:"0"(level));
	return (c & k_SSE4_2) ? &CRCUtil::ComputeCRC32_Accelerate : &CRCUtil::ComputeCRC32_Lookup;
#elif __aarch64__
	// TODO(xuxunzhi) check if processor support crrc32 instruction
	return &CRCUtil::ComputeCRC32_Accelerate;
#elif __loongarch__
	return &CRCUtil::ComputeCRC32_Accelerate;
#else
	return &CRCUtil::ComputeCRC32_Lookup;
#endif
}
