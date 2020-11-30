#ifndef BENCH_MORPHO_H
#define BENCH_MORPHO_H

#include "morpho.h"
#include "morpho_SIMD.h"
#include "morpho_optim.h"
#include "my_macro.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


#define TEMPS_RESULTATS(t, t_min, t_max, t_somme) \
        t_min = MIN(t_min, t); \
        t_max = MAX(t_max, t); \
        t_somme += timer_step1;

void chrono_erosion();
void chrono_erosion_SIMD();
void chrono_erosion_OPTIM();

void chrono_dilatation();
void chrono_dilatation_SIMD();
void chrono_dilatation_OPTIM();

void chrono_ouverture();
void chrono_ouverture_SIMD();
void chrono_ouverture_OPTIM();

void chrono_erosion();
void chrono_erosion_SIMD();
void chrono_erosion_OPTIM();

#endif