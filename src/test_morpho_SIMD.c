#include "test_morpho_SIMD.h"

//On va tester l'erosion sur une matrice uint8** 3x32
//Soit trois pixels de hauteur et 32 de largeur
void test_erosion_SIMD_OK(){
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 31;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 1;
        }
    }

    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

}

void test_dilatation_SIMD_OK(){
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 31;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = k%2;
        }
    }

    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

}
