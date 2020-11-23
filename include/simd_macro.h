/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

//chargements

#define vec_store(adr, vec) _mm_store_si128(adr, vec)
#define vec_load(adr) _mm_load_si128(adr)

//Operations sur bit

#define vec_and(a, b)   _mm_and_si128(a, b)
#define vec_andnot(a, b) _mm_andnot_si128(a, b)
#define vec_or(a, b)    _mm_or_si128(a, b)
#define vec_add(a, b)   _mm_add_epi8(a, b)
#define vec_sub(a, b)   _mm_sub_epi8(a, b)
#define vec_gt(a, b)    _mm_cmpgt_epi8(a, b)
#define vec_lt(a, b)    _mm_cmplt_epi8(a, b)
#define vec_eq(a, b)    _mm_cmpeq_epi8(a, b)
#define vec_max(a, b)   _mm_max_epu8(a, b)
#define vec_min(a, b)   _mm_min_epu8(a, b)

// shifts

#define vec_sll(v, n)   _mm_bslli_si128(v, n)
#define vec_srl(v, n)   _mm_bsrli_si128(v, n)
#define vec_left1(v0, v1)  vec_add(vec_srl(v0, 15), vec_sll(v1, 1))
#define vec_left2(v0, v1)  vec_add(vec_srl(v0, 14), vec_sll(v1, 2))
#define vec_left3(v0, v1)  vec_add(vec_srl(v0, 13), vec_sll(v1, 3))
#define vec_left4(v0, v1)  vec_add(vec_srl(v0, 12), vec_sll(v1, 4))

#define vec_right1(v1, v2) vec_add(vec_srl(v1, 1), vec_sll(v2, 15))
#define vec_right2(v1, v2) vec_add(vec_srl(v1, 2), vec_sll(v2, 14))
#define vec_right3(v1, v2) vec_add(vec_srl(v1, 3), vec_sll(v2, 13))
#define vec_right4(v1, v2) vec_add(vec_srl(v1, 4), vec_sll(v2, 12))


// calculs
#define vec_div3(x) x
#define vec_div5(x) x

#define vec_add3(x0, x1, x2) _mm_add_ps(_mm_add_ps(x0, x1), x2)
#define vec_add5(x0, x1, x2, x3, x4) vec_add3(vec_add3(x0, x1, x2), x3, x4)


#define vAVERAGE3(x0,x1,x2) x0
#define vAVERAGE5(x0,x1,x2,x3,x4) x0

#endif // __SIMD_MACRO_H__
