#include "uwrapper.h"
#include "udasics.h"
#include "csr.h"
#include "uattr.h"

uint64_t umaincall_helper = 0;

ATTR_DASICS_LEVEL1 int32_t dasics_ulib_libcfg_alloc(uint64_t cfg, uint64_t lo, uint64_t hi) {
    lo = ROUNDDOWN(lo, 0x8);
    hi = ROUND(hi, 0x8);
    uint64_t libcfg = read_csr(0x880);  // DasicsLibCfg
    int32_t max_cfgs = DASICS_LIBCFG_WIDTH;
    uint64_t mem_bound_status = dasics_ulib_query_bound(TYPE_MEM_BOUND);
    int32_t target_idx,orig_idx;
    for (target_idx= 0; target_idx < max_cfgs; ++target_idx) {
        uint64_t curr_status = (mem_bound_status >> (target_idx * 2)) & 0x3;

        if (curr_status == 0x3){

            // try to find origin libcfg 
            for (orig_idx = 0; orig_idx < max_cfgs; ++orig_idx){
                uint64_t orig_status = (mem_bound_status >> (orig_idx * 2)) & 0x3;
                if (orig_status == 0x1){ // libcfg in the same level
                    uint64_t orig_cfg = (libcfg >> (orig_idx * 4)) & DASICS_LIBCFG_MASK;
                    uint64_t orig_lo,orig_hi;
                    switch (orig_idx) { // read origin libcfg
                    case 0:
                        orig_lo = read_csr(0x890);   // DasicsLibBound0Lo
                        orig_hi = read_csr(0x891);   // DasicsLibBound0Hi
                        break;
                    case 1:
                        orig_lo = read_csr(0x892);   // DasicsLibBound1Lo
                        orig_hi = read_csr(0x893);   // DasicsLibBound1Hi
                        break;
                    case 2:
                        orig_lo = read_csr(0x894);   // DasicsLibBound2Lo
                        orig_hi = read_csr(0x895);   // DasicsLibBound2Hi
                        break;
                    case 3:
                        orig_lo = read_csr(0x896);   // DasicsLibBound3Lo
                        orig_hi = read_csr(0x897);   // DasicsLibBound3Hi
                        break;
                    case 4:
                        orig_lo = read_csr(0x898);   // DasicsLibBound4Lo
                        orig_hi = read_csr(0x899);   // DasicsLibBound4Hi
                        break;
                    case 5:
                        orig_lo = read_csr(0x89a);   // DasicsLibBound5Lo
                        orig_hi = read_csr(0x89b);   // DasicsLibBound5Hi
                        break;
                    case 6:
                        orig_lo = read_csr(0x89c);   // DasicsLibBound6Lo
                        orig_hi = read_csr(0x89d);   // DasicsLibBound6Hi
                        break;
                    case 7:
                        orig_lo = read_csr(0x89e);   // DasicsLibBound7Lo
                        orig_hi = read_csr(0x89f);   // DasicsLibBound7Hi
                        break;
                    case 8:
                        orig_lo = read_csr(0x8a0);   // DasicsLibBound8Lo
                        orig_hi = read_csr(0x8a1);   // DasicsLibBound8Hi
                        break;
                    case 9:
                        orig_lo = read_csr(0x8a2);   // DasicsLibBound9Lo
                        orig_hi = read_csr(0x8a3);   // DasicsLibBound9Hi
                        break;
                    case 10:
                        orig_lo = read_csr(0x8a4);   // DasicsLibBound10Lo
                        orig_hi = read_csr(0x8a5);   // DasicsLibBound10Hi
                        break;
                    case 11:
                        orig_lo = read_csr(0x8a6);   // DasicsLibBound11Lo
                        orig_hi = read_csr(0x8a7);   // DasicsLibBound11Hi
                        break;
                    case 12:
                        orig_lo = read_csr(0x8a8);   // DasicsLibBound12Lo
                        orig_hi = read_csr(0x8a9);   // DasicsLibBound12Hi
                        break;
                    case 13:
                        orig_lo = read_csr(0x8aa);   // DasicsLibBound13Lo
                        orig_hi = read_csr(0x8ab);   // DasicsLibBound13Hi
                        break;
                    case 14:
                        orig_lo = read_csr(0x8ac);   // DasicsLibBound14Lo
                        orig_hi = read_csr(0x8ad);   // DasicsLibBound14Hi
                        break;
                    case 15:
                        orig_lo = read_csr(0x8ae);   // DasicsLibBound15Lo
                        orig_hi = read_csr(0x8af);   // DasicsLibBound15Hi
                        break;
                    default:
                        break;
                    }
                    if (orig_lo <= lo && hi <= orig_hi && !(cfg & ~orig_cfg)) break; // current field smaller than origin, OK
                }
            }
            if (orig_idx == max_cfgs)
            {
                printf("no origin libcfg\n");
                return -1; // no origin libcfg
            }
            dasics_ulib_copy_bound(TYPE_MEM_BOUND,orig_idx,target_idx); // copy origin libcfg to target
            switch (target_idx) { // modify target libcfg according to arg
                case 0:
                    write_csr(0x890, lo);   // DasicsLibBound0Lo
                    write_csr(0x891, hi);   // DasicsLibBound0Hi
                    break;
                case 1:
                    write_csr(0x892, lo);   // DasicsLibBound1Lo
                    write_csr(0x893, hi);   // DasicsLibBound1Hi
                    break;
                case 2:
                    write_csr(0x894, lo);   // DasicsLibBound2Lo
                    write_csr(0x895, hi);   // DasicsLibBound2Hi
                    break;
                case 3:
                    write_csr(0x896, lo);   // DasicsLibBound3Lo
                    write_csr(0x897, hi);   // DasicsLibBound3Hi
                    break;
                case 4:
                    write_csr(0x898, lo);   // DasicsLibBound4Lo
                    write_csr(0x899, hi);   // DasicsLibBound4Hi
                    break;
                case 5:
                    write_csr(0x89a, lo);   // DasicsLibBound5Lo
                    write_csr(0x89b, hi);   // DasicsLibBound5Hi
                    break;
                case 6:
                    write_csr(0x89c, lo);   // DasicsLibBound6Lo
                    write_csr(0x89d, hi);   // DasicsLibBound6Hi
                    break;
                case 7:
                    write_csr(0x89e, lo);   // DasicsLibBound7Lo
                    write_csr(0x89f, hi);   // DasicsLibBound7Hi
                    break;
                case 8:
                    write_csr(0x8a0, lo);   // DasicsLibBound8Lo
                    write_csr(0x8a1, hi);   // DasicsLibBound8Hi
                    break;
                case 9:
                    write_csr(0x8a2, lo);   // DasicsLibBound9Lo
                    write_csr(0x8a3, hi);   // DasicsLibBound9Hi
                    break;
                case 10:
                    write_csr(0x8a4, lo);   // DasicsLibBound10Lo
                    write_csr(0x8a5, hi);   // DasicsLibBound10Hi
                    break;
                case 11:
                    write_csr(0x8a6, lo);   // DasicsLibBound11Lo
                    write_csr(0x8a7, hi);   // DasicsLibBound11Hi
                    break;
                case 12:
                    write_csr(0x8a8, lo);   // DasicsLibBound12Lo
                    write_csr(0x8a9, hi);   // DasicsLibBound12Hi
                    break;
                case 13:
                    write_csr(0x8aa, lo);   // DasicsLibBound13Lo
                    write_csr(0x8ab, hi);   // DasicsLibBound13Hi
                    break;
                case 14:
                    write_csr(0x8ac, lo);   // DasicsLibBound14Lo
                    write_csr(0x8ad, hi);   // DasicsLibBound14Hi
                    break;
                case 15:
                    write_csr(0x8ae, lo);   // DasicsLibBound15Lo
                    write_csr(0x8af, hi);   // DasicsLibBound15Hi
                    break;
                default:
                    break;
            }
            // Write config
            libcfg &= ~(DASICS_LIBCFG_MASK << (target_idx * 4));
            libcfg |= (cfg & DASICS_LIBCFG_MASK) << (target_idx * 4);
            write_csr(0x880, libcfg);   // DasicsLibCfg

            return target_idx;
        }
    }
    printf("failed in alloc\n");
    return -1;
}


ATTR_DASICS_LEVEL1 int32_t dasics_ulib_libcfg_copy(int src_idx) {
    uint64_t libcfg = read_csr(0x880);  // DasicsLibCfg
    int32_t max_cfgs = DASICS_LIBCFG_WIDTH;
    uint64_t mem_bound_status = dasics_ulib_query_bound(TYPE_MEM_BOUND);
    uint64_t src_status = (mem_bound_status >> (src_idx * 2)) & 0x3;
    if (src_status == 0 || src_status == 3) return -1;  // cannot copy
    int32_t target_idx;
    for (target_idx= 0; target_idx < max_cfgs; ++target_idx) {
        uint64_t curr_status = (mem_bound_status >> (target_idx * 2)) & 0x3;

        if (curr_status == 0x3){
            dasics_ulib_copy_bound(TYPE_MEM_BOUND,src_idx,target_idx); // copy origin libcfg to target
            return target_idx;
        }
    }
    return -1;
}

#include <stdio.h>
ATTR_DASICS_LEVEL1 int32_t dasics_ulib_libcfg_free(int32_t idx) {
    uint64_t mem_bound_status = dasics_ulib_query_bound(TYPE_MEM_BOUND);
    if (!(mem_bound_status >> (idx * 2) & 0x3))
    {
        printf("free no permission\n");
         return -1; // no permission
    }

    if (idx < 0 || idx >= DASICS_LIBCFG_WIDTH)
    {
        printf("not bound\n");
         return -1;
    }
    uint64_t libcfg = read_csr(0x880);  // DasicsLibCfg
    libcfg &= ~(DASICS_LIBCFG_MASK << (idx * 4));
    write_csr(0x880, libcfg);   // DasicsLibCfg
    return 0;
}

// uint32_t dasics_libcfg_get(int32_t idx) {
//     if (idx < 0 || idx >= DASICS_LIBCFG_WIDTH) return -1;
//     uint64_t libcfg = read_csr(0x880);  // DasicsLibCfg
//     return (libcfg >> (idx * 4)) & DASICS_LIBCFG_MASK;
// }

ATTR_DASICS_LEVEL1 int32_t dasics_ulib_jumpcfg_alloc(uint64_t lo, uint64_t hi)
{
    lo = ROUNDDOWN(lo, 0x8);
    hi = ROUND(hi, 0x8);    
    uint64_t jumpcfg = read_csr(0x8c8);    // DasicsJumpCfg
    int32_t max_cfgs = DASICS_JUMPCFG_WIDTH;
    uint64_t jmp_bound_status = dasics_ulib_query_bound(TYPE_JMP_BOUND);
    int32_t target_idx,orig_idx;
    for (target_idx = 0; target_idx < max_cfgs; ++target_idx) {
        uint64_t curr_status = (jmp_bound_status >> (target_idx * 2)) & 0x3;
        if (curr_status == 0x3) // found available cfg
        {
            // try to find origin jmpcfg 
            for (orig_idx = 0; orig_idx < max_cfgs; ++orig_idx){
                uint64_t orig_status = (jmp_bound_status >> (orig_idx * 2)) & 0x3;
                if (orig_status == 0x1){ // jmpcfg in the same level
                    uint64_t orig_lo,orig_hi;
                    switch (orig_idx) { // read origin jmpcfg
                        case 0:
                            orig_lo = read_csr(0x8c0);  // DasicsJumpBound0Lo
                            orig_hi = read_csr(0x8c1);  // DasicsJumpBound0Hi
                            break;
                        case 1:
                            orig_lo = read_csr(0x8c2);  // DasicsJumpBound1Lo
                            orig_hi = read_csr(0x8c3);  // DasicsJumpBound1Hi
                            break;
                        case 2:
                            orig_lo = read_csr(0x8c4);  // DasicsJumpBound2Lo
                            orig_hi = read_csr(0x8c5);  // DasicsJumpBound2Hi
                            break;
                        case 3:
                            orig_lo = read_csr(0x8c6);  // DasicsJumpBound3Lo
                            orig_hi = read_csr(0x8c7);  // DasicsJumpBound3Hi
                            break;
                        default:
                            break;
                    }
                    if (orig_lo <= lo && hi <= orig_hi) break; // current field smaller than origin, OK
                }
            }
            if (orig_idx == max_cfgs) return -1; // no origin jmpcfg
            dasics_ulib_copy_bound(TYPE_JMP_BOUND,orig_idx,31); // copy origin jmpcfg to scratchpad
            write_csr(0x8d2, lo);  // scratchpad_lo
            write_csr(0x8d3, hi);  // scratchpad_hi
            dasics_ulib_copy_bound(TYPE_JMP_BOUND,31,target_idx); // copy scratchpad to target jmpcfg

            jumpcfg &= ~(DASICS_JUMPCFG_MASK << (target_idx * 16));
            jumpcfg |= DASICS_JUMPCFG_V << (target_idx * 16);
            write_csr(0x8c8, jumpcfg); // DasicsJumpCfg
            return target_idx;
        }
    }
    return -1;
}

ATTR_DASICS_LEVEL1 int32_t dasics_ulib_jumpcfg_free(int32_t idx) {
    uint64_t jmp_bound_status = dasics_ulib_query_bound(TYPE_JMP_BOUND);
    if (!(jmp_bound_status >> (idx * 2) & 0x3)) return -1; // no permission
    
    if (idx < 0 || idx >= DASICS_JUMPCFG_WIDTH) return -1;
    uint64_t jumpcfg = read_csr(0x8c8);    // DasicsJumpCfg
    jumpcfg &= ~(DASICS_JUMPCFG_V << (idx * 16));
    write_csr(0x8c8, jumpcfg); // DasicsJumpCfg
    return 0;
}