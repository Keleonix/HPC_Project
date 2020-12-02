#include "bench_chaine.h"

//Benchmark de la chaine SD+Morpho (version scalaire)
//n : nombre de fois où la chaine est lancée
void chrono_chaine(int n){

    // // chronometrie
    // int iter, niter = 1;
    // int run, nrun = 1;
    // double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    //La mesure de temps de la chaine ne prend pas en compte les
    //chargements et allocations, on va chronometrer du step1
    //à fermeture

    //Idée, ecrire un csv
    //Après avoir traité les 199
    //ecrire le temps complet pris pour traiter la sequence
    //ecrire le nombre de pixels par seconde
    //ptet autre chose, à voir
    FILE* fichier_csv;
    //On supprime le contenu du fichier et on écrit le nom des colonnes
    fichier_csv = fopen("bench_csv/chaine_scalaire.csv", "w");
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

    int nbPixels = (nrh+1)*(nch+1);

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

    for(int essai = 0: essai < n; essai++){
        for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

            //Generation du nom de fichier de l'image suivante
            generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

            //Chargement de l'image
            It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

            temps_frame = dtime();
            SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
            SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);
            SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);
            SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch);

            Et = ouverture(Et, *nrl, *nrh, *ncl, *nch);
            Et = fermeture(Et, *nrl, *nrh, *ncl, *nch);
            temps_frame = dtime() - temps_frame;

            temps_sequence =+ temps_frame;

            copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
            copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
        }

        //Résultats
        //Ouverture d'un fichier
        //On n'écrit à la suite du fichier
        fichier_csv = fopen("bench_csv/chaine_scalaire.csv", "a");
        //Essai;Temps_frame;Temps_sequence;Pixel_par_seconde
        temps_frame = temps_sequence/(NOMBRE_IMAGE);
        pixel_par_seconde = temps_frame/nbPixels;
        fprintf(fichier_csv, "%d;%6.2f;%6.2f;%6.2f\n", essai, temps_frame, temps_sequence, pixel_par_seconde);
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

void chrono_chaine_SIMD(){

}

void chrono_chaine_OPTIM(){

}
