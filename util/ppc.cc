#include "util/ppc.h"
//#include "util/probe.h"

/* flags we export */
int arch_ppc_crc32 = 0;

#include <stdio.h>
#include <sys/auxv.h>

#if __linux__

#include <elf.h>
#include <link.h> // ElfW macro

#ifndef PPC_FEATURE2_VEC_CRYPTO
#define PPC_FEATURE2_VEC_CRYPTO         0x02000000
#endif

#ifndef AT_HWCAP2
#define AT_HWCAP2       26
#endif

static unsigned long get_auxval(unsigned long type)
{
	unsigned long result = 0;
	int read = 0;
	FILE *f = fopen("/proc/self/auxv", "r");
	if (f) {
		ElfW(auxv_t) entry;
		while ((read = fread(&entry, sizeof(entry), 1, f)) > 0) {
			if (read != 1)
				break;
			if (entry.a_type == type) {
				result = entry.a_un.a_val;
				break;
			}
		}
		fclose(f);
	}
	return result;
}


int arch_ppc_probe(void)
{
        arch_ppc_crc32 = 0;
#if defined(__linux__) && defined(__powerpc64__)
        if (get_auxval(AT_HWCAP2) & PPC_FEATURE2_VEC_CRYPTO) arch_ppc_crc32 = 1;
#endif
	return arch_ppc_crc32;
}
#endif // __linux__

