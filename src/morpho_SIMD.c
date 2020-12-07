#include "morpho_SIMD.h"

#define R 1
#define DEROULAGE_BORDS 3
#define BORD 1

vuint8** bords_SIMD(uint8** im, int nrl, int hauteur, int ncl, int largeur, int val_Bords){

    //Creer une vui8matrix avec des bords
    //Initialiser les bords à 0, tout en dupliquant les données de l'image à
    //l'interieur
    //liberer la memoire lié à l'image de base
    //Renvoyer la nouvelle image

    int bord = 1;


    //Matrice avec bords
    vuint8** im_mat = vui8matrix(nrl-bord, hauteur+bord, ncl-bord, largeur+bord);

    //Matrice avec l'image

    vuint8** im_vect = (vuint8**) im;

    //Premiere ligne et derniere ligne
    for(int i = ncl-bord; i <= largeur+bord; i++){

        vec_store(&im_mat[nrl-bord][i], init_vuint8(val_Bords));
        vec_store(&im_mat[hauteur+bord][i], init_vuint8(val_Bords));
    }


    for(int j = nrl; j <= hauteur; j++){

        //Bord gauche
        im_mat[j][ncl-bord] = init_vuint8(val_Bords);

        //On duplique cette ligne de l'image dans le im_mat
        for (int k = ncl; k <= largeur; k++) {
            vec_store(&im_mat[j][k], im_vect[j][k]);
        }

        //Bord droit
        im_mat[j][largeur+bord] = init_vuint8(val_Bords);

    }

    return im_mat;
}


uint8** erosion_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){

    //Nombre de pixels de l'image
    int nbPixels_ligne = nch;

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels_ligne/16;

    //On alloue la matrice necessaire
    //Dimensions :
    //hauteur : -b à nrh+b
    //largeur : -b à nbVuint8+b
    int bord = 1;
    int hauteur = nrh;
    int largeur = nbVuint8;

    //Vecteurs dans lesquels nos pixels seront chargés
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    //Vecteurs nous permettant de faire nos shifts left et gauche
    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    //Vecteurs pour nos opérations AND
    vuint8 and_1ereligne;
    vuint8 and_2emeligne;
    vuint8 and_3emeligne;
    vuint8 and_noyau;

    vuint8** im_mat = bords_SIMD(im, nrl, hauteur, ncl, largeur, 1);

    //On cree une matrice qui va contenir le résultat de notre erosion
    vuint8** erosion_mat = vui8matrix(nrl, hauteur, ncl, largeur);

    //On parcourt l'image de vecteur en vecteur
    for(int j = nrl; j <= hauteur; j++){
        for(int k = ncl; k <= largeur; k++){



            a0 = vec_load(&im_mat[j-1][k-1]); b0 = vec_load(&im_mat[j-1][k]); c0 = vec_load(&im_mat[j-1][k+1]);
            a1 = vec_load(&im_mat[j  ][k-1]); b1 = vec_load(&im_mat[j  ][k]); c1 = vec_load(&im_mat[j ][k+1]);
            a2 = vec_load(&im_mat[j+1][k-1]); b2 = vec_load(&im_mat[j+1][k]); c2 = vec_load(&im_mat[j+1][k+1]);

            aa0 = vec_left1(a0, b0); cc0 = vec_right1(b0, c0);
            aa1 = vec_left1(a1, b1); cc1 = vec_right1(b1, c1);
            aa2 = vec_left1(a2, b2); cc2 = vec_right1(b2, c2);

            //AND sur chaque ligne

            and_1ereligne = vec_and3(aa0, b0, cc0);
            and_2emeligne = vec_and3(aa1, b1, cc1);
            and_3emeligne = vec_and3(aa2, b2, cc2);

            //AND du noyau

            and_noyau = vec_and3(and_1ereligne, and_2emeligne, and_3emeligne);

            //On place le résultat du AND dans la matrice resultat
            vec_store(&erosion_mat[j][k], and_noyau);
        }
    }

    // On retourne la matrice sous sa forme scalaire
    return (uint8**)erosion_mat;
}

uint8** dilatation_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){

    //Nombre de pixels de l'image
    int nbPixels_ligne = nch;

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels_ligne/16;

    //On alloue la matrice necessaire
    //Dimensions :
    //hauteur : -b à nrh+b
    //largeur : -b à nbVuint8+b
    int bord = 1;
    int hauteur = nrh;
    int largeur = nbVuint8;

    //Vecteurs dans lesquels nos pixels seront chargés
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    //Vecteurs nous permettant de faire nos shifts left et gauche
    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    //Vecteurs pour nos opérations OR
    vuint8 or_1ereligne;
    vuint8 or_2emeligne;
    vuint8 or_3emeligne;
    vuint8 or_noyau;

    //On crée une matrice vuint8** comprenant l'image avec des bords
    vuint8** im_mat = bords_SIMD(im, nrl, hauteur, ncl, largeur, 0);

    //On cree une matrice qui va contenir le résultat de notre erosion
    vuint8** dilatation_mat = vui8matrix(nrl, hauteur, ncl, largeur);

    //On parcourt l'image de vecteur en vecteur
    for(int j = nrl; j <= hauteur; j++){
        for(int k = ncl; k <= largeur; k++){


            a0 = vec_load(&im_mat[j-1][k-1]); b0 = vec_load(&im_mat[j-1][k]); c0 = vec_load(&im_mat[j-1][k+1]);
            a1 = vec_load(&im_mat[j  ][k-1]); b1 = vec_load(&im_mat[j  ][k]); c1 = vec_load(&im_mat[j  ][k+1]);
            a2 = vec_load(&im_mat[j+1][k-1]); b2 = vec_load(&im_mat[j+1][k]); c2 = vec_load(&im_mat[j+1][k+1]);

            //Shifts
            aa0 = vec_left1(a0, b0); cc0 = vec_right1(b0, c0);
            aa1 = vec_left1(a1, b1); cc1 = vec_right1(b1, c1);
            aa2 = vec_left1(a2, b2); cc2 = vec_right1(b2, c2);

            //AND sur chaque ligne
            or_1ereligne = vec_or3(aa0, b0, cc0);
            or_2emeligne = vec_or3(aa1, b1, cc1);
            or_3emeligne = vec_or3(aa2, b2, cc2);

            //AND du noyau
            or_noyau = vec_or3(or_1ereligne, or_2emeligne, or_3emeligne);

            //On place le résultat du AND dans la matrice resultat
            vec_store(&dilatation_mat[j][k], or_noyau);
        }
    }

    //On retourne la matrice sous sa forme scalaire
    return (uint8**)dilatation_mat;
}

uint8** fermeture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){
    return erosion_SIMD(dilatation_SIMD(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

uint8** ouverture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){
    return dilatation_SIMD(erosion_SIMD(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}
