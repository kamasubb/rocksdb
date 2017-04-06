/* Copyright (C) 2017 International Business Machines Corp.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#ifndef CEPH_COMMON_CRC32C_PPC_H
#define CEPH_COMMON_CRC32C_PPC_H

#include "util/ppc-opcode.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__powerpc64__)

extern uint32_t crc32c_ppc(uint32_t crc, unsigned char const *buffer, unsigned len);
unsigned int __crc32_vpmsum(unsigned int crc, unsigned char const *p,
                            unsigned long len);
#else

static inline uint32_t crc32c_ppc(uint32_t crc, unsigned char const *buffer, unsigned len)
{
	return 0;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
