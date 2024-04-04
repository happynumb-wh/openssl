#ifndef _OPENSSL_SSL_UDASICS_H
#define _OPENSSL_SSL_UDASICS_H

#define DASICS_LIBCFG_WIDTH 16
#define DASICS_LIBCFG_MASK  0xfUL
#define DASICS_LIBCFG_V     0x8UL
#define DASICS_LIBCFG_R     0x2UL
#define DASICS_LIBCFG_W     0x1UL

#define DASICS_JUMPCFG_WIDTH 4
#define DASICS_JUMPCFG_MASK 0xffffUL
#define DASICS_JUMPCFG_V    0x1UL


#define TYPE_MEM_BOUND 0
#define TYPE_JMP_BOUND 1


int32_t  dasics_ulib_libcfg_alloc(uint64_t cfg, uint64_t lo ,uint64_t hi);
int32_t  dasics_ulib_libcfg_free(int32_t idx);
int32_t  dasics_ulib_jumpcfg_alloc(uint64_t lo, uint64_t hi);
int32_t  dasics_ulib_jumpcfg_free(int32_t idx);

#endif