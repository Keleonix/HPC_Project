#ifndef BENCH_MOUVEMENT_H
#define BENCH_MOUVEMENT_H

#include "mouvement.h"
#include "mouvement_SIMD.h"
#include "mouvement_optim.h"
#include "mymacro.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


#define CPP_RESULTATS(t, t_min, t_max, t_somme) \
        t_min = MIN(t_min, t); \
        t_max = MAX(t_max, t); \
        t_somme += t;

//Mesure du temps pour la version scalaire de l'algorithme SigmaDelta
void chrono_mouvement();

//Mesure du temps pour la version SIMD de l'algorithme SigmaDelta
void chrono_mouvement_SIMD();

//Mesure du temps pour la version optimisée de l'algorithme SigmaDelta
void chrono_mouvement_OPTIM();

#endif /*BENCH_MOUVEMENT_H*/
