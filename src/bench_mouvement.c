#include "bench_mouvement.h"

void chrono_SD_step1(int n){


    //La mesure de temps de la chaine ne prend pas en compte les
    //chargements et allocations, on va chronometrer du step1
    //à fermeture

    //On ecrit un csv
    //Après avoir traité les 199 images
    //On ecrit le temps complet pris pour traiter la sequence
    //On ecrit le temps pour traiter une frame
    //On ecrit le débit, i.e. nombre de pixels traités par seconde

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step1.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

    int nbPixels = (*nrh+1)*(*nch+1);
    // printf("Chargement de l'image.\n");
    // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Allocation des matrices pour l'algorithme
    uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It;

    //Algorithme SigmaDelta
    //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
    char image[18]; //17 caractères dans le chemin relatif de l'image

    for(int essai = 0; essai < n; essai++)
    {
        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

            temps_frame = dtime();
            SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step1.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step2(int n){
    //Timer pour chaque étape
    //CPP STEPS
    //La mesure de temps de la chaine ne prend pas en compte les
    //chargements et allocations, on va chronometrer du step1
    //à fermeture

    //On ecrit un csv
    //Après avoir traité les 199 images
    //On ecrit le temps complet pris pour traiter la sequence
    //On ecrit le temps pour traiter une frame
    //On ecrit le débit, i.e. nombre de pixels traités par seconde

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step2.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

    int nbPixels = (*nrh+1)*(*nch+1);
    // printf("Chargement de l'image.\n");
    // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Allocation des matrices pour l'algorithme
    uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It;

    //Algorithme SigmaDelta
    //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
    char image[18]; //17 caractères dans le chemin relatif de l'image

    for(int essai = 0; essai < n; essai++)
    {
        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

            SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);

            temps_frame = dtime();

            SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);

            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step2.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step3(int n){

    //La mesure de temps de la chaine ne prend pas en compte les
    //chargements et allocations, on va chronometrer du step1
    //à fermeture

    //On ecrit un csv
    //Après avoir traité les 199 images
    //On ecrit le temps complet pris pour traiter la sequence
    //On ecrit le temps pour traiter une frame
    //On ecrit le débit, i.e. nombre de pixels traités par seconde

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step3.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

    int nbPixels = (*nrh+1)*(*nch+1);
    // printf("Chargement de l'image.\n");
    // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Allocation des matrices pour l'algorithme
    uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It;

    //Algorithme SigmaDelta
    //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
    char image[18]; //17 caractères dans le chemin relatif de l'image

    for(int essai = 0; essai < n; essai++)
    {
        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

            SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
            SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);

            temps_frame = dtime();
            SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);

            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
            copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step3.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step4(int n){

    //La mesure de temps de la chaine ne prend pas en compte les
    //chargements et allocations, on va chronometrer du step1
    //à fermeture

    //On ecrit un csv
    //Après avoir traité les 199 images
    //On ecrit le temps complet pris pour traiter la sequence
    //On ecrit le temps pour traiter une frame
    //On ecrit le débit, i.e. nombre de pixels traités par seconde

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step4.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);

    int nbPixels = (*nrh+1)*(*nch+1);
    // printf("Chargement de l'image.\n");
    // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

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

    for(int essai = 0; essai < n; essai++)
    {
        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);


            SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
            SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);
            SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);

            temps_frame = dtime();
            SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
            copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_scalaire_step4.csv", "a");

        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
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

void chrono_SD_step1_SIMD(int n){
    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step1.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

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

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

    for(int essai = 0; essai < n; essai++){

        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

            copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

            temps_frame = dtime();

            SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);

            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            //Changement de variables
            // Mt_1 = Mt;
            copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step1.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }


    //Algorithme SigmaDelta
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    free_vui8vector(Mt, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step2_SIMD(int n){

    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step2.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

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
    vuint8* Ot = vui8vector(0, nbPixels);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

    //Allocation d'une matrice uint8 pour conserver le resultat Et
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    for(int essai = 0; essai < n; essai++){

        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
            // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

            copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

            SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);

            temps_frame = dtime();
            SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            //Changement de variables
            // Mt_1 = Mt;
            copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step2.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }


    //Algorithme SigmaDelta
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    free_vui8vector(Mt, 0, nbPixels);
    free_vui8vector(Ot, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step3_SIMD(int n){
    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step3.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

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

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

    for(int essai = 0; essai < n; essai++){

        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
            // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

            copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

            SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);
            SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8);

            temps_frame = dtime();
            SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            //Changement de variables
            // Mt_1 = Mt;
            // Vt_1 = Vt;
            copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
            copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step3.csv", "a");

        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
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
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

void chrono_SD_step4_SIMD(int n){
    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step4.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

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

    for(int essai = 0; essai < n; essai++){

        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
            // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

            copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);


            SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);
            SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8);
            SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8);

            temps_frame = dtime();
            SigmaDelta_step4_SIMD(Ot, Vt, Et, nbVuint8);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            //Changement de variables
            // Mt_1 = Mt;
            // Vt_1 = Vt;
            copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
            copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_SIMD_step4.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
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

void chrono_SD_steps_OPTIM(int n){

    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/sigma_delta/SD_OPTIM_steps.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

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

    for(int essai = 0; essai < n; essai++){

        temps_sequence = 0;
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
            // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

            copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);

            temps_frame = dtime();
            SigmaDelta_steps_OPTIM(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nbVuint8);
            temps_frame = dtime() - temps_frame;

            temps_sequence += temps_frame;

            copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
            copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/sigma_delta/SD_OPTIM_steps.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }


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

//TODO: A retirer
//Mesure du temps pour la version scalaire de l'algorithme SigmaDelta
// void chrono_mouvement(){
//
//     // chronometrie
//     int iter, niter = 1;
//     int run, nrun = 1;
//     double t0, t1, dt, tmin, t;
//
//     int n = 0;
//
//     //CPP pour chaque étape
//     //CPP STEP1
//     double cycle_step1 = 0;
//     double cycle_step1_min = 1e38; //Temps minimum pour un appel de l'étape 1
//     double cycle_step1_max = 0; //Temps maximum pour un appel de l'étape 1
//     double cycle_step1_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP2
//     double cycle_step2 = 0;
//     double cycle_step2_min = 1e38; //Temps minimum pour un appel de l'étape 2
//     double cycle_step2_max = 0; //Temps maximum pour un appel de l'étape 2
//     double cycle_step2_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP3
//     double cycle_step3 = 0;
//     double cycle_step3_min = 1e38; //Temps minimum pour un appel de l'étape 3
//     double cycle_step3_max = 0; //Temps maximum pour un appel de l'étape 3
//     double cycle_step3_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP4
//     double cycle_step4 = 0 ;
//     double cycle_step4_min = 1e38; //Temps minimum pour un appel de l'étape 2
//     double cycle_step4_max = 0; //Temps maximum pour un appel de l'étape 2
//     double cycle_step4_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //Algorithme
//     int* nrl = malloc(sizeof(int));
//     int* nrh = malloc(sizeof(int));
//     int* ncl = malloc(sizeof(int));
//     int* nch = malloc(sizeof(int));
//     char image0[] = "car3/car_3000.pgm";
//
//     //Chargement de la 1ere image
//     uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
//
//     //Allocation des matrices pour l'algorithme
//     uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Et = ui8matrix(*nrl, *nrh, *ncl, *nch);
//
//     //Initialisation de Mt_1 et Vt_1
//     SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);
//
//     //Allocation de It
//     uint8** It;
//     n = (*nrh+1)*(*nch+1); //Nombre de pixels
//     //Algorithme SigmaDelta
//     //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
//     char image[18]; //17 caractères dans le chemin relatif de l'image
//     for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){
//
//         //Generation du nom de fichier de l'image suivante
//         generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);
//
//         //Chargement de l'image
//         It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
//
//         CHRONO(SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch), cycle_step1);
//         CPP_RESULTATS(cycle_step1, cycle_step1_min, cycle_step1_max, cycle_step1_sequence);
//
//         CHRONO(SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch), cycle_step2);
//         CPP_RESULTATS(cycle_step2, cycle_step2_min, cycle_step2_max, cycle_step2_sequence);
//
//         CHRONO(SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch), cycle_step3);
//         CPP_RESULTATS(cycle_step3, cycle_step3_min, cycle_step3_max, cycle_step3_sequence);
//
//         CHRONO(SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch), cycle_step4);
//         CPP_RESULTATS(cycle_step4, cycle_step4_min, cycle_step4_max, cycle_step4_sequence);
//
//         copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
//         copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
//     }
//
//     //Affichage des résultats
//     printf("Resultats étape 1 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step1_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step1_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step1_sequence/n);
//
//     printf("Resultats étape 2 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step2_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step2_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step2_sequence/n);
//
//     printf("Resultats étape 3 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step3_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step3_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step3_sequence/n);
//
//     printf("Resultats étape 4 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step4_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step4_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step4_sequence/n);
//
//     //Desallocation de la mémoire
//     free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
//     free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
//     free(nrl);
//     free(nrh);
//     free(ncl);
//     free(nch);
// }
//
// //Mesure du temps pour la version SIMD de l'algorithme SigmaDelta
// void chrono_mouvement_SIMD(){
//
//     // chronometrie
//     int iter, niter = 5;
//     int run, nrun = 5;
//     double t0, t1, dt, tmin, t;
//
//     int n = 0;
//     //Timer pour chaque étape
//     //CPP STEP1
//     double cycle_step1 = 0;
//     double cycle_step1_min = 1e38; //Temps minimum pour un appel de l'étape 1
//     double cycle_step1_max = 0; //Temps maximum pour un appel de l'étape 1
//     double cycle_step1_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP2
//     double cycle_step2 = 0;
//     double cycle_step2_min = 1e38; //Temps minimum pour un appel de l'étape 2
//     double cycle_step2_max = 0; //Temps maximum pour un appel de l'étape 2
//     double cycle_step2_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP3
//     double cycle_step3 = 0;
//     double cycle_step3_min = 1e38; //Temps minimum pour un appel de l'étape 3
//     double cycle_step3_max = 0; //Temps maximum pour un appel de l'étape 3
//     double cycle_step3_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //CPP STEP4
//     double cycle_step4 = 0 ;
//     double cycle_step4_min = 1e38; //Temps minimum pour un appel de l'étape 2
//     double cycle_step4_max = 0; //Temps maximum pour un appel de l'étape 2
//     double cycle_step4_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //Algorithme
//     int* nrl = malloc(sizeof(int));
//     int* nrh = malloc(sizeof(int));
//     int* ncl = malloc(sizeof(int));
//     int* nch = malloc(sizeof(int));
//     char image0[] = "car3/car_3000.pgm";
//
//     //Chargement de la 1ere image
//     uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
//
//     int nbPixels = (*nrh+1)*(*nch+1);
//
//     n = nbPixels;
//     //Calcule du nombre de vecteurs nécessaires pour l'image
//     int nbVuint8 = nbPixels/16+1;
//
//     //Allocation des matrices pour l'algorithme
//     vuint8* Mt_1 = vui8vector(0, nbPixels);
//     vuint8* Vt_1 = vui8vector(0, nbPixels);
//     vuint8* Mt = vui8vector(0, nbPixels);
//     vuint8* Vt = vui8vector(0, nbPixels);
//     vuint8* Ot = vui8vector(0, nbPixels);
//     vuint8* Et = vui8vector(0, nbPixels);
//
//     //Initialisation de Mt_1 et Vt_1
//     SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);
//
//     //Allocation de It
//     uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     vuint8* It = vui8vector(0, nbPixels);
//
//     char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image
//
//     //Allocation d'une matrice uint8 pour conserver le resultat Et
//     uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Vt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Ot_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//
//     //On commence l'algorithme à la deuxième image
//     for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){
//
//         //Generation du nom de fichier de l'image suivante
//         generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);
//
//         //Chargement de l'image
//         imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
//
//         copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);
//
//         CHRONO(SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8), cycle_step1);
//         CPP_RESULTATS(cycle_step1, cycle_step1_min, cycle_step1_max, cycle_step1_sequence);
//
//         CHRONO(SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8), cycle_step2);
//         CPP_RESULTATS(cycle_step2, cycle_step2_min, cycle_step2_max, cycle_step2_sequence);
//
//         CHRONO(SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8), cycle_step3);
//         CPP_RESULTATS(cycle_step3, cycle_step3_min, cycle_step3_max, cycle_step3_sequence);
//
//         CHRONO(SigmaDelta_step4_SIMD(Ot, Vt, Et, nbVuint8), cycle_step4);
//         CPP_RESULTATS(cycle_step4, cycle_step4_min, cycle_step4_max, cycle_step4_sequence);
//
//         copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
//         copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
//     }
//
//     //Affichage des résultats
//     printf("Resultats étape 1 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step1_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step1_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step1_sequence/n);
//
//     printf("Resultats étape 2 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step2_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step2_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step2_sequence/n);
//
//     printf("Resultats étape 3 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step3_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step3_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step3_sequence/n);
//
//     printf("Resultats étape 4 de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_step4_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_step4_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_step4_sequence/n);
//
//     // Desallocation de la mémoire
//     free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
//     free_vui8vector(It, 0, nbPixels);
//     free_vui8vector(Mt_1, 0, nbPixels);
//     free_vui8vector(Vt_1, 0, nbPixels);
//     free_vui8vector(Mt, 0, nbPixels);
//     free_vui8vector(Vt, 0, nbPixels);
//     free_vui8vector(Ot, 0, nbPixels);
//     free_vui8vector(Et, 0, nbPixels);
//     free(nrl);
//     free(nrh);
//     free(ncl);
//     free(nch);
// }
//
// //Mesure du temps pour la version optimisée de l'algorithme SigmaDelta
// void chrono_mouvement_OPTIM(){
//     // chronometrie
//     int iter, niter = 1;
//     int run, nrun = 1;
//     double t0, t1, dt, tmin, t;
//
//     //Timer pour chaque étape
//     //CPP STEPS
//     double cycle_steps = 0;
//     double cycle_steps_min = 1e38; //Temps minimum pour un appel de la fonction
//     double cycle_steps_max = 0; //Temps maximum pour un appel de la fonction
//     double cycle_steps_sequence = 0; //Somme des temps pour la sequence entiere
//
//     //Algorithme
//     int* nrl = malloc(sizeof(int));
//     int* nrh = malloc(sizeof(int));
//     int* ncl = malloc(sizeof(int));
//     int* nch = malloc(sizeof(int));
//     char image0[] = "car3/car_3000.pgm";
//
//     //Chargement de la 1ere image
//     uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
//
//     int nbPixels = (*nrh+1)*(*nch+1);
//     int n = nbPixels;
//     //Calcule du nombre de vecteurs nécessaires pour l'image
//     int nbVuint8 = nbPixels/16+1;
//
//     //Allocation des matrices pour l'algorithme
//     vuint8* Mt_1 = vui8vector(0, nbPixels);
//     vuint8* Vt_1 = vui8vector(0, nbPixels);
//     vuint8* Mt = vui8vector(0, nbPixels);
//     vuint8* Vt = vui8vector(0, nbPixels);
//     vuint8* Ot = vui8vector(0, nbPixels);
//     vuint8* Et = vui8vector(0, nbPixels);
//
//     //Initialisation de Mt_1 et Vt_1
//     SigmaDelta_step0_OPTIM(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);
//
//     //Allocation de It
//     uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     vuint8* It = vui8vector(0, nbPixels);
//
//     char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image
//
//     //Allocation d'une matrice uint8 pour conserver le resultat Et
//     uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Vt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Ot_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//     uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
//
//     //On commence l'algorithme à la deuxième image
//     for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){
//
//         //Generation du nom de fichier de l'image suivante
//         generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);
//
//         //Chargement de l'image
//         imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
//
//         copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);
//
//         CHRONO(SigmaDelta_steps_OPTIM(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nbVuint8), cycle_steps);
//         CPP_RESULTATS(cycle_steps, cycle_steps_min, cycle_steps_max, cycle_steps_sequence);
//
//         copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
//         copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
//     }
//     //Affichage des résultats
//     printf("Resultats étapes de l'algorithme\n");
//     printf("Temps minimum : %6.2f \n", cycle_steps_min/n);
//     printf("Temps maximum : %6.2f \n", cycle_steps_max/n);
//     printf("Temps séquence : %6.2f \n", cycle_steps_sequence/n);
//
//     // Desallocation de la mémoire
//     free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
//     free_vui8vector(It, 0, nbPixels);
//     free_vui8vector(Mt_1, 0, nbPixels);
//     free_vui8vector(Vt_1, 0, nbPixels);
//     free_vui8vector(Mt, 0, nbPixels);
//     free_vui8vector(Vt, 0, nbPixels);
//     free_vui8vector(Ot, 0, nbPixels);
//     free_vui8vector(Et, 0, nbPixels);
//     free(nrl);
//     free(nrh);
//     free(ncl);
//     free(nch);
// }
