// Pour les tests :
// @YounesC vous pouvez faire des tests unitaires
// sur des toutes petites images
// et en pré-calculant à la main les résultats que vous devez obtenir
// mais ensuite une fois que vous avez validé manuellement une version
// (la plus simple si possible) servez-vous en de référence pour vérifier les
// résultats des autres versions

//Deux images par fonction
//Taille 3x16

void test1_step1_OK(){
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

    //On teste la fonction
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    SigmaDelta_step1(It, Mt_1, Mt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test1_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test1_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test1_step1_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

    printf("test1_step1_OK validé, OK\n");
}

void test2_step1_OK(){
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

    //On teste la fonction
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    SigmaDelta_step1(It, Mt_1, Mt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test2_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test2_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test2_step1_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

    printf("test2_step1_OK validé, OK\n");
}

void test3_step1_OK(){
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

    //On teste la fonction
    uint8** Mt = ui8matrix(nrl, nrh, ncl, nch);
    SigmaDelta_step1(It, Mt_1, Mt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à Mt+1
    //La deuxieme ligne doit être égale à Mt
    //La troisième ligne doit être à Mt-1
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Mt[i][j] != Mt_1[i][j]+1){
                    printf("test3_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Mt[i][j] != Mt_1[i][j]){
                    printf("test3_step1_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Mt[i][j] != Mt_1[i][j]-1){
                    printf("test3_step1_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(It, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt, nrl, nrh, ncl, nch);
    free_ui8matrix(Mt_1, nrl, nrh, ncl, nch);

    printf("test3_step1_OK validé, OK\n");
}


void test1_step2_OK(){
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
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 50;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
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

    //On teste la fonction
    SigmaDelta_step2(It, Mt, Ot, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //On doit avoir ecart sur chaque pixel partout

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test1_step2_OK faux, KO\n");
                    return;
            }
        }
    }

    printf("test1_step2_OK validé, OK\n");
}

void test2_step2_OK(){
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
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 100;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
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

    //On teste la fonction
    SigmaDelta_step2(It, Mt, Ot, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //On doit avoir ecart sur chaque pixel partout

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test2_step2_OK faux, KO\n");
                    return;
            }
        }
    }

    printf("test2_step2_OK validé, OK\n");
}

void test3_step2_OK(){
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
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);

    //On la remplit avec des données
    int debut = 200;
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            Mt_1[i][j] = debut;
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

    //On teste la fonction
    SigmaDelta_step2(It, Mt, Ot, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //On doit avoir 1 [...] 15 sur la première ligne
    //16 [..] 31 sur la deuxieme
    //32 [...]47 sur la troisieme

    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(Ot[i][j] != ecart){
                    printf("test3_step2_OK faux, KO\n");
                    return;
            }
        }
    }

    printf("test3_step2_OK validé, OK\n");
}

void test1_step3_OK(){
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
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step3(Ot, Vt_1, Vt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMIN
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à 123
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != VMIN){
                    printf("test1_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != VMIN){
                    printf("test1_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != 123){
                    printf("test1_step3_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);

    printf("test1_step3_OK validé, OK\n");

}

void test2_step3_OK(){
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
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step3(Ot, Vt_1, Vt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != VMAX){
                    printf("test2_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != VMIN){
                    printf("test2_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != VMAX){
                    printf("test2_step3_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);

    printf("test2_step3_OK validé, OK\n");
}

void test3_step3_OK(){
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
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step3(Ot, Vt_1, Vt, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Vt[i][j] != 128){
                    printf("test3_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Vt[i][j] != 64){
                    printf("test3_step3_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(Vt[i][j] != 199){
                    printf("test3_step3_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Vt_1, nrl, nrh, ncl, nch);

    printf("test3_step3_OK validé, OK\n");
}

void test1_step4_OK(){

    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step4(Ot, Vt, Et, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 0){
                if(Et[i][j] != 0){
                    printf("test1_step4_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 1){
                if(Et[i][j] != 1){
                    printf("test1_step4_OK faux, KO\n");
                    return;
                }
            }
            else if(i == 2){//On descend de 1 sur la dernière ligne
                if(j < 8 && Et[i][j] != 0){
                    printf("test1_step4_OK faux, KO\n");
                    return;
                }
                else if(j > 8 && Et[i][j] != 0){
                    printf("test1_step4_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);

    printf("test1_step4_OK validé, OK\n");
}

void test2_step4_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step4(Ot, Vt, Et, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if((i*16+j)%3 == 0){
                if(Et[i][j] != 0){
                    printf("test2_step4_OK faux, KO\n");
                    return;
                }
            }
            else if((i*16+j)%3 == 1){
                if(Et[i][j] != 1){
                    printf("test2_step4_OK faux, KO\n");
                    return;
                }
            }
            else{
                if(Et[i][j] != 1){
                    printf("test2_step4_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);

    printf("test2_step4_OK validé, OK\n");
}

void test3_step4_OK(){
    int i, j;
    int nrl = 0;
    int nrh = 2;
    int ncl = 0;
    int nch = 15;

    //On cree des ui8matrix pour Ot, Vt, Et
    uint8** Ot = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Vt = ui8matrix(nrl, nrh, ncl, nch);
    uint8** Et = ui8matrix(nrl, nrh, ncl, nch);

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

    //On teste la fonction
    SigmaDelta_step4(Ot, Vt, Et, &nrl, &nrh, &ncl, &nch);

    //Nous verifions maintenant le résultat
    //La première ligne doit être égale à VMAX
    //La deuxieme ligne doit être égale à VMIN
    //La troisième ligne doit être égale à VMAX
    //Si on detecte une erreur, on renvoie la fonction
    for(i = nrl; i <= nrh; i++){
        for(j = ncl; j <= nch; j++){
            if(i == 20){
                if(Et[i][j] != 0){
                    printf("test3_step4_OK faux, KO\n");
                    return;
                }
            }
            else{
                if(Et[i][j] != 1){
                    printf("test2_step4_OK faux, KO\n");
                    return;
                }
            }
        }
    }

    free_ui8matrix(Vt, nrl, nrh, ncl, nch);
    free_ui8matrix(Ot, nrl, nrh, ncl, nch);
    free_ui8matrix(Et, nrl, nrh, ncl, nch);

    printf("test2_step4_OK validé, OK\n");
}
