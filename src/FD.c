#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "morpho.h"

#define THETA 10

uint8** FD(char imf0[], char imf_1[], int* nrl, int* nrh, int* ncl, int* nch){    
    uint8** mf_1;
    uint8** mf0;
    uint8** Et;
    uint8** O;

    mf_1 = LoadPGM_ui8matrix(imf_1, nrl, nrh, ncl, nch);
    mf0 = LoadPGM_ui8matrix(imf0, nrl, nrh, ncl, nch);
    Et = ui8matrix(*nrl, *nrh, *ncl, *nch);
    O = ui8matrix(*nrl, *nrh, *ncl, *nch);
    // display_ui8matrix(Et , *nrl, *nrh, *ncl, *nch, "[%d]", NULL);


    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            O[j][k] = abs(mf0[j][k]-mf_1[j][k]);
            if(O[j][k] < THETA){
                Et[j][k] = 0;
            }
            else{
                Et[j][k] = 1;
            }
        }
    }


    free_ui8matrix(mf0, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(mf_1, *nrl, *nrh, *ncl, *nch);

    // display_ui8matrix(Et , *nrl, *nrh, *ncl, *nch, "%d|", NULL);
    return Et;
}

int main(int argc, char* argv[]){
    int* nrl = malloc(sizeof(int)); int* nrh = malloc(sizeof(int)); int* ncl = malloc(sizeof(int)); int* nch = malloc(sizeof(int));
    char imf_1[] = "car3/car_3000.pgm";
    char im[] = "car3/car_3001.pgm";

    uint8** Et;
    uint8** Im = LoadPGM_ui8matrix(im, nrl, nrh, ncl, nch);

    // Et = FD(im, imf_1, nrl, nrh, ncl, nch);
    // display Picture

    Et = erosion(Im, *nrl, *nrh, *ncl, *nch);
    // display Picture

    Et = dilatation(Im, *nrl, *nrh, *ncl, *nch);
    // display Picture

    Et = fermeture(Im, *nrl, *nrh, *ncl, *nch);
    // display Picture

    Et = ouverture(Im, *nrl, *nrh, *ncl, *nch);
    // display Picture

    free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
    free(nrl); free(nrh); free(ncl); free(nch);

    return 0;
}