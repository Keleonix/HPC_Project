/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement.h"
#include "morpho.h"

#include "mouvement_SIMD.h"
#include "morpho_SIMD.h"

#include "mouvement_optim.h"
#include "morpho_optim.h"

#include "my_vnrutil.h"
#include "simd_macro.h"

#include "dtime.h"
#include "test_mouvement.h"
#include "test_mouvement_SIMD.h"
#include "test_mouvement_optim.h"

#include "test_morpho.h"
#include "test_morpho_SIMD.h"
#include "test_morpho_optim.h"

#include "bench_mouvement.h"
#include "bench_morpho.h"
#include "bench_chaine.h"

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199


//Applique l'algorithme SigmaDelta, puis la morphologie aux images de la séquence
void chaine_complete();
//Applique l'algorithme SigmaDelta, puis la morphologie aux images de la séquence en SIMD
void chaine_complete_SIMD();
//Applique l'algorithme SigmaDelta, puis la morphologie aux images de la séquence en SIMD optimisé
void chaine_complete_OPTIM();

//Trois modes possibles,
//Verif (Lance les tests unitaires et affiche donc les OK et les KO
//Traitement (Fais la chaine complète normalement et enregistre les images traitées)
//Bench (Lance les fonctions de benchmark)

int main(int argc, char const *argv[]){

    //0 pour les tests unitaires,
    //1 pour le traitement, fait la chaine complète et enregistre les images traitées
    //2 pour les benchmarks

    int mode = 2;
    int n = 300;

    switch(mode){
        case 0:
            /*Fonctions appelant tous les tests unitaires */
            tests_mouvement();
            tests_mouvement_SIMD();
            tests_mouvement_OPTIM();
            tests_erosion_OPTIM();
            tests_dilatation_OPTIM();
            tests_erosion_SIMD();
            tests_dilatation_SIMD();
            tests_erosion();
            tests_dilatation();
            break;
        case 1:
            /*Fonctions de test des chaînes complètes */
            // chaine_complete();
            // chaine_complete_SIMD();
            chaine_complete_OPTIM();
            break;

        case 2:
            /*Chrono étapes SD */
            chrono_SD_step1(n);
            chrono_SD_step2(n);
            chrono_SD_step3(n);
            chrono_SD_step4(n);

            /*Chrono étapes SD SIMD*/
            chrono_SD_step1_SIMD(n);
            chrono_SD_step2_SIMD(n);
            chrono_SD_step3_SIMD(n);
            chrono_SD_step4_SIMD(n);

            /*Chrono SD optimisé*/
            chrono_SD_steps_OPTIM(n);

            /*Chrono morpho */
            chrono_erosion(n);
            chrono_erosion_SIMD(n);
            chrono_erosion_OPTIM(n);

            chrono_dilatation(n);
            chrono_dilatation_SIMD(n);
            // chrono_dilatation_OPTIM(n);

            /* Chrono chaine complète*/
            chrono_chaine(n);
            chrono_chaine_SIMD(n);
            chrono_chaine_OPTIM(n);
            break;
    }


    return 0;
}

void chaine_complete(){

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
    char image[48];
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

        //TODO : Rajouter les macros chrono pour mesurer le temps de chaque fonction
        SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
        SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);
        SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);
        SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch);

        generate_filename_k_ndigit_extension("images_scalaire/Mt_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("images_scalaire/Ot_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("images_scalaire/Vt_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, image);

        Et = ouverture(Et, *nrl, *nrh, *ncl, *nch);
        Et = fermeture(Et, *nrl, *nrh, *ncl, *nch);

        generate_filename_k_ndigit_extension("images_scalaire/Etmorph_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, image);

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

void chaine_complete_SIMD(){
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

    int nbPixels = (*nrh+1)*(*nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1 = vui8vector(0, nbPixels);
    vuint8* Vt_1 = vui8vector(0, nbPixels);
    vuint8* Mt = vui8vector(0, nbPixels);
    vuint8* Vt = vui8vector(0, nbPixels);
    vuint8* Ot = vui8vector(0, nbPixels);
    vuint8* Et = vui8vector(0, nbPixels);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char image[48];

    //Allocation d'une matrice uint8 pour conserver le resultat Et
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //On commence l'algorithme à la deuxième image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

        SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);
        SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8);
        SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8);
        SigmaDelta_step4_SIMD(Ot, Vt, Et, nbVuint8);

        generate_filename_k_ndigit_extension("images_SIMD/Mt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, Mt_ui8);
        SavePGM_ui8matrix(Mt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_SIMD/Ot_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, Ot_ui8);
        SavePGM_ui8matrix(Ot_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_SIMD/Vt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, Vt_ui8);
        SavePGM_ui8matrix(Vt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_SIMD/Et_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        Et_ui8 = ouverture_SIMD(Et_ui8, *nrl, *nrh, *ncl, *nch);
        Et_ui8 = fermeture_SIMD(Et_ui8, *nrl, *nrh, *ncl, *nch);

        generate_filename_k_ndigit_extension("images_SIMD/Etmorph_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        //Changement de variables
        // Mt_1 = Mt;
        // Vt_1 = Vt;
        copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
    }

    //Algorithme SigmaDelta
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    free_vui8vector(Mt, 0, nbPixels);
    free_vui8vector(Vt, 0, nbPixels);
    free_vui8vector(Ot, 0, nbPixels);
    free_vui8vector(Et, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chaine_complete_OPTIM(){
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

    int nbPixels = (*nrh+1)*(*nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1 = vui8vector(0, nbPixels);
    vuint8* Vt_1 = vui8vector(0, nbPixels);
    vuint8* Mt = vui8vector(0, nbPixels);
    vuint8* Vt = vui8vector(0, nbPixels);
    vuint8* Ot = vui8vector(0, nbPixels);
    vuint8* Et = vui8vector(0, nbPixels);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_OPTIM(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char image[48];

    //Allocation d'une matrice uint8 pour conserver le resultat Et
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //On commence l'algorithme à la deuxième image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

        SigmaDelta_steps_OPTIM(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nbVuint8);

        generate_filename_k_ndigit_extension("images_OPTIM/Mt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, Mt_ui8);
        SavePGM_ui8matrix(Mt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_OPTIM/Ot_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, Ot_ui8);
        SavePGM_ui8matrix(Ot_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_OPTIM/Vt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, Vt_ui8);
        SavePGM_ui8matrix(Vt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("images_OPTIM/Et_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        Et_ui8 = ouverture_OPTIM(Et_ui8, *nrl, *nrh, *ncl, *nch);
        Et_ui8 = fermeture_OPTIM(Et_ui8, *nrl, *nrh, *ncl, *nch);

        generate_filename_k_ndigit_extension("images_OPTIM/Etmorph_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        // }

        //Changement de variables
        Mt_1 = Mt;
        Vt_1 = Vt;
    }

    //Algorithme SigmaDelta
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    free_vui8vector(Ot, 0, nbPixels);
    free_vui8vector(Et, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}
