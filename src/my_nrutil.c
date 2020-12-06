#include "my_nrutil.h"

#define VMAX 254

//Convertit la matrice binaire {0 ; 1} en matrice {0, VMAX}
void convertion_matrice_binaire(uint8** mat, int nrl, int nrh, int ncl, int nch){
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(mat[j][k]){
                mat[j][k] = VMAX;
            }
        }
    }
}
