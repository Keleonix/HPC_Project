#include "bench_mouvement.h"

//Mesure du temps pour la version scalaire de l'algorithme SigmaDelta
void chrono_mouvement(){

    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //TIMER STEP1
    double timer_step1 = 0;
    double timer_step1_min = 1e38; //Temps minimum pour un appel de l'étape 1
    double timer_step1_max = 0; //Temps maximum pour un appel de l'étape 1
    double timer_step1_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP2
    double timer_step2 = 0;
    double timer_step2_min = 1e38; //Temps minimum pour un appel de l'étape 2
    double timer_step2_max = 0; //Temps maximum pour un appel de l'étape 2
    double timer_step2_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP3
    double timer_step3 = 0;
    double timer_step3_min = 1e38; //Temps minimum pour un appel de l'étape 3
    double timer_step3_max = 0; //Temps maximum pour un appel de l'étape 3
    double timer_step3_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP4
    double timer_step4 = 0 ;
    double timer_step4_min = 1e38; //Temps minimum pour un appel de l'étape 2
    double timer_step4_max = 0; //Temps maximum pour un appel de l'étape 2
    double timer_step4_sequence = 0; //Somme des temps pour la sequence entiere

    //Algorithme
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

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

        CHRONO(SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch), timer_step1);
        TEMPS_RESULTATS(timer_step1, timer_step1_min, timer_step1_max, timer_step1_sequence);

        CHRONO(SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch), timer_step2);
        TEMPS_RESULTATS(timer_step2, timer_step2_min, timer_step2_max, timer_step2_sequence);

        CHRONO(SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch), timer_step3);
        TEMPS_RESULTATS(timer_step3, timer_step3_min, timer_step3_max, timer_step3_sequence);

        CHRONO(SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch), timer_step4);
        TEMPS_RESULTATS(timer_step4, timer_step4_min, timer_step4_max, timer_step4_sequence);

        copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
        copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
    }

    //Affichage des résultats
    printf("Resultats étape 1 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step1_min);
    printf("Temps maximum : %4.0f \n", timer_step1_max);
    printf("Temps séquence : %4.0f \n", timer_step1_sequence);

    printf("Resultats étape 2 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step2_min);
    printf("Temps maximum : %4.0f \n", timer_step2_max);
    printf("Temps séquence : %4.0f \n", timer_step2_sequence);

    printf("Resultats étape 3 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step3_min);
    printf("Temps maximum : %4.0f \n", timer_step3_max);
    printf("Temps séquence : %4.0f \n", timer_step3_sequence);

    printf("Resultats étape 4 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step4_min);
    printf("Temps maximum : %4.0f \n", timer_step4_max);
    printf("Temps séquence : %4.0f \n", timer_step4_sequence);

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

//Mesure du temps pour la version SIMD de l'algorithme SigmaDelta
void chrono_mouvement_SIMD(){

    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //TIMER STEP1
    double timer_step1 = 0;
    double timer_step1_min = 1e38; //Temps minimum pour un appel de l'étape 1
    double timer_step1_max = 0; //Temps maximum pour un appel de l'étape 1
    double timer_step1_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP2
    double timer_step2 = 0;
    double timer_step2_min = 1e38; //Temps minimum pour un appel de l'étape 2
    double timer_step2_max = 0; //Temps maximum pour un appel de l'étape 2
    double timer_step2_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP3
    double timer_step3 = 0;
    double timer_step3_min = 1e38; //Temps minimum pour un appel de l'étape 3
    double timer_step3_max = 0; //Temps maximum pour un appel de l'étape 3
    double timer_step3_sequence = 0; //Somme des temps pour la sequence entiere

    //TIMER STEP4
    double timer_step4 = 0 ;
    double timer_step4_min = 1e38; //Temps minimum pour un appel de l'étape 2
    double timer_step4_max = 0; //Temps maximum pour un appel de l'étape 2
    double timer_step4_sequence = 0; //Somme des temps pour la sequence entiere

    //Algorithme
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

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

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

        CHRONO(SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8), timer_step1);
        TEMPS_RESULTATS(timer_step1, timer_step1_min, timer_step1_max, timer_step1_sequence);

        CHRONO(SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8), timer_step2);
        TEMPS_RESULTATS(timer_step2, timer_step2_min, timer_step2_max, timer_step2_sequence);

        CHRONO(SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8), timer_step3);
        TEMPS_RESULTATS(timer_step3, timer_step3_min, timer_step3_max, timer_step3_sequence);

        CHRONO(SigmaDelta_step4_SIMD(Ot, Vt, Et, nbVuint8), timer_step4);
        TEMPS_RESULTATS(timer_step4, timer_step4_min, timer_step4_max, timer_step4_sequence);

        copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
    }

    //Affichage des résultats
    printf("Resultats étape 1 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step1_min);
    printf("Temps maximum : %4.0f \n", timer_step1_max);
    printf("Temps séquence : %4.0f \n", timer_step1_sequence);

    printf("Resultats étape 2 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step2_min);
    printf("Temps maximum : %4.0f \n", timer_step2_max);
    printf("Temps séquence : %4.0f \n", timer_step2_sequence);

    printf("Resultats étape 3 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step3_min);
    printf("Temps maximum : %4.0f \n", timer_step3_max);
    printf("Temps séquence : %4.0f \n", timer_step3_sequence);

    printf("Resultats étape 4 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_step4_min);
    printf("Temps maximum : %4.0f \n", timer_step4_max);
    printf("Temps séquence : %4.0f \n", timer_step4_sequence);

    // Desallocation de la mémoire
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

//Mesure du temps pour la version optimisée de l'algorithme SigmaDelta
void chrono_mouvement_OPTIM(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //TIMER STEPS
    double timer_steps = 0;
    double timer_steps_min = 1e38; //Temps minimum pour un appel de la fonction
    double timer_steps_max = 0; //Temps maximum pour un appel de la fonction
    double timer_steps_sequence = 0; //Somme des temps pour la sequence entiere

    //Algorithme
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

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

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

        CHRONO(SigmaDelta_steps_OPTIM(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nbVuint8), timer_steps);
        TEMPS_RESULTATS(timer_steps, timer_steps_min, timer_steps_max, timer_steps_sequence);

        copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
    }
    //Affichage des résultats
    printf("Resultats étape 1 de l'algorithme\n");
    printf("Temps minimum : %4.0f \n", timer_steps_min);
    printf("Temps maximum : %4.0f \n", timer_steps_max);
    printf("Temps séquence : %4.0f \n", timer_steps_sequence);

    // Desallocation de la mémoire
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
