#include "test_mouvement_optim.h"

//Faire des matrices lancer l'algo steps_OPTIM
//Regarder le resultat, faire des if avec KO

void tests_mouvement_OPTIM(){
    test1_steps_OK();
    test2_steps_OK();
    test3_steps_OK();
}

void test1_steps_OK(){
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
            // if(debut < 255) debut++;
        }
    }

    //On copie dans une autre matrice
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt_1[i][j];

            if(i == 0){ //On augmente de 5 sur la premiere ligne
                It[i][j] += 5;
            }
            //On ne fait pas de changement sur la ligne du milieu

            else if(i == 2){//On descend de 5 sur la dernière ligne
                It[i][j] -= 5;
            }

        }
    }


    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    //On teste la fonction
    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    for(int i = 0; i < nbVuint8; i++){
        Vt_1_vect[i] = init_vuint8((uint8)VMIN);
    }

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);

    SigmaDelta_steps_OPTIM(It_vect, Mt_1_vect, Mt_vect, Ot_vect, Vt_1_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);

    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Et[i][j] != 1){
                    printf("test1_steps_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Et[i][j] != 0){
                    printf("test1_steps_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 5 sur la dernière ligne
                if(Et[i][j] != 1){
                    printf("test1_steps_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    printf("test1_steps_OK vrai, OK\n");
}


void test2_steps_OK(){
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
            // if(debut < 255) debut++;
        }
    }

    //On copie dans une autre matrice
    uint8** It = ui8matrix(nrl, nrh, ncl, nch);
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            It[i][j] = Mt_1[i][j];

            if(i == 0){ //On augmente de 5 sur la premiere ligne
                if(j > 5){
                    It[i][j] += 5;
                }
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;



    //On teste la fonction
    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    for(int i = 0; i < nbVuint8; i++){
        Vt_1_vect[i] = init_vuint8((uint8)VMIN);
    }

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);

    SigmaDelta_steps_OPTIM(It_vect, Mt_1_vect, Mt_vect, Ot_vect, Vt_1_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);

    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Et[i][j] != 1){
                    if(j > 5){
                        printf("test2_steps_OK faux, KO\n");
                        return;
                    }
                }
            }
            else if(i == 1){
                if(Et[i][j] != 0){
                    printf("test2_steps_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 5 sur la dernière ligne
                if(Et[i][j] != 0){
                    printf("test2_steps_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    printf("test2_steps_OK vrai, OK\n");
}

void test3_steps_OK(){
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

            if(i == 1){ //On augmente de 5 sur la ligne du milieu
                It[i][j] += 5;
            }
            else if(i == 2){//On descend de 5 sur la dernière ligne
                It[i][j] -= 5;
            }

        }
    }

    //On copie dans un vuint8 *
    int nbPixels = (nrh+1)*(nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    //On teste la fonction
    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1_vect = vui8vector(0, nbPixels);
    vuint8* Vt_1_vect = vui8vector(0, nbPixels);
    vuint8* Mt_vect = vui8vector(0, nbPixels);
    vuint8* Vt_vect = vui8vector(0, nbPixels);
    vuint8* Ot_vect = vui8vector(0, nbPixels);
    vuint8* Et_vect = vui8vector(0, nbPixels);
    vuint8* It_vect = vui8vector(0, nbPixels);

    for(int i = 0; i < nbVuint8; i++){
        Vt_1_vect[i] = init_vuint8((uint8)VMIN);
    }

    copy_ui8matrix_vui8vector(It, nrl, nrh, ncl, nch, It_vect);
    copy_ui8matrix_vui8vector(Mt_1, nrl, nrh, ncl, nch, Mt_1_vect);

    SigmaDelta_steps_OPTIM(It_vect, Mt_1_vect, Mt_vect, Ot_vect, Vt_1_vect, Vt_vect, Et_vect, nbVuint8);

    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);
    copy_vui8vector_ui8matrix(Et_vect, nrl, nrh, ncl, nch, Et);

    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Et[i][j] != 0){
                        printf("test3_steps_OK faux, KO\n");
                        return;
                }
            }
            else if(i == 1){
                if(Et[i][j] != 1){
                    printf("test3_steps_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 5 sur la dernière ligne
                if(Et[i][j] != 1){
                    printf("test3_steps_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    printf("test3_steps_OK vrai, OK\n");
}
