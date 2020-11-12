/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement.h"
// #include "test_mouvement.h"
// #include "bench_mouvement.h"

#include "mouvement_SIMD.h"

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199

// void info(void)
// {
// #ifdef ENABLE_BENCHMARK
//     puts("mode Benchmark ON");
//     puts("DEBUG OFF");
// #else
//     puts("mode Benchmark OFF");
//     puts("DEBUG ON");
// #endif
// }

void copy_ui8matrix_vui8vector(uint8** mat, long nrl, long nrh, long ncl, long nch, vuint8* vect){

    int nbVect = (nch+1)/16; //Nombre de vecteur par ligne
    int i = 0; //Indice pour vui8vector
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k+=16){
            vect[i] = init_vuint8_all(mat[j][k  ], mat[j][k+1], mat[j][k+2], mat[j][k+3], \
                                    mat[j][k+4], mat[j][k+5], mat[j][k+6], mat[j][k+7], \
                                    mat[j][k+8], mat[j][k+9], mat[j][k+10], mat[j][k+11], \
                                    mat[j][k+12], mat[j][k+13], mat[j][k+14], mat[j][k+15]);
            i++;
        }
    }
}

int main(){
    // info();
    //main_mouvement();
    //SIMD
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    //Chargement de l'image O
    // char image0[] = "img_test/rei2.pgm";
    char image0[] = "car3/car_3000.pgm";
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    printf("Chargement de l'image.\n");
    printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Copie de Io dans Mo, vuint8
    int p = 0; //padding
    int b = 0; //bord

    //sans bord
    int nbPixels = (*nrh+1)*(*nch+1);
    int nbVuint8 = nbPixels/16+1;
    printf("Nombre de pixels = %d, pixels restants après division = %d => Nombre de vecteurs = %d\n,", nbPixels, nbPixels%16, nbVuint8);

    //Les images de la séquence ont un nombre de pixels qui est multiple de 16
    //On va donc juste faire un tableau de vuint8 1D sans padding et on verra bien
    //Sans bord, sans padding

    //Etape 0 :
        //Parcours de Io pour remplir Mo
        vuint8* Mo = vui8vector(0, nbPixels);
        copy_ui8matrix_vui8vector(Io, *nrl, *nrh, *ncl, *nch, Mo);

        //Initialisation de Vo
        vuint8* Vo = vui8vector(0, nbPixels);
        for(int i = 0; i < nbVuint8; i++){
            Vo = init_vuint8((uint8)VMIN);
        }

    //Etape 1
    //Chargement de la première image
    char image1[] = "car3/car_3000.pgm";
    uint8** It = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    vuint8* Itvect = vui8vector(0, nbPixels);
    copy_ui8copy_ui8matrix_vui8vector(It, *nrl, *nrh, *ncl, *nch, Itvect);

    


    //On calcule le nombre de vecteurs correspondant à hxw
    //On a un bord de 1 et on calcule le padding à partir du reste de
    //de la division nbPixels/16
    // vuint8** Mo = vui8matrix(*nrl, *nrh, *ncl, *nch);
    // Mo = (vuint8**) Io;
    // display_vui8matrix(Mo, *nrl, *nrh, *ncl, *nch, "%d",NULL);

    //Initialisation de Vo à VMIN (on mettra à VMAX quand on comprendra comment
    //enregistrer une image PGM en SIMD)
    return 0;
}
