#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <nrdef.h>
#include <nrutil.h>
#include <mutil.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

//Initialisation de la premiere image, matrice de moyenne et matrice de variance à t = 0
void SigmaDelta_step0(uint8** Io, uint8** Mt_1, uint8** Vt_1, \
    int* nrl, int* nrh, \
    int* ncl, int* nch);

//Etape 1 : estimation de l'image de fond
void SigmaDelta_step1(uint8** It, uint8** Mt_1, uint8** Mt, int* nrl, int* nrh, int* ncl, int* nch);

//Etape 2 : Ot, difference entre image source et moyenne
void SigmaDelta_step2(uint8** It,  uint8** Mt, uint8** Ot, int* nrl, int* nrh, int* ncl, int* nch);

//Etape 3 : Mise à jour de l'image de variance Vt
void SigmaDelta_step3(uint8** Ot, uint8** Vt_1, uint8** Vt, int* nrl, int* nrh, int* ncl, int* nch);

//Etape 4 : Estimation de l'image d'etiquettes binaires Et
void SigmaDelta_step4(uint8** Ot, uint8** Vt, uint8** Et, int* nrl, int* nrh, int* ncl, int* nch);

//Convertit la matrice binaire {0 ; 1} en matrice {0, VMAX}
void convertion_matrice_binaire(uint8** mat, int nrl, int nrh, int ncl, int nch);

//Fonction principale qui alloue/desalloue les tableaux utilisés, appelle les
//fonctions correspondantes à chaque étape de SigmaDelta, enregistre chaque
//tableau Et dans un fichier PGM
void main_mouvement();

#endif /* MOUVEMENT_H */
