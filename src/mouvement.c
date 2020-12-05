#include "mouvement.h"

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

//Premiere étape de l'algorithme SigmaDelta
void SigmaDelta_step0(uint8** Io, uint8** Mt_1, uint8** Vt_1, \
    int* nrl, int* nrh, \
    int* ncl, int* nch){
    // Mt_1 = Io
    // Vt_1 = VMIN
    copy_ui8matrix_ui8matrix (Io, *nrl, *nrh, *ncl, *nch, Mt_1); //La première image de fond est égale à la première image
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            Vt_1[j][k] = VMIN;
        }
    }
}

//Etape 1 : estimation de l'image de fond
void SigmaDelta_step1(uint8** It, uint8** Mt_1, uint8** Mt, int* nrl, int* nrh, int* ncl, int* nch){

        uint8 pixel_Mt_1 = 0;
        uint8 pixel_It = 0;

        for(int j = *nrl; j <= *nrh; j++){
            for(int k = *ncl; k <= *nch; k++){
                pixel_It = It[j][k];
                pixel_Mt_1 = Mt_1[j][k];

                if(pixel_Mt_1 < pixel_It)
                {
                    Mt[j][k] = pixel_Mt_1 + 1;
                }
                else if(pixel_Mt_1 > pixel_It){
                    Mt[j][k] = pixel_Mt_1 - 1;
                }
                else{
                    Mt[j][k] = pixel_Mt_1;
                }
            }
        }
}

//Etape 2 : Ot, difference entre image source et moyenne
void SigmaDelta_step2(uint8** It,  uint8** Mt, uint8** Ot, int* nrl, int* nrh, int* ncl, int* nch){

    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            Ot[j][k] = abs(Mt[j][k] - It[j][k]);
        }
    }
}

//Etape 3 : Mise à jour de l'image de variance Vt
void SigmaDelta_step3(uint8** Ot, uint8** Vt_1, uint8** Vt, int* nrl, int* nrh, int* ncl, int* nch){

    uint8 pixel_Vt_1 = 0;
    uint8 pixel_Ot = 0;
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            pixel_Vt_1 = Vt_1[j][k];
            pixel_Ot = Ot[j][k];

            if(pixel_Vt_1 < N * pixel_Ot) //N = 3
            {
                Vt[j][k] = pixel_Vt_1 + 1;
            }
            else if(pixel_Vt_1 > N * pixel_Ot){
                Vt[j][k] = pixel_Vt_1 - 1;
            }
            else{
                Vt[j][k] = pixel_Vt_1;
            }

            Vt[j][k] = MAX(MIN(Vt[j][k], VMAX), VMIN);
        }
    }
}

//Etape 4 : Estimation de l'image d'etiquettes binaires Et
void SigmaDelta_step4(uint8** Ot, uint8** Vt, uint8** Et, int* nrl, int* nrh, int* ncl, int* nch){

    uint8 pixel_Vt = 0;
    uint8 pixel_Ot = 0;
    for(int j = *nrl; j <= *nrh; j++){
        for(int k = *ncl; k <= *nch; k++){
            pixel_Vt = Vt[j][k];
            pixel_Ot = Ot[j][k];

            if(pixel_Ot < pixel_Vt){
                Et[j][k] = 0;
            }
            else{
                Et[j][k] = 1;
            }
        }
    }

}

void main_mouvement(){
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
    uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Et = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It;

    //Algorithme SigmaDelta
    //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
    char image[18]; //17 caractères dans le chemin relatif de l'image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

        SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
        SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);
        SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);
        SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch);


        generate_filename_k_ndigit_extension("test/Mt_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, image);
        // generate_filename_k_ndigit_extension("test/Ot_", i, 0, "pgm", image);
        // SavePGM_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, image);
        // generate_filename_k_ndigit_extension("test/Vt_", i, 0, "pgm", image);
        // SavePGM_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("test/Et_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, image);


        //Changement de variables
        // Mt_1 = Mt;
        // Vt_1 = Vt;
        copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
        copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
    }
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}
