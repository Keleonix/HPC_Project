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

#define vec_left1(v0, v1)  _mm_shuffle_ps(_mm_shuffle_ps(v0, v1, _MM_SHUFFLE(0, 0, 3, 3)), v1, _MM_SHUFFLE(2, 1, 3, 0));
#define vec_left2(v0, v1)  _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(1, 0, 3, 2));
#define vec_left3(v0, v1)  _mm_shuffle_ps(v0, _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(0,0,3,3)), _MM_SHUFFLE(2, 1, 3, 0));
#define vec_left4(v0, v1)  _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(3, 2, 1, 0));

#define vec_right1(v1, v2) _mm_shuffle_ps(v1, _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(0,0,3,3)), _MM_SHUFFLE(3, 0, 2, 1));
#define vec_right2(v1, v2) _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1, 0, 3, 2));
#define vec_right3(v1, v2) _mm_shuffle_ps(_mm_shuffle_ps(v1, v2, _MM_SHUFFLE(0, 0, 3, 3)), v2, _MM_SHUFFLE(3, 0, 2, 1));
#define vec_right4(v1, v2) _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 2, 1, 0));


// calculs
#define vec_div3(x) x
#define vec_div5(x) x

#define vec_add3(x0, x1, x2) _mm_add_ps(_mm_add_ps(x0, x1), x2)
#define vec_add5(x0, x1, x2, x3, x4) vec_add3(vec_add3(x0, x1, x2), x3, x4)


#define vAVERAGE3(x0,x1,x2) x0
#define vAVERAGE5(x0,x1,x2,x3,x4) x0

#endif // __SIMD_MACRO_H__
