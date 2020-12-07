#include "test_morpho_SIMD.h"

#define NB_TESTS_EROSION 7
#define NB_TESTS_DILATATION 7

//On testera l'erosion/dilatation sur une matrice uint8**
void test_erosion_SIMD_1(){        // test de 1 solitaires
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_2(){        // test de carrés de 1
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0},
                                {1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0},
                                {1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_3(){        // test de 1 par paires et en croix
    int nrl = 0;
    int nrh = 3;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1 || j == 2 || k == 7 || k == 8){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
        }
    }
    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[4][16] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_4(){        // test des quatres coins
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[7][16] = {  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_5(){        // test de 1 solitaires dans les coins
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    // On affiche le resultat
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_6(){        // test des bords de l'image = 2
    int nrl = 0;
    int nrh = 4;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j >= nrh-1 || k >= nch-1 || j <= nrl+1 || k <= ncl+1) mat_test[j][k] = 1;
            else mat_test[j][k] = 0;
        }
    }

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[5][16] = {  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_erosion_SIMD_7(){        // test ligne au centre
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1) mat_test[j][k] = 1;
            else mat_test[j][k] = 0;
        }
    }

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = erosion_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void tests_erosion_SIMD(){
    // On stovke toutes les fonctions de test dans un tableau de pointeur de fonctions
    void(*tests[NB_TESTS_EROSION])() = {test_erosion_SIMD_1, test_erosion_SIMD_2, test_erosion_SIMD_3, test_erosion_SIMD_4, test_erosion_SIMD_5, test_erosion_SIMD_6, test_erosion_SIMD_7};
    
    // On appelle chaque fonction une par une pour vérifier OK/KO
    for(int i = 0; i < NB_TESTS_EROSION; i++){
        printf("Test erosion %d\n", i+1);
        (tests[i])();
    }
}

void test_dilatation_SIMD_1(){        // test de 1 solitaires
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    

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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
                                {0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
                                {0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_2(){        // test de carrés de 1
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_3(){        // test de 1 par paires et en croix
    int nrl = 0;
    int nrh = 3;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1 || j == 2 || k == 7 || k == 8){
                mat_test[j][k] = 1;
            }
            else{
                mat_test[j][k] = 0;
            }
        }
    }
    //On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    //s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[4][16] = {  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_4(){        // test des quatres coins
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[7][16] = {  {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
                                {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
                                {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
                                {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
                                {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_5(){        // test de 1 solitaires dans les coins
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
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_6(){        // test des bords de l'image = 1
    int nrl = 0;
    int nrh = 4;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == nrh || k == nch || j == nrl || k == ncl) mat_test[j][k] = 1;
            else mat_test[j][k] = 0;
        }
    }

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[5][16] = {  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void test_dilatation_SIMD_7(){        // test ligne au centre
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;
    uint8** mat_test = ui8matrix(nrl, nrh, ncl, nch);

    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(j == 1) mat_test[j][k] = 1;
            else mat_test[j][k] = 0;
        }
    }

    // On affiche la matrice pour s'assurer qu'elle ressemble bien à ce qu'on
    // s'attend
    // printf("Matrice de test \n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(mat_test[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    //On appelle maintenant la fonction erosion
    uint8** resultat = dilatation_SIMD(mat_test, nrl, nrh, ncl, nch);

    //On affiche le resultat
    
    // printf("Matrice résultat de l'erosion\n\n");
    // for(int i = nrl; i <= nrh; i++){
    //     display_ui8vector(resultat[i], ncl, nch, " %d", NULL);
    //     printf("\n");
    // }

    // On crée une matrice correspondant au resultat attendu
    uint8 mat_verif[3][16] = {  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // On compare les elements un par un, si un diffère => KO
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            if(resultat[j][k] != mat_verif[j][k]){
                printf("KO\n");
                return;
            }
        }
    }

    printf("OK\n");
    free_ui8matrix(resultat, nrl, nrh, ncl, nch);
    free_ui8matrix(mat_test, nrl, nrh, ncl, nch);
}

void tests_dilatation_SIMD(){
    // On stovke toutes les fonctions de test dans un tableau de pointeur de fonctions
    void(*tests[NB_TESTS_DILATATION])() = {test_dilatation_SIMD_1, test_dilatation_SIMD_2, test_dilatation_SIMD_3, test_dilatation_SIMD_4, test_dilatation_SIMD_5, test_dilatation_SIMD_6, test_dilatation_SIMD_7};
    
    // On appelle chaque fonction une par une pour vérifier OK/KO
    for(int i = 0; i < NB_TESTS_DILATATION; i++){
        printf("Test dilatation %d\n", i+1);
        (tests[i])();
    }
}