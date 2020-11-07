#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#define R 1

uint8** erosion(uint8** im, int nrl, int nrh, int ncr, int nch){
    int i, j, k;
    uint8 tmp;
    uint8** res;

    res = ui8matrix(nrl - r, nrh + r, ncl - r, *nch + r);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch < j++){
            
        }
    }

    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch < j++){
            tmp = im[i-1][j-1];
            for(k = i-r; k <= i+r; k++){
                for(l = j-r; l <= j+r; l++){
                    if (im[k][l] < tmp){
                        tmp = im[k][l];
                    }
                }
            }
            res[i][j] = tmp;
        }
    }

    return res;
}

int main(int argc, char* argv[]){




    return 0;
}