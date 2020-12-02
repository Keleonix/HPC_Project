#include "bench_morpho.h"

void chrono_erosion(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_erosion = 0;

    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    int n = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 1;
        }
    }
    //On appelle maintenant la fonction erosion
    CHRONO(uint8** resultat = erosion(mat_test, nrl, nrh, ncl, nch), cycle_erosion);

    printf("Resultats erosion\n");
    printf("Cpp : %6.2f \n", cycle_erosion/n);
    //TODO: free mat test et resultat
}

void chrono_erosion_SIMD(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_erosion_SIMD = 0;

    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    int n = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 1;
        }
    }
    uint8** resultat;
    //On appelle maintenant la fonction erosion
    CHRONO(resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch), cycle_erosion_SIMD);
    // uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);
    printf("Resultats erosion SIMD\n");
    printf("Cpp : %6.2f \n", cycle_erosion_SIMD/n);
    //TODO: free mat test et resultat (Impossible de lancer chrone avec niter > 1)
    //erreur seg à voir
}

void chrono_erosion_OPTIM(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_erosion_OPTIM = 0;

    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    int n = (nrh+1)*(nch+1);
    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 1;
        }
    }
    uint8** resultat;
    //On appelle maintenant la fonction erosion
    CHRONO(resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch), cycle_erosion_OPTIM);

    printf("Resultats erosion OPTIM\n");
    printf("Cpp : %6.2f \n", cycle_erosion_OPTIM/n);
}

void chrono_dilatation(){

    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_dilatation = 0;


    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    int n = (nrh+1)*(nch+1);


    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1 && k%4 == 3){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
        }
    }

    CHRONO(uint8** resultat = dilatation(mat_test, nrl, nrh, ncl, nch), cycle_dilatation);

    printf("Resultats dilatation\n");
    printf("Cpp : %6.2f \n", cycle_dilatation/n);
}

void chrono_dilatation_SIMD(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_dilatation_SIMD = 0;


    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    int n = (nrh+1)*(nch+1);


    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1 && k%4 == 3){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
        }
    }

    CHRONO(uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch), cycle_dilatation_SIMD);

    printf("Resultats dilatation SIMD\n");
    printf("Cpp : %6.2f \n", cycle_dilatation_SIMD/n);
}

void chrono_dilatation_OPTIM(){
    // chronometrie
    int iter, niter = 1;
    int run, nrun = 1;
    double t0, t1, dt, tmin, t;

    //Timer pour chaque étape
    //CPP STEPS
    double cycle_dilatation_OPTIM = 0;


    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    int n = (nrh+1)*(nch+1);


    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1 && k%4 == 3){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
        }
    }

    CHRONO(uint8** resultat = dilatation_OPTIM(mat_test, nrl, nrh, ncl, nch), cycle_dilatation_OPTIM);

    printf("Resultats dilatation OPTIM\n");
    printf("Cpp : %6.2f \n", cycle_dilatation_OPTIM/n);
}

void chrono_ouverture();
void chrono_ouverture_SIMD();
void chrono_ouverture_OPTIM();
