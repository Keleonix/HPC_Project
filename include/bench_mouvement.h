#ifndef BENCH_MOUVEMENT_H
#define BENCH_MOUVEMENT_H

#include "mouvement.h"
#include "mouvement_SIMD.h"
#include "mouvement_optim.h"
#include "mymacro.h"
#include "dtime.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

//Mesure du temps pour les versions scalaires des étapes de
// l'algorithme SigmaDelta
void chrono_SD_step1(int n);
void chrono_SD_step2(int n);
void chrono_SD_step3(int n);
void chrono_SD_step4(int n);

//Mesure du temps pour les versions SIMD des étapes de
// l'algorithme SigmaDelta
void chrono_SD_step1_SIMD(int n);
void chrono_SD_step2_SIMD(int n);
void chrono_SD_step3_SIMD(int n);
void chrono_SD_step4_SIMD(int n);

//Mesure du temps pour les versions optimisées des étapes de
// l'algorithme SigmaDelta
void chrono_SD_steps_OPTIM(int n);

//Mesure du temps pour la version scalaire de l'algorithme SigmaDelta
void chrono_mouvement();

//Mesure du temps pour la version SIMD de l'algorithme SigmaDelta
void chrono_mouvement_SIMD();

//Mesure du temps pour la version optimisée de l'algorithme SigmaDelta
void chrono_mouvement_OPTIM();

#endif /*BENCH_MOUVEMENT_H*/
