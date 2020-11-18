/*
    Fonctions inspirées de vnrutil.h pour faciliter l'optimisation en SIMD
*/

#ifndef MY_VNRUTIL_H
#define MY_VNRUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <nrdef.h>
#include <nrutil.h>
#include <vnrdef.h>
#include <vnrutil.h>
#include <mutil.h>

#include "simd_macro.h"

//Copie les données d'une matrice uint8** dans un tableau de vecteurs vuint8* de taille (nrh*nch)
void copy_ui8matrix_vui8vector(uint8** mat, long nrl, long nrh, long ncl, long nch, vuint8* vect);

//Multiplie deux vuint8, a et b, entre eux et renvoie le produit c
vuint8 vi8_mul(vuint8 a, vuint8 b);

//Applique abs au vecteur en faisant un if(vect < 0)
vuint8 vi8_abs(vuint8 vect);

// //Compare les vecteurs a et b, et renvoie un vecteur composé des MAX(a[i], b[i])
// vuint8 vi8_max(vuint8 a, vuint8 b);
//
// //Compare les vecteurs a et b, et renvoie un vecteur composé des MIN(a[i], b[i])
// vuint8 vi8_min(vuint8 a, vuint8 b);

//Copie les données d'un tableau de vecteurs vuint8* dans une matrice uint8** de taille nrh x nch
void copy_vui8vector_ui8matrix(vuint8* vect, long nrl, long nrh, long ncl, long nch, uint8** mat);

//Copie les données du vecteur vect1 vers le vecteur vect2
void copy_vui8vector_vui8vector(vuint8* vect1, int nbVuint8, vuint8* vect2);
#endif /* MY_VNRUTIL_H */
