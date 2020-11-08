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
#include "test_mouvement.h"
#include "bench_mouvement.h"

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

int main(){
    // info();
    printf("Début du programme principal.\n");
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    printf("Chargement de l'image.\n");
    printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Allocation des matrices pour l'algorithme
    uint8** Mt_1;
    uint8** Vt_1;
    uint8** Mt;
    uint8** Vt;
    uint8** Ot;
    uint8** Et;

    Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);
    Et = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Algorithme SigmaDelta
    SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);

    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
    free(image);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
    return 0;
}
