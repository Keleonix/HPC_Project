#ifndef MORPHO_SIMD_H
#define MORPHO_SIMD_H

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "simd_macro.h"

vuint8** bords_SIMD(uint8** im, int nrl, int hauteur, int ncl, int largeur, int val_Bords);
uint8** erosion_SIMD(uint8** im, int nrl, int nrh, int ncr, int nch);
uint8** dilatation_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** fermeture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** ouverture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch);

#endif /*MORPHO_SIMD_H */
