#include "bench_morpho.h"

#define INDEX_BASE_IM 3001

void chrono_erosion(int n){

    printf("Debut chrono_erosion\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/erosion_scalaire.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30];
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;

        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){
            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = erosion(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;
        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/erosion_scalaire.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);

    }

    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_erosion\n");

}

void chrono_erosion_SIMD(int n){

    printf("Debut chrono_erosion_SIMD\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/erosion_SIMD.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30]; //17 caractères dans le chemin relatif de l'image
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;
        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){
            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;


        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/erosion_SIMD.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    //free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_erosion_SIMD\n");

}

void chrono_erosion_OPTIM(int n){

    printf("Debut chrono_erosion_OPTIM\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/erosion_OPTIM.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30]; //17 caractères dans le chemin relatif de l'image
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;
        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){

            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;


        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/erosion_OPTIM.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_erosion_OPTIM\n");

}

void chrono_dilatation(int n){

    printf("Debut chrono_dilatation\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/dilatation_scalaire.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30]; //17 caractères dans le chemin relatif de l'image
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;
        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){
            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = dilatation(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;


        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/dilatation_scalaire.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_dilatation\n");

}

void chrono_dilatation_SIMD(int n){

    printf("Debut chrono_dilatation_SIMD\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/dilatation_SIMD.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30]; //17 caractères dans le chemin relatif de l'image
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;
        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){
            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;


        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/dilatation_SIMD.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_dilatation_SIMD\n");

}

void chrono_dilatation_OPTIM(int n){

    printf("Debut chrono_dilatation_OPTIM\n");

    FILE* fichier_csv;
    //On ouvre le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/morpho/dilatation_OPTIM.csv", "w");
    fprintf(fichier_csv, "Essai;Temps_frame;Temps_sequence;Pixel_par_seconde\n");
    fclose(fichier_csv);

    double temps_frame = 0;
    double temps_sequence = 0;
    double pixel_par_seconde = 0;

    //On crée une matrice de la taille des images de car3
    int nrl = 0;
    int nrh = 239;
    int ncl = 0;
    int nch = 319;
    uint8** mat_test;

    int nbPixels = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    uint8** resultat = ui8matrix(nrl, nrh, ncl, nch);
    char image[30]; //17 caractères dans le chemin relatif de l'image
    //On appelle maintenant la fonction erosion
    for(int essai = 0; essai < n; essai++){
        temps_sequence = 0;
        for(int i = INDEX_BASE_IM; i <= INDEX_BASE_IM+NOMBRE_IMAGE-1; i++){
            generate_filename_k_ndigit_extension("images_scalaire/Et_", i, 0, "pgm", image);
            mat_test = LoadPGM_ui8matrix(image, &nrl, &nrh, &ncl, &nch);

            temps_frame = dtime();
            resultat = dilatation_OPTIM(mat_test, nrl, nrh, ncl, nch);
            temps_frame = dtime() - temps_frame;
            temps_sequence += temps_frame;


        }
        //Résultats
        //Ouverture d'un fichier
        //On écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/morpho/dilatation_OPTIM.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = (temps_sequence/(NOMBRE_IMAGE));
        pixel_par_seconde = nbPixels/temps_frame;
        temps_frame *= 1000; //On multiplie par 1000 pour avoir le temps en ms
        temps_sequence *= 1000;
        fprintf(fichier_csv, "%d;%lf;%lf;%lf\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
        fclose(fichier_csv);
    }

    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);

    printf("Fin chrono_dilatation_OPTIM\n");

}
