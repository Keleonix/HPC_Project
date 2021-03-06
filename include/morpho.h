#ifndef MORPHO_H
#define MORPHO_H

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

uint8** bords(uint8** im, int nrl, int nrh, int ncl, int nch, int val_Bords);
uint8** erosion(uint8** im, int nrl, int nrh, int ncr, int nch);
uint8** dilatation(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** fermeture(uint8** im, int nrl, int nrh, int ncl, int nch);
uint8** ouverture(uint8** im, int nrl, int nrh, int ncl, int nch);

#endif /* MORPHO_H */
