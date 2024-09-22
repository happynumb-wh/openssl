#ifndef _OPENSSL_UWRAPPER_UDASICS_H
#define _OPENSSL_UWRAPPER_UDASICS_H
#include <stdint.h>

#define DASICS_HOOK_FUNC_MAGIC 0x66668888

extern void * dasics_ulib_libcall(void *arg0, void *arg1, void *arg2, void *arg3, void * arg4, void * arg5, void *arg6, void *func_name);
#define dasics_ulib_libcall_no_args(func_name) (dasics_ulib_libcall(0, 0, 0, 0, 0, 0, 0, func_name))


extern void * dasics_umain_call(uint64_t dasics_hook_flag, void * ptr, void * arg0,  void * arg1, void * arg2,  void * arg3, void * arg4,  void * arg5);
extern void dasics_ulib_copy_mem_bound(int bound_src, int bound_dst);
extern void dasics_ulib_copy_jmp_bound(int bound_src, int bound_dst);
extern uint64_t dasics_ulib_query_mem_bound(void);
extern uint64_t dasics_ulib_query_jmp_bound(void);
int32_t dasics_ulib_libcfg_copy(int src_idx);


#define dasics_ulib_copy_bound(type,bound_src,bound_dst) ((type)?\
                                                    dasics_ulib_copy_jmp_bound(bound_src, bound_dst):\
                                                    dasics_ulib_copy_mem_bound(bound_src, bound_dst))
#define dasics_ulib_query_bound(type) ((type)?\
                                  dasics_ulib_query_jmp_bound():\
                                  dasics_ulib_query_mem_bound())


#endif