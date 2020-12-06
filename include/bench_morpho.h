#ifndef BENCH_MORPHO_H
#define BENCH_MORPHO_H

#include "morpho.h"
#include "morpho_SIMD.h"
#include "morpho_optim.h"
#include "mymacro.h"
#include "dtime.h"

#define NOMBRE_IMAGE 199

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


#define CPP_RESULTATS(t, t_min, t_max) \
        t_min = MIN(t_min, t); \
        t_max = MAX(t_max, t); \

void chrono_erosion(int n);
void chrono_erosion_SIMD(int n);
void chrono_erosion_OPTIM(int n);

void chrono_dilatation(int n);
void chrono_dilatation_SIMD(int n);
void chrono_dilatation_OPTIM(int n);

#endif
