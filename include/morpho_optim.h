#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "simd_macro.h"

vuint8** bords_OPTIM(uint8** im, int nrl, int hauteur, int ncl, int largeur);
uint8** erosion_OPTIM(uint8** im, int nrl, int nrh, int ncr, int nch);
uint8** dilatation_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** fermeture_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** ouverture_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch);
