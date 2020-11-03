/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

// a remplir

#define vec_left1(v0, v1)  _mm_shuffle_ps(_mm_shuffle_ps(v0,v1,_MM_SHUFFLE(1,0,3,2)),v1,_MM_SHUFFLE(2,1,2,1))
#define vec_left2(v0, v1)  _mm_shuffle_ps(v0,v1,_MM_SHUFFLE(1,0,3,2))
#define vec_left3(v0, v1)  _mm_shuffle_ps(_mm_shuffle_ps(v0,v1,_MM_SHUFFLE(1,0,3,2)),v0,_MM_SHUFFLE(2,1,2,1))
#define vec_left4(v0, v1)  v1

#define vec_right1(v1, v2) _mm_shuffle_ps(v1,_mm_shuffle_ps(v1,v2,_MM_SHUFFLE(1,0,3,2)),_MM_SHUFFLE(2,1,2,1))
#define vec_right2(v1, v2) _mm_shuffle_ps(v1,v2,_MM_SHUFFLE(1,0,3,2))
#define vec_right3(v1, v2) _mm_shuffle_ps(_mm_shuffle_ps(v1,v2,_MM_SHUFFLE(1,0,3,2)),v2,_MM_SHUFFLE(2,1,2,1))
#define vec_right4(v1, v2) v2


// calculs
#define vec_div3(x) _mm_mul_ps(x,_mm_set_ps(0.333333f,0.333333f,0.333333f,0.333333f))
#define vec_div5(x) _mm_mul_ps(x,_mm_set_ps(0.2f,0.2f,0.2f,0.2f))

#define vec_add3(x0, x1, x2) _mm_add_ps(x0,_mm_add_ps(x1,x2))
#define vec_add5(x0, x1, x2, x3, x4) _mm_add_ps(x0,_mm_add_ps(x1,_mm_add_ps(x2,_mm_add_ps(x3,x4))))
#define vec_add9(x0,x1,x2,x3,x4,x5,x6,x7,x8) vec_add3(vec_add3(x0,x1,x2),vec_add3(x3,x4,x5),vec_add3(x6,x7,x8))

#define vAVERAGE3(x0,x1,x2) vec_div3(vec_add3(x0,x1,x2))
#define vAVERAGE5(x0,x1,x2,x3,x4) vec_div5(vec_add5(x0,x1,x2,x3,x4))

#endif // __SIMD_MACRO_H__
