#include "test_morpho_optim.h"
#include "test_morpho_simd.h"

#define NB_TESTS_EROSION 10

//TODO: Faire les mêmes tests en changeant avec des valeurs différentes
//TODO: Faire des macros pour chaque matrice pour augmenter le nombre de tests
//unitaires
//On va tester l'erosion sur une matrice uint8** 3x32
//Soit trois pixels de hauteur et 32 de largeur
void test_erosion_OPTIM_1(){        //test de 1 solitaires
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    //On fait une matrice avec des 1 et des 0 qui s'enchainent parce qu'il est
    //tard et que j'ai pas d'autres idées

    // for(int j = nrl; j <= nrh; j++){
    //     for(int k = ncl; k <= nch; k++){
    //         mat_test[j][k] = 1;
    //     }
    // }

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
    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

}

void test_erosion_OPTIM_2(){        //test de carrés de 1
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(k%5 == 0 ||k%5 == 1 ||k%5 == 2){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
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
    uint8** resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }
}

void test_erosion_OPTIM_3(){        //test de 1 par paires et en croix
    int nrl = 0;
    int nrh = 3;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if((k+j)%5 == 0 ||(j)%6 == 2 ||(k-j)%7 == 4){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
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
    uint8** resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }
}

void test_erosion_OPTIM_4(){            // Test des quatres coins
    int nrl = 0;
    int nrh = 6;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 0;
        }
    }

    mat_test[0][0] = 1;
    mat_test[1][0] = 1;
    mat_test[0][1] = 1;
    mat_test[1][1] = 1;

    mat_test[0][15] = 1;
    mat_test[1][15] = 1;
    mat_test[0][14] = 1;
    mat_test[1][14] = 1;

    mat_test[6][15] = 1;
    mat_test[5][15] = 1;
    mat_test[6][14] = 1;
    mat_test[5][14] = 1;

    mat_test[6][0] = 1;
    mat_test[5][0] = 1;
    mat_test[6][1] = 1;
    mat_test[5][1] = 1;

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    // //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_OPTIM(mat_test, nrl, nrh, ncl, nch);

    // //On affiche le resultat
    // //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    // //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }
}

void test_erosion_OPTIM_5(){        //test de 1 solitaires dans les coins
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat_test[j][k] = 0;
        }
    }

    mat_test[0][0] = 1;

    mat_test[0][15] = 1;

    mat_test[2][15] = 1;

    mat_test[2][0] = 1;

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    // //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    // //On affiche le resultat
    // //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    // //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de l'erosion\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }
}
void test_erosion_OPTIM_6(){}
void test_erosion_OPTIM_7(){}
void test_erosion_OPTIM_8(){}
void test_erosion_OPTIM_9(){}
void test_erosion_OPTIM_10(){}

void tests_erosion_OPTIM(){
    void(*tests[NB_TESTS_EROSION])() = {test_erosion_OPTIM_1, test_erosion_OPTIM_2, test_erosion_OPTIM_3, test_erosion_OPTIM_4, test_erosion_OPTIM_5, test_erosion_OPTIM_6, test_erosion_OPTIM_7, test_erosion_OPTIM_8, test_erosion_OPTIM_9, test_erosion_OPTIM_10};
    for(int i = 0; i < NB_TESTS_EROSION; i++){
        printf("Test erosion %d\n", i+1);
        (tests[i])();
    }

}

void test_dilatation_OPTIM_1(){
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
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

    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    printf("Matrice de test \n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_OPTIM(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    //TODO: Remplacer par un test, qui envoie OK pour chaque ligne correcte
    //et KO pour chaque ligne mauvaise
    printf("Matrice résultat de la dilatation\n\n");
    for(int i = nrl; i <= nrh; i++){
        display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
        printf("\n");
    }

}
