
#ifndef __MACROS_H__
#define __MACROS_H__

// #define left_shift(a,b) _mm_shuffle_ps(_mm_shuffle_ps(a,b,_MM_SHUFFLE(1,0,3,2)),b,_MM_SHUFFLE(2,1,2,1))

// #define right_shift(b,c) _mm_shuffle_ps(b,_mm_shuffle_ps(b,c,_MM_SHUFFLE(1,0,3,2)),_MM_SHUFFLE(2,1,2,1))

// #define fst_shift5(a,b) _mm_shuffle_ps(a,b,_MM_SHUFFLE(1,0,3,2))

// #define snd_shift5(a,b) _mm_shuffle_ps(a,b,_MM_SHUFFLE(2,1,2,1))

#define vec_shuffle(a,b,c,d,e,f) _mm_shuffle_ps(a,b,_MM_SHUFFLE(c,d,e,f))

#define vec_add(a,b) _mm_add_ps(a,b)

#define vec_mul(a,b) _mm_mul_ps(a,b)

#define set(a,b,c,d) _mm_set_ps(a,b,c,d)

#define load(a) _mm_load_ps(a)

#define store(a,b) _mm_store_ps(a,b)

#endif