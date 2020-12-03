#ifndef BENCH_CHAINE_H
#define BENCH_CHAINE_H

#include "morpho.h"
#include "morpho_SIMD.h"
#include "morpho_optim.h"
#include "mouvement.h"
#include "mouvement_SIMD.h"
#include "mouvement_optim.h"
#include "mymacro.h"
#include "dtime.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


#define CPP_RESULTATS(t, t_min, t_max) \
        t_min = MIN(t_min, t); \
        t_max = MAX(t_max, t); \

// #define TEMPS(X,t)                       \
//     tmin = 1e38;                          \
//     for(run=0; run<nrun; run++) {         \
//         t0 = (double) dtime();           \
//         for(iter=0; iter<niter; iter++) { \
//             X;                            \
//         }                                 \
//         t1 = (double) dtime();           \
//         dt=t1-t0; if(dt<tmin) tmin = dt;  \
//     }                                     \
//     t = tmin / (double) niter

//Fonctions servant à bencher la chaine SD+Morpho

void chrono_chaine(int n);
void chrono_chaine_SIMD(int n);
void chrono_chaine_OPTIM(int n);

#endif
