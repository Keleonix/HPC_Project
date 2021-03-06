#include "morpho.h"

#define R 1                                     // On défini le rayon R pour l'espace B de convolution

uint8** bords(uint8** im, int nrl, int nrh, int ncl, int nch, int val_Bords){
    int i, j;
    uint8** bordsIm;

    bordsIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);

    for(i = nrl - R; i <= nrh + R; i++){                                                    // On crée une image avec des bords initialisés à 0
        for(j = ncl - R; j <= nch + R; j++){                                                // Les bords sont placés à une distance R autour de l'image
            if(i >= nrl && i <= nrh && j >= ncl && j <= nch) bordsIm[i][j] = im[i][j];
            else bordsIm[i][j] = val_Bords;
        }
    }
    return bordsIm;
}

uint8** erosion(uint8** im, int nrl, int nrh, int ncl, int nch){
    int i, j, k, l;
    uint8 tmp;
    uint8** res;
    uint8** bordsIm;

    res = ui8matrix(nrl, nrh, ncl, nch);
    bordsIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);   // Future image de taille [nrl+nrh+2*R, ncl+nch+2*R]

    bordsIm = bords(im, nrl, nrh, ncl, nch, 1);                  // Création de bords

    for(i = nrl; i <= nrh; i++){                                // On parcour toute l'image pour faire une convolution pixel par pixel
        for(j = ncl; j <= nch; j++){

            tmp = bordsIm[i-1][j-1];                           // tmp est égal à la première case de ce qui va être l'espace B

            for(k = i-R; k <= i+R; k++){                        // On procède à la convolution sur l'espace B avec B = 2*R + 1 
                for(l = j-R; l <= j+R; l++){

                    tmp &= bordsIm[k][l];                     // On applique un filtre "AND" sur l'espace de convolution

                }
            }

            res[i][j] = tmp;                                    // On stocke le résultat

        }
    }

    return res;                                                 // On renvoie le résultat
}

uint8** dilatation(uint8** im, int nrl, int nrh, int ncl, int nch){
    int i, j, k, l;
    uint8 tmp;
    uint8** res;
    uint8** bordsIm;

    res = ui8matrix(nrl, nrh, ncl, nch);
    bordsIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);       // Future image de taille [nrl+nrh+2*R, ncl+nch+2*R]

    bordsIm = bords(im, nrl, nrh, ncl, nch, 0);                      // Création de bords

    for(i = nrl; i <= nrh; i++){                                    // On parcour toute l'image pour faire une convolution pixel par pixel
        for(j = ncl; j <= nch; j++){

            tmp = bordsIm[i-1][j-1];                               // tmp est égal à la première case de ce qui va être l'espace B

            for(k = i-R; k <= i+R; k++){                            // On procède à la convolution sur l'espace B avec B = 2*R + 1 
                for(l = j-R; l <= j+R; l++){

                    tmp |= bordsIm[k][l];                         // On applique un filtre "OR" sur l'espace de convolution

                }
            }

            res[i][j] = tmp;                                        // On stocke le résultat

        }
    }

    return res;                                 // On renvoie le résultat
}

uint8** fermeture(uint8** im, int nrl, int nrh, int ncl, int nch){
    return erosion(dilatation(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

uint8** ouverture(uint8** im, int nrl, int nrh, int ncl, int nch){
    return dilatation(erosion(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}