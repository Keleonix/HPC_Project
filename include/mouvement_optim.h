#ifndef MOUVEMENT_OPTIM_H
#define MOUVEMENT_OPTIM_H

#include <stdio.h>
#include <stdlib.h>
#include <nrdef.h>
#include <nrutil.h>
#include <vnrdef.h>
#include <vnrutil.h>
#include <mutil.h>

#include "my_vnrutil.h"
#include "simd_macro.h"
#include "mouvement.h"

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199

//Initialisation de la premiere image, image de fond et image de variance à t = 0
void SigmaDelta_step0_OPTIM(uint8** Io, vuint8* Mt_1, vuint8* Vt_1,\
     int* nrl, int* nrh, int* ncl, int* nch, int nbVuint8);

//Etapes de l'algoritme SigmaDelta
//Etape 1 : estimation de l'image de fond (version SIMD)
//Etape 2 : Ot, difference entre image source et moyenne (version SIMD)
//Etape 3 : Mise à jour de l'image de variance Vt (version SIMD)
//Etape 4 : Estimation de l'image d'etiquettes binaires Et (version SIMD)
void SigmaDelta_steps_OPTIM(vuint8* It, vuint8* Mt_1, vuint8* Mt,\
     vuint8* Ot, vuint8* Vt_1, vuint8* Vt, vuint8* Et, int nbVuint8);


//Fonction principale qui alloue/desalloue les tableaux utilisés, appelle les
//fonctions correspondantes à chaque étape de SigmaDelta et enregistre chaque
//tableau Et dans un fichier PGM (version OPTIM)
void main_mouvement_OPTIM();

void main_mvt_ref_OPTIM();
#endif /*MOUVEMENT_OPTIM_H */
