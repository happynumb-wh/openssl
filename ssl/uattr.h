#ifndef _SSL_UATTR_H
#define _SSL_UATTR_H


#include <stdint.h>

#define PAGE_SIZE 0x1000


extern uint64_t  __dasics_level1_ssl_begin[];
extern uint64_t  __dasics_level1_ssl_end[];

extern uint64_t  __dasics_level2_ssl_begin[];
extern uint64_t  __dasics_level2_ssl_end[];

extern uint64_t  __dasics_level3_ssl_begin[];
extern uint64_t  __dasics_level3_ssl_end[];

extern uint64_t  __openssl_got_begin[];
extern uint64_t  __openssl_got_end[];
// self heap
extern void * openssl_self_heap;
extern uint64_t openssl_malloc_size;
extern uint64_t openssl_full_size;

extern uint64_t umaincall_helper;

#define ATTR_DASICS_LEVEL1 __attribute__((section(".dasics_text.ssldasics_level1")))
#define ATTR_DASICS_LEVEL2 __attribute__((section(".dasics_text.ssldasics_level2")))
#define ATTR_DASICS_LEVEL3 __attribute__((section(".dasics_text.ssldasics_level3")))

#define ROUND(a, n)     (((((uint64_t)(a))+(n)-1)) & ~((n)-1))

#define ROUNDDOWN(a, n) (((uint64_t)(a)) & ~((n)-1))

struct elf_msg
{
   uint64_t _text_start, _text_end;
   uint64_t _plt_start, _plt_end;
   uint64_t _r_start, _r_end;
   uint64_t _w_start, _w_end; 
   uint64_t _map_start, _map_end;
};


extern struct elf_msg openssl_elf;
#endif