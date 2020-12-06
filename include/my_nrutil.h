/*
    Fonctions inspirées de nrutil.h
*/

#ifndef MY_NRUTIL_H
#define MY_NRUTIL_H

#include <stdio.h>
#include <stddef.h>

#include "nrdef.h"
#include "nrutil.h"

//Convertit la matrice binaire {0 ; 1} en matrice {0, VMAX}
void convertion_matrice_binaire(uint8** mat, int nrl, int nrh, int ncl, int nch);

#endif /* MY_NRUTIL_H */
