#include "test_mouvement_SIMD.h"

//Deux images par fonction
//Taille 3x16

void tests_mouvement_SIMD(){
    //Tests pour l'etape 1
    test1_step1_SIMD_OK();
    test2_step1_SIMD_OK();
    test3_step1_SIMD_OK();

    //Tests pour l'etape 2
    test1_step2_SIMD_OK();
    test2_step2_SIMD_OK();
    test3_step2_SIMD_OK();

    //Tests pour l'etape 3
    test1_step3_SIMD_OK();
    test2_step3_SIMD_OK();
    test3_step3_SIMD_OK();

    //Tests pour l'etape 4
    test1_step4_SIMD_OK();
    test2_step4_SIMD_OK();
    test3_step4_SIMD_OK();
}


void test1_step1_SIMD_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree une ui8matrix pour Mt_1
    uint8** Mt_1 = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 0;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
            if(debut < 255) debut++;
        }
    }

    //On copie dans une autre matrice
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt_1[i][j];

            if(i == 0){ //On augmente de 1 sur la premiere ligne
                It[i][j] += 1;
            }
            //On ne fait pas de changement sur la ligne du milieu

            else if(i == 2){//On descend de 1 sur la dernière ligne
                It[i][j] -= 1;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);


    SigmaDelta_step1_SIMD(It_vect, Mt_1_vect, Mt_vect, nbVuint8);

    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Mt_vect, nrl, nrh, ncl, nch, Mt);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test1_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test1_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test1_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_1_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);

    printf("test1_step1_SIMD_OK validé, OK\n");
}

void test2_step1_SIMD_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree une ui8matrix pour Mt_1
    uint8** Mt_1 = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 50;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
            if(debut < 255) debut++;
        }
    }

    //On copie dans une autre matrice
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt_1[i][j];

            if(i == 0){ //On augmente de 1 sur la premiere ligne
                It[i][j] += 1;
            }
            //On ne fait pas de changement sur la ligne du milieu

            else if(i == 2){//On descend de 1 sur la dernière ligne
                It[i][j] -= 1;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);


    SigmaDelta_step1_SIMD(It_vect, Mt_1_vect, Mt_vect, nbVuint8);

    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Mt_vect, nrl, nrh, ncl, nch, Mt);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test2_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test2_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test2_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_1_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);

    printf("test2_step1_SIMD_OK validé, OK\n");
}

void test3_step1_SIMD_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree une ui8matrix pour Mt_1
    uint8** Mt_1 = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 100;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
            if(debut < 255) debut++;
        }
    }

    //On copie dans une autre matrice
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt_1[i][j];

            if(i == 0){ //On augmente de 1 sur la premiere ligne
                It[i][j] += 1;
            }
            //On ne fait pas de changement sur la ligne du milieu

            else if(i == 2){//On descend de 1 sur la dernière ligne
                It[i][j] -= 1;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);


    SigmaDelta_step1_SIMD(It_vect, Mt_1_vect, Mt_vect, nbVuint8);

    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Mt_vect, nrl, nrh, ncl, nch, Mt);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test3_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test3_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test3_step1_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_1_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);

    printf("test3_step1_SIMD_OK validé, OK\n");
}


void test1_step2_SIMD_OK(){
    //L'etape 2 consiste à faire Ot = abs(Mt - It)
    //On veut que Mt - It donne des resultats negatifs sur la premiere ligne
    //positifs sur la deuxieme
    //et negatifs sur la troisième
    //afin de verifier que l'operation abs est bien réalisée

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Mt, It, Ot
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 50;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt[i][j] = debut;
            if(debut < 255) debut++;
        }
    }

    int ecart = 10; //L'ecart entre It et Mt

    //On copie dans la matrice It
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt[i][j];

            if(i == 0){ //It > Mt sur la premiere ligne
                It[i][j] += ecart;
            }
            else if(i == 1){//It < Mt sur la deuxieme ligne
                It[i][j] -= ecart;
            }
            else if(i == 2){//It > Mt sur la troisieme ligne
                It[i][j] += ecart;
            }

        }
    }
    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt, nrl, nrh, ncl, nch, Mt_vect);

    SigmaDelta_step2_SIMD(It_vect, Mt_vect, Ot_vect, nbVuint8);

    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Ot_vect, nrl, nrh, ncl, nch, Ot);

    //Nous verifions maintenant le résultat
    //On doit avoir ecart sur chaque pixel partout

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test1_step2_SIMD_OK faux, KO\n");
                    return;
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);

    printf("test1_step2_SIMD_OK validé, OK\n");
}

void test2_step2_SIMD_OK(){
    //L'etape 2 consiste à faire Ot = abs(Mt - It)
    //On veut que Mt - It donne des resultats positifs sur la premiere ligne
    //negatifs sur la deuxieme
    //et positifs sur la troisième
    //afin de verifier que l'operation abs est bien réalisée

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Mt, It, Ot
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 100;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt[i][j] = debut;
            if(debut < 255) debut++;
        }
    }

    int ecart = 20; //L'ecart entre It et Mt

    //On copie dans la matrice It
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt[i][j];

            if(i == 0){ //It > Mt sur la premiere ligne
                It[i][j] -= ecart;
            }
            else if(i == 1){//It < Mt sur la deuxieme ligne
                It[i][j] += ecart;
            }
            else if(i == 2){//It > Mt sur la troisieme ligne
                It[i][j] -= ecart;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt, nrl, nrh, ncl, nch, Mt_vect);


    SigmaDelta_step2_SIMD(It_vect, Mt_vect, Ot_vect, nbVuint8);

    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Ot_vect, nrl, nrh, ncl, nch, Ot);

    //Nous verifions maintenant le résultat
    //On doit avoir ecart sur chaque pixel partout

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test2_step2_SIMD_OK faux, KO\n");
                    return;
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);

    printf("test2_step2_SIMD_OK validé, OK\n");
}

void test3_step2_SIMD_OK(){
    //L'etape 2 consiste à faire Ot = abs(Mt - It)
    //On veut que Mt - It donne des resultats negatifs sur la premiere ligne
    //positifs sur la deuxieme
    //et negatifs sur la troisième
    //afin de verifier que l'operation abs est bien réalisée

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Mt, It, Ot
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 200;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt[i][j] = debut;
        }
    }

    int ecart = 1; //L'ecart entre It et Mt

    //On copie dans la matrice It
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt[i][j];

            if(i == 0){ //It > Mt sur la premiere ligne
                It[i][j] -= ecart;
            }
            else if(i == 1){//It < Mt sur la deuxieme ligne
                It[i][j] += ecart;
            }
            else if(i == 2){//It > Mt sur la troisieme ligne
                It[i][j] -= ecart;
            }

            ecart++;

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt, nrl, nrh, ncl, nch, Mt_vect);


    SigmaDelta_step2_SIMD(It_vect, Mt_vect, Ot_vect, nbVuint8);

    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Ot_vect, nrl, nrh, ncl, nch, Ot);

    //Nous verifions maintenant le résultat
    //On doit avoir 1 [...] 15 sur la première ligne
    //16 [..] 31 sur la deuxieme
    //32 [...]47 sur la troisieme

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test3_step2_SIMD_OK faux, KO\n");
                    return;
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_vui8vector(It_vect, 0, nbPixels);
    free_vui8vector(Mt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);

    printf("test3_step2_SIMD_OK validé, OK\n");
}

void test1_step3_SIMD_OK(){
    //L'etape 3 compare les pixels de Vt_1 et ceux de Ot multiplié
    //par un facteur N = 3, avant d'utiliser les macros MIN et MAX afin que
    //Vt soit toujours compris entre 1 et 254

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Vt_1, Ot, Vt
    uint8** Vt_1 = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //On met tous les pixels de Ot à 0
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = 0;
        }
    }

    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){

            if(i == 0){ //On met la ligne à 1
                Vt_1[i][j] = 1;
            }

            else if(i == 0){//On met la ligne à 0
                Vt_1[i][j] = 0;
            }
            else if(i == 2){//On met la ligne à 124
                Vt_1[i][j] = 124;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt_1, nrl, nrh, ncl, nch, Vt_1_vect);

    //On teste la fonction
    SigmaDelta_step3_SIMD(Ot_vect, Vt_1_vect, Vt_vect, nbVuint8);

    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Vt_vect, nrl, nrh, ncl, nch, Vt);



    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMIN
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à 123
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != VMIN){
                    printf("test1_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != VMIN){
                    printf("test1_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != 123){
                    printf("test1_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Vt_1_vect, 0, nbPixels);
    printf("test1_step3_SIMD_OK validé, OK\n");

}

void test2_step3_SIMD_OK(){
    //L'etape 3 compare les pixels de Vt_1 et ceux de Ot multiplié
    //par un facteur N = 3, avant d'utiliser les macros MIN et MAX afin que
    //Vt soit toujours compris entre 1 et 254

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Vt_1, Ot, Vt
    uint8** Vt_1 = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //On met tous les pixels de Ot à 85
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = 85;
        }
    }
    //Comme N = 3, tous les elements d'Ot seront à 255

    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){

            if(i == 0){ //On met la ligne à 254
                Vt_1[i][j] = 254;
            }

            else if(i == 1){//On met la ligne à 0
                Vt_1[i][j] = 0;
            }
            else if(i == 2){//On met la ligne à 255
                Vt_1[i][j] = 255;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt_1, nrl, nrh, ncl, nch, Vt_1_vect);

    //On teste la fonction
    SigmaDelta_step3_SIMD(Ot_vect, Vt_1_vect, Vt_vect, nbVuint8);

    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Vt_vect, nrl, nrh, ncl, nch, Vt);


    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != VMAX){
                    printf("test2_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != VMIN){
                    printf("test2_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != VMAX){
                    printf("test2_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Vt_1_vect, 0, nbPixels);

    printf("test2_step3_SIMD_OK validé, OK\n");
}

void test3_step3_SIMD_OK(){
    //L'etape 3 compare les pixels de Vt_1 et ceux de Ot multiplié
    //par un facteur N = 3, avant d'utiliser les macros MIN et MAX afin que
    //Vt soit toujours compris entre 1 et 254

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Vt_1, Ot
    uint8** Vt_1 = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //On met tous les pixels de Ot à 43
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = 43;
        }
    }
    //Comme N = 3, tous les elements d'Ot seront à 129

    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){

            if(i == 0){ //On met la ligne à 127
                Vt_1[i][j] = 127;
            }

            else if(i == 1){//On met la ligne à 63
                Vt_1[i][j] = 63;
            }
            else if(i == 2){//On met la ligne à 200
                Vt_1[i][j] = 200;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt_1, nrl, nrh, ncl, nch, Vt_1_vect);

    //On teste la fonction
    SigmaDelta_step3_SIMD(Ot_vect, Vt_1_vect, Vt_vect, nbVuint8);

    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Vt_vect, nrl, nrh, ncl, nch, Vt);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != 128){
                    printf("test3_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != 64){
                    printf("test3_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != 199){
                    printf("test3_step3_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Vt_1_vect, 0, nbPixels);

    printf("test3_step3_SIMD_OK validé, OK\n");
}

void test1_step4_SIMD_OK(){

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //Ot [50, 97]
    int debut = 50;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = debut;
            debut++;
        }
    }


    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){

            if(i == 0){ //On met la ligne à 100
                Vt[i][j] = 100;
            }

            else if(i == 1){//On met la ligne à 40
                Vt[i][j] = 40;
            }
            else if(i == 2){//On met la ligne à 90
                Vt[i][j] = 90;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt, nrl, nrh, ncl, nch, Vt_vect);

    //On teste la fonction
    SigmaDelta_step4_SIMD(Ot_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);


    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Et[i][j] != 0){
                    printf("test1_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Et[i][j] != 1){
                    printf("test1_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(j < 8 && Et[i][j] != 0){
                    printf("test1_step4_SIMD_OK faux, KO\n");
                    return;
                }
                else if(j > 8 && Et[i][j] != 0){
                    printf("test1_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Et_vect, 0, nbPixels);

    printf("test1_step4_SIMD_OK validé, OK\n");
}

void test2_step4_SIMD_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //Ot [50, 97]
    int debut = 100;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = debut;
            debut++;
        }
    }

    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Vt[i][j] = Ot[i][j];

            if((i*16+j)%3 == 0){
                Vt[i][j]++; //Si Vt > Ot, Et = 0
            }
            else if((i*16+j)%3 == 1){
                Vt[i][j]--; //Si Vt <= Ot, Et = 1
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt, nrl, nrh, ncl, nch, Vt_vect);

    //On teste la fonction
    SigmaDelta_step4_SIMD(Ot_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if((i*16+j)%3 == 0){
                if(Et[i][j] != 0){
                    printf("test2_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else if((i*16+j)%3 == 1){
                if(Et[i][j] != 1){
                    printf("test2_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else{
                if(Et[i][j] != 1){
                    printf("test2_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Et_vect, 0, nbPixels);

    printf("test2_step4_SIMD_OK validé, OK\n");
}

void test3_step4_SIMD_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

    //On teste si les valeurs restent comprises entre
    //Vmin et Vmax

    //Ot [50, 97]
    int debut = 100;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Ot[i][j] = debut;
            debut++;
        }
    }

    //On copie dans une autre matrice
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Vt[i][j] = Ot[i][j];

            if(i == 20){
                Vt[i][j]++; //Si Vt > Ot, Et = 0
            }
        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);

    copy_ui8matrix_vui8vector(Ot, nrl, nrh, ncl, nch, Ot_vect);
    copy_ui8matrix_vui8vector(Vt, nrl, nrh, ncl, nch, Vt_vect);

    //On teste la fonction
    SigmaDelta_step4_SIMD(Ot_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 20){
                if(Et[i][j] != 0){
                    printf("test3_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
            else{
                if(Et[i][j] != 1){
                    printf("test2_step4_SIMD_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);
    free_vui8vector(Vt_vect, 0, nbPixels);
    free_vui8vector(Ot_vect, 0, nbPixels);
    free_vui8vector(Et_vect, 0, nbPixels);

    printf("test2_step4_SIMD_OK validé, OK\n");
}
