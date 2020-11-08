#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <nrdef.h>
#include <nrutil.h>
#include <vnrdef.h>
#include <vnrutil.h>
#include <mutil.h>

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

//Allocation des matrices
void alloc_ui8matrixes();

//Premiere étape de l'algorithme SigmaDelta
void SigmaDelta_1step(uint8** It, uint8** Mt_1, uint8** Mt,\
    uint8** Ot, uint8** Vt_1, uint8** Vt,\
    uint8** Et, int* nrl, int* nrh, int* ncl, int* nch);

//Etapes suivantes de l'algorithme SigmaDelta
void SigmaDelta_1step(uint8** It, uint8** Mt_1, uint8** Mt, uint8** Ot, uint8** Vt_1, uint8** Vt, uint8** Et, int* nrl, int* nrh, int* ncl, int* nch)

//Desallocation des matrices
void free_ui8matrixes();

#endif /* MOUVEMENT_H */
