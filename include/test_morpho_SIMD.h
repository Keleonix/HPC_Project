#include "morpho_SIMD.h"

#define NB_TESTS_EROSION 7
#define NB_TESTS_DILATATION 7

//TODO: Faire les mêmes tests en changeant avec des valeurs différentes
//TODO: Faire des macros pour chaque matrice pour augmenter le nombre de tests
//unitaires
//On testera l'erosion/dilatation sur une matrice uint8**
void test_erosion_SIMD_1();
void test_erosion_SIMD_2();
void test_erosion_SIMD_3();
void test_erosion_SIMD_4();
void test_erosion_SIMD_5();
void test_erosion_SIMD_6();
void test_erosion_SIMD_7();
void tests_erosion_SIMD();
void test_dilatation_SIMD_1();
void test_dilatation_SIMD_2();
void test_dilatation_SIMD_3();
void test_dilatation_SIMD_4();
void test_dilatation_SIMD_5();
void test_dilatation_SIMD_6();
void test_dilatation_SIMD_7();
void tests_dilatation_SIMD();