#include "morpho.h"

#define R 1                                     // On défini le rayon R pour l'espace B de convolution

uint8** Margin(uint8** im, int nrl, int nrh, int ncl, int nch){
    int i, j;
    uint8** marginIm;

    marginIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);

    for(i = nrl - R; i <= nrh + R; i++){                                                    // On crée une image avec des bords initialisés à 0
        for(j = ncl - R; j <= nch + R; j++){                                                // Les bords sont placés à une distance R autour de l'image
            if(i >= nrl && i <= nrh && j >= ncl && j <= nch) marginIm[i][j] = im[i][j];
            else marginIm[i][j] = 0;
        }
    }
    return marginIm;
}

uint8** erosion(uint8** im, int nrl, int nrh, int ncl, int nch){
    int i, j, k, l;
    uint8 tmp;
    uint8** res;
    uint8** marginIm;

    res = ui8matrix(nrl, nrh, ncl, nch);
    marginIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);   // Future image de taille [nrl+nrh+2*R, ncl+nch+2*R]

    marginIm = Margin(im, nrl, nrh, ncl, nch);                  // Création de bords

    for(i = nrl; i <= nrh; i++){                                // On parcour toute l'image pour faire une convolution pixel par pixel
        for(j = ncl; j <= nch; j++){

            tmp = marginIm[i-1][j-1];                           // tmp est égal à la première case de ce qui va être l'espace B

            for(k = i-R; k <= i+R; k++){                        // On procède à la convolution sur l'espace B avec B = 2*R + 1 
                for(l = j-R; l <= j+R; l++){

                    tmp &= marginIm[k][l];                     // On applique un filtre "AND" sur l'espace de convolution

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
    uint8** marginIm;

    res = ui8matrix(nrl, nrh, ncl, nch);
    marginIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);       // Future image de taille [nrl+nrh+2*R, ncl+nch+2*R]

    marginIm = Margin(im, nrl, nrh, ncl, nch);                      // Création de bords

    for(i = nrl; i <= nrh; i++){                                    // On parcour toute l'image pour faire une convolution pixel par pixel
        for(j = ncl; j <= nch; j++){

            tmp = marginIm[i-1][j-1];                               // tmp est égal à la première case de ce qui va être l'espace B

            for(k = i-R; k <= i+R; k++){                            // On procède à la convolution sur l'espace B avec B = 2*R + 1 
                for(l = j-R; l <= j+R; l++){

                    tmp |= marginIm[k][l];                         // On applique un filtre "OR" sur l'espace de convolution

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