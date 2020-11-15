#include <stdio.h>
#include <stdlib.h>

#include <nrdef.h>
#include <nrutil.h>

#include <vnrdef.h>
#include <vnrutil.h>

#include <mutil.h>

// t : instant de temps courant, servant à indicer les images
// It : image source en niveau de gris à l’instant t
// It−1 : l’image source à l’instant t-1,
// Mt : image de fond (image de moyenne),
// Ot : image de différence, en niveau de gris
// Vt : image de variance (d’écart type en fait) calculée pour tout pixel,
// Et : image d’étiquettes binaires (mouvement / fond), Et(x) = {0, 1} ou Et(x) = {0, 255} pour coder {fond,
// mouvement}
// x : le pixel courant de coordonnées (i,j)

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

//Initialisation de l'algorithme SigmaDelta
void SigmaDelta_step0(uint8** Io, uint8** Mt_1, uint8** Vt_1, int* nrl, int* nrh, int* ncl, int* nch){
    printf("Initialisation\n");
    // Mt_1 = Io
    // Vt_1 = VMIN
    copy_ui8matrix_ui8matrix (Io, *nrl, *nrh, *ncl, *nch, Mt_1); //La première image de fond est égale à la première image
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            Vt_1[j][k] = VMIN;
        }
    }
    printf("Fin du step0\n");

}


void SigmaDelta_1step(uint8** It, uint8** Mt_1, uint8** Mt, uint8** Ot, uint8** Vt_1, uint8** Vt, uint8** Et, int* nrl, int* nrh, int* ncl, int* nch){

    //Début de l'algorithme t = 1
    //Etape 1 : estimation de l'image de fond
    uint8 pixelM = 0;
    uint8 pixelIm = 0;
    //TODO : La matrice Mt_1 provoque des erreurs, à vérifier
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            pixelIm = It[j][k];
            pixelM = Mt_1[j][k];
            // pixelM = 0;
            // if(j < *nrl + 10){
            //     // printf("Mt = %d\n", pixelM);
            // }

            if(pixelM < pixelIm)
            {
                Mt[j][k] = pixelM + 1;
            }
            else if(pixelM > pixelIm){
                Mt[j][k] = pixelM - 1;
            }
            else{
                Mt[j][k] = pixelM;
            }
        }
    }

    //Etape 2 : Difference Ot
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            Ot[j][k] = abs(Mt[j][k] - It[j][k]);
        }
    }

    //Etape 3 : Mise à jour de l'image de variance Vt
    uint8 pixelVt = 0;
    uint8 pixelOt = 0;
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            pixelVt = Vt_1[j][k];
            pixelOt = Ot[j][k];

            if(pixelVt < N * pixelOt)
            {
                Vt[j][k] = pixelVt + 1;
            }
            else if(pixelVt > N * pixelOt){
                Vt[j][k] = pixelVt - 1;
            }
            else{
                Vt[j][k] = pixelVt;
            }

            Vt[j][k] = MAX(MIN(Vt[j][k], VMAX), VMIN);
        }
    }

    //Etape 4 : Estimation de l'image d'etiquettes binaires Et
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            pixelVt = Vt[j][k];
            pixelOt = Ot[j][k];
            if(pixelOt < pixelVt){
                Et[j][k] = 0;
            }
            else{
                Et[j][k] = 1;
            }
        }
    }
}

// int main(){
//     printf("Début du programme principal.\n");
//     int* nrl = malloc(sizeof(int));
//     int* nrh = malloc(sizeof(int));
//     int* ncl = malloc(sizeof(int));
//     int* nch = malloc(sizeof(int));
//     char image0[] = "car3/car_3000.pgm";

//     //Chargement de la 1ere image
//     uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
//     printf("Chargement de l'image.\n");
//     printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

//     //Allocation des matrices pour l'algorithme
//     uint8** Mt_1;
//     uint8** Vt_1;
//     uint8** Mt;
//     uint8** Vt;
//     uint8** Ot;
//     uint8** Et;

//     Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     Et = ui8matrix(*nrl, *nrh, *ncl, *nch);

//     //Initialisation de Mt_1 et Vt_1
//     SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

//     //Allocation de It
//     uint8** It = ui8matrix(*nrl, *nrh, *ncl, *nch);

//     //Algorithme SigmaDelta
//     char* image = malloc(18); //17 caractères dans le chemin relatif de l'image
//     for(int i = 3001; i < 3000+NOMBRE_IMAGE; i++){
//         //Generation du nom de fichier de l'image suivante
//         generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

//         //Chargement de l'image
//         It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

//         SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);

//         //Changement de variables
//         copy_ui8matrix_ui8matrix (Mt_1, *nrl, *nrh, *ncl, *nch, Mt);
//         copy_ui8matrix_ui8matrix (Vt_1, *nrl, *nrh, *ncl, *nch, Vt);
//     }


//     //Desallocation de la mémoire
//     free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
//     free(image);
//     free(nrl);
//     free(nrh);
//     free(ncl);
//     free(nch);
//     return 0;
// }
