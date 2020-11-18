#include "test_mouvement_SIMD.h"


void test_fct_vi8max_OK(){
    vuint8 min = init_vuint8(VMIN);
    vuint8 a = init_vuint8_all(1,1,0,1,1,1,0,1,1,-1,1,1,1,1,1,-1);

    vuint8 attendu = init_vuint8_all(1,1,VMIN,1,1,1,VMIN,1,1,VMIN,1,1,1,1,1,VMIN);
    vuint8 test = vi8_max(a, min);
    vuint8 test_2 = vi8_max(min, a);

    display_vuint8(test, "%d  ", "test : ");
    printf("\n");

    display_vuint8(test_2, "%d  ", "test 2 : ");
    printf("\n");


    display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
    printf("\n");
}

void test_fct_vi8max_OK_2(){

}

void test_fct_vi8min_OK(){
    vuint8 max = init_vuint8(240);
    vuint8 a = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);

    vuint8 attendu = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);
    vuint8 test = vi8_min(a, max);
    vuint8 test_2 = vi8_min(max, a);

    vuint8 test_3 = _mm_min_epu8(a, max);
    vuint8 test_4 = _mm_min_epu8(a, max);

    display_vuint8(test, "%d  ", "test : ");
    printf("\n");

    display_vuint8(test_2, "%d  ", "test 2 : ");
    printf("\n");

    display_vuint8(test_3, "%d  ", "test 3 : ");
    printf("\n");

    display_vuint8(test_4, "%d  ", "test 4 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_3), "%d  ", "attendu 3 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_4), "%d  ", "attendu 4 : ");
    printf("\n");
}

void test_fct_vi8min_vi8max_OK(){
}

void test_vec_and(){
    vuint8 FF = init_vuint8(255);
    vuint8 a = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);

    vuint8 attendu = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);
    vuint8 test = vec_and(a, FF);
    vuint8 test_2 = vec_and(FF, a);

    display_vuint8(test, "%d  ", "test : ");
    printf("\n");

    display_vuint8(test_2, "%d  ", "test 2 : ");
    printf("\n");


    display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
    printf("\n");
}
