#ifndef BENCH_MORPHO_H
#define BENCH_MORPHO_H

#include "morpho.h"
#include "morpho_SIMD.h"
#include "morpho_optim.h"
#include "mymacro.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


#define CPP_RESULTATS(t, t_min, t_max) \
        t_min = MIN(t_min, t); \
        t_max = MAX(t_max, t); \

void chrono_erosion();
void chrono_erosion_SIMD();
void chrono_erosion_OPTIM();

void chrono_dilatation();
void chrono_dilatation_SIMD();
void chrono_dilatation_OPTIM();

void chrono_ouverture();
void chrono_ouverture_SIMD();
void chrono_ouverture_OPTIM();

void chrono_fermeture();
void chrono_fermeture_SIMD();
void chrono_fermeture_OPTIM();

#endif
