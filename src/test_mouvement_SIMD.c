#include "test_mouvement_SIMD.h"

//TODO: Faut que je nettoie et fasse des vrais tests

//On va etudier le resultat du step1 pour voir, c'est quoi le souci avec les Mt
void test1_step1_SIMD(){
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

    int nbPixels = (*nrh+1)*(*nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_1 = vui8vector(0, nbPixels);
    vuint8* Mt = vui8vector(0, nbPixels);
    vuint8* Vt_1 = vui8vector(0, nbPixels);
    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char* image = malloc(sizeof(char)*48);
    // uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    for(int j = 3001; j <= 3100; j++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", j, 0, "pgm", image);

        //Chargement de l'image
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
        // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);
        vuint8 pixelsIm, pixelsM, C1, C2, K1, K2, K, M;

        for(int i = 0; i < nbVuint8; i++){
            pixelsIm = vec_load(&It[i]);
            pixelsM = vec_load(&Mt_1[i]);

            C1 = vec_gt (pixelsIm, pixelsM); //Sont mis à 1 tout pixel où It > main
            C2 = vec_gt (pixelsM, pixelsIm); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
            K1 = init_vuint8(1);
            K2 = init_vuint8(-1);
            K = vec_or(vec_and(C1, K1), vec_and(C2, K2));

            M = vec_add(K, pixelsM);
            vec_store(&Mt[i], M);
            if(j > 50 && j < 55 && i > 50 && i < 95){

                printf("Vecteur %i \n\n", i);

                       printf("It ");
                       display_vuint8(pixelsIm,"%d ", NULL);
                       printf("\n");

                       printf("Mo ");
                       display_vuint8(pixelsM, "%d ", NULL);
                       printf("\n");

                       printf("C1 ");
                       display_vuint8(C1,"%d ", NULL);
                       printf("\n");

                       printf("C2 ");
                       display_vuint8(C2,"%d ", NULL);
                       printf("\n");

                       printf("K1 ");
                       display_vuint8(K1,"%d ", NULL);
                       printf("\n");

                       printf("K2 ");
                       display_vuint8(K2,"%d ", NULL);
                       printf("\n");

                       printf("K ");
                       display_vuint8(K,"%d ", NULL);
                       printf("\n");

                       printf("M ");
                       display_vuint8(M,"%d ", NULL);
                       printf("\n");

                       printf("Mt ");
                       display_vuint8(Mt[i],"%d ", NULL);
                       printf("\n");
            }
        }

        // generate_filename_k_ndigit_extension("test_SIMD/Mt_", i, 0, "pgm", image);
        // copy_vui8vector_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, Mt_ui8);
        // SavePGM_ui8matrix(Mt_ui8, *nrl, *nrh, *ncl, *nch, image);
    }
}

//Test de Load, Save et des fonctions copy de vnrutil
void test_imagePGM(){

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

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Generation du nom de fichier de l'image suivante
    for(int i = 3001; i < 3100; i++){
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);
        copy_vui8vector_ui8matrix(It, *nrl, *nrh, *ncl, *nch, Et_ui8);
        generate_filename_k_ndigit_extension("retest/_", i, 0, "pgm", image);

        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);
    }

}

//On teste l'algorithme de comparaison dans la boucle de SigmaDelta_step1_SIMD
//sur deux vuint8
//0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
//15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
//Ici, on veut donc que
//0 0 0 0 0 0 0 0 2 2 2 2 2 2 2 2

void test_algo_step1_OK_1(){
    vuint8 a = init_vuint8_all(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    vuint8 b = init_vuint8_all(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
    vuint8 M = init_vuint8(1);

    vuint8 C1, C2, K1, K2, K;

    C1 = vec_gt (a, b); //Sont mis à 1 tout pixel où It > main
    C2 = vec_gt (b, a); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
    K1 = init_vuint8(1);
    K2 = init_vuint8(-1);
    K = vec_or(vec_and(C1, K1), vec_and(C2, K2));

    M = vec_add(K, M);

    printf("\n\n");

    display_vuint8(a,"%d ", "a ");
    printf("\n");

    display_vuint8(b, "%d ", "b ");
    printf("\n");

    display_vuint8(C1,"%d ", "C1 ");
    printf("\n");

    display_vuint8(C2,"%d ", "C2 ");
    printf("\n");

    display_vuint8(K1,"%d ", "K1 ");
    printf("\n");

    display_vuint8(K2,"%d ", "K2 ");
    printf("\n");

    display_vuint8(K,"%d ", "K ");
    printf("\n");

    display_vuint8(M,"%d ", "M ");
    printf("\n");

    printf("\n\n");

}
