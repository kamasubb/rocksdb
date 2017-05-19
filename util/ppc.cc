/* Copyright (C) 2017 International Business Machines Corp.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "util/ppc.h"

/* flags we export */
int arch_ppc_crc32 = 0;

#if __linux__ && __powerpc64__
#include <stdio.h>
#include <sys/auxv.h>
#endif /* __linux__ && __powerpc64__ */

#if __linux__

#ifndef PPC_FEATURE2_VEC_CRYPTO
#define PPC_FEATURE2_VEC_CRYPTO         0x02000000
#endif

#ifndef AT_HWCAP2
#define AT_HWCAP2       26
#endif

int arch_ppc_probe(void)
{
  arch_ppc_crc32 = 0;

#if defined(__linux__) && defined(__powerpc64__)
  if (getauxval(AT_HWCAP2) & PPC_FEATURE2_VEC_CRYPTO) arch_ppc_crc32 = 1;
#endif /* __linux__ && __powerpc64__ */
        
  return arch_ppc_crc32;
}
#endif // __linux__

