#include "morpho_SIMD.h"

#define R 1                                     // On défini le rayon R pour l'espace B de convolution ici R = 1
#define DEROULAGE_MARGE 3

void bords_SIMD(uint8** im, int nrl, int* nrh, int ncl, int* nch){
    int i, j, n, r;
    vuint8 im0, im1, im2;
    vuint8** marginIm;

    marginIm = vui8matrix(nrl - R, nrh + R, ncl - R, nch + R);
    //Slide 17 NRC
    //Prendre l'image, caster sur vuint8**
    //Dupliquer les bords
    
    n = *nrh + 2*R;                                                         // prologue 1
    r = n % DEROULAGE_MARGE;
    for(i = nrl; i < n-r; i += DEROULAGE_MARGE){                            //boucle 1
        marginIm[i][ncl   ] = 0; marginIm[i+1][ncl   ] = 0; marginIm[i+2][ncl     ] = 0;
        marginIm[i][*nch+R] = 0; marginIm[i+1][*nch+R] = 0; marginIm[i+2][*nch+2*R] = 0;
    }
    switch(r){                                                              //epilogue 1
        case 2:
            marginIm[i+1][ncl     ] = 0;
            marginIm[i+1][*nch+2*R] = 0;
        case 1:
            marginIm[i][ncl     ] = 0;
            marginIm[i][*nch+2*R] = 0;
        default:
            break;
    }

    n = *nch + 2*R;                                                         // prologue 2
    r = n % DEROULAGE_MARGE;
    for(i = ncl; i < n-r; i += DEROULAGE_MARGE){                            //boucle 2
        marginIm[nrl     ][j] = 0; marginIm[nrl     ][j+1] = 0; marginIm[nrl     ][j+2] = 0;
        marginIm[*nrh+2*R][j] = 0; marginIm[*nrh+2*R][j+1] = 0; marginIm[*nrh+2*R][j+2] = 0;
    }
    switch(r){                                                              //epilogue 2
        case 2:
            marginIm[nrl     ][j+1] = 0;
            marginIm[*nrh+2*R][j+1] = 0;
        case 1:
            marginIm[nrl     ][j] = 0;
            marginIm[*nrh+2*R][j] = 0;
        default:
            break;
    }

    n = *nrh;                                                               // prologue 3
    r = n % DEROULAGE_MARGE;
    for(j = ncl; j < *nch; j++){                                            // boucle 3
        for(i = nrl; i < *nrh; i++){
            im0 = im[i+0][j];       im1 = im[i+1][j];       im2 = im[i+2][j];
            marginIm[i][j] = im0;   marginIm[i+1][j] = im1; marginIm[i+2][j] = im2;
        }
    }
    switch(r){                                                              // epilogue 3
        case 2:
            im1 = im[i+1][j];
            marginIm[i+1][j] = im1;
        case 1:
            im0 = im[i+0][j];
            marginIm[i][j] = im0;
        default:
            break;
    }

}

uint8** erosion(uint8** im, int nrl, int nrh, int ncl, int nch){
    int i, j, k, l;
    uint8 tmp;
    uint8** res;
    uint8** marginIm;

    res = ui8matrix(nrl, nrh, ncl, nch);
    marginIm = ui8matrix(nrl - R, nrh + R, ncl - R, nch + R);   // Future image de taille [nrl+nrh+2*R, ncl+nch+2*R]

        bords_SIMD(marginIm, nrl, &nrh, ncl, &nch);            // Création de bords

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

    marginIm = bords_SIMD(im, nrl, &nrh, ncl, &nch);                // Création de bords

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
