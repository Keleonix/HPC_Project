#include "morpho_SIMD.h"

#define R 1                                     // On défini le rayon R pour l'espace B de convolution ici R = 1
#define DEROULAGE_MARGE 3
#define BORD 1

vuint8** bords_SIMD(uint8** im, int nrl, int hauteur, int ncl, int largeur){

    //1ERE SOLUTION, PEUT ETRE AMELIOREE
    //Creer une vui8matrix avec des bords
    //Initialiser les bords à 0, tout en dupliquant les données de l'image à
    //l'interieur
    //liberer la memoire lié à l'image de base
    //Renvoyer la nouvelle image

    //METHODE NAIVE
    int bord = 1;


    //Matrice avec bords
    vuint8** im_mat = vui8matrix(nrl-bord, hauteur+bord, ncl-bord, largeur+bord);
    //printf("Matrice avec bords\n");

    //Matrice avec l'image

    vuint8** im_vect = (vuint8**) im;
    //printf("Matrice avec l'image\n");

    //Premiere ligne et derniere ligne
    for(int i = ncl-bord; i <= largeur+bord; i++){

        vec_store(&im_mat[nrl-bord][i], init_vuint8(0));
        vec_store(&im_mat[hauteur+bord][i], init_vuint8(0));
    }
    //printf("Premiere ligne et derniere ligne de la matrice avec bords\n");


    for(int j = nrl; j <= hauteur; j++){

        //Bord gauche
        im_mat[j][ncl-bord] = init_vuint8(0);

        //On duplique cette ligne de l'image dans le im_mat
        // dup_vui8vector(im_vect[j], ncl, largeur, im_mat[j]);

        //Equivalent à :
        for (int k = ncl; k <= largeur; k++) {
            vec_store(&im_mat[j][k], im_vect[j][k]);
        }

        //Bord droit
        im_mat[j][largeur+bord] = init_vuint8(0);

    }

    // free_vui8matrix(im_vect)

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

    //printf("Dimensions :\n");
    //printf("hauteur : %d \n", hauteur);
    //printf("largeur : %d \n", largeur);
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

   //On crée une matrice vuint8** comprenant l'image avec des bords
   //TODO: trouver un meilleur
   vuint8** im_mat = bords_SIMD(im, nrl, hauteur, ncl, largeur);
   //printf("Matrice d'image avec bords\n\n");
   for(int i = nrl-BORD; i <= hauteur+BORD; i++){
       for(int j = ncl-BORD; j <= largeur+BORD; j++){
           //printf("Vecteur [%d][%d] : ", i, j);
           //display_vuint8(im_mat[i][j], "%d ", NULL);
           //printf("\n");
       }
   }

   //On cree une matrice qui va contenir le résultat de notre erosion
   vuint8** erosion_mat = vui8matrix(nrl, hauteur, ncl, largeur);

   //On libère la mémoire lié à l'image
   free_ui8matrix(im, nrl, nrh, ncl, nch);


    //On parcourt l'image de vecteur en vecteur
    for(int j = nrl; j <= hauteur; j++){
        for(int k = ncl; k <= largeur; k++){



            a0 = vec_load(&im_mat[j-1][k-1]); b0 = vec_load(&im_mat[j-1][k]); c0 = vec_load(&im_mat[j-1][k+1]);
            //Affichage des vecteurs loades
            //printf("Affichage des vecteurs loadés \n\n");
            //display_vuint8(a0, "%d ", "a0 = ");
            //printf("\n");
            //display_vuint8(b0, "%d ", "b0 = ");
            //printf("\n");
            //display_vuint8(c0, "%d ", "c0 = ");
            //printf("\n");
            a1 = vec_load(&im_mat[j  ][k-1]); b1 = vec_load(&im_mat[j  ][k]); c1 = vec_load(&im_mat[j ][k+1]);
            //Affichage des vecteurs loades
            //display_vuint8(a1, "%d ", "a1 = ");
            //printf("\n");
            //display_vuint8(b1, "%d ", "b1 = ");
            //printf("\n");
            //display_vuint8(c1, "%d ", "c1 = ");
            //printf("\n");
            a2 = vec_load(&im_mat[j+1][k-1]); b2 = vec_load(&im_mat[j+1][k]); c2 = vec_load(&im_mat[j+1][k+1]);
            //Affichage des vecteurs loades
            //display_vuint8(a2, "%d ", "a2 = ");
            //printf("\n");
            //display_vuint8(b2, "%d ", "b2 = ");
            //printf("\n");
            //display_vuint8(c2, "%d ", "c2 = ");
            //printf("\n");

            //Shifts

            aa0 = vec_left1(a0, b0); cc0 = vec_right1(b0, c0);
            //printf("Affichage des shifts \n\n");
            //display_vuint8(aa0, "%d ", "aa0 = ");
            //printf("\n");
            //display_vuint8(cc0, "%d ", "cc0 = ");
            //printf("\n");

            aa1 = vec_left1(a1, b1); cc1 = vec_right1(b1, c1);
            //display_vuint8(aa1, "%d ", "aa1 = ");
            //printf("\n");
            //display_vuint8(cc1, "%d ", "cc1 = ");
            //printf("\n");

            aa2 = vec_left1(a2, b2); cc2 = vec_right1(b2, c2);
            //display_vuint8(aa2, "%d ", "aa2 = ");
            //printf("\n");
            //display_vuint8(cc2, "%d ", "cc2 = ");
            //printf("\n");

            //AND sur chaque ligne

            and_1ereligne = vec_and3(aa0, b0, cc0);
            and_2emeligne = vec_and3(aa1, b1, cc1);
            and_3emeligne = vec_and3(aa2, b2, cc2);
            //printf("Affichage des vecteurs AND\n\n");
            // //display_vuint8(and_1ereligne, "%d ", "and_1ereligne = ");
            // //printf("\n");
            // //display_vuint8(and_2emeligne, "%d ", "and_2emeligne = ");
            // //printf("\n");
            // //display_vuint8(and_3emeligne, "%d ", "and_3emeligne = ");
            //printf("\n");


            //AND du noyau

            and_noyau = vec_and3(and_1ereligne, and_2emeligne, and_3emeligne);
            // //printf("Affichage du AND noyau \n\n");
            // //display_vuint8(and_noyau, "%d ", "and_noyau = ");
            // //printf("\n");

            //On place le résultat du AND dans la matrice resultat
            vec_store(&erosion_mat[j][k], and_noyau);
            //printf("Affichage de la donnée storée\n\n");
            //printf("Numéro [%d][%d]", j, k);
            // //display_vuint8(erosion_mat[j][k], "%d ", "and_store = ");
            //printf("\n");
        }
    }

    //On retourne la matrice sous sa forme scalaire
    //TODO: Utiliser une fonction convertissant dans le cas où le nombre de pixels par
    //ligne n'est pas multiple de 16 ?
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
   //TODO: trouver un meilleur
   vuint8** im_mat = bords_SIMD(im, nrl, hauteur, ncl, largeur);

   //On cree une matrice qui va contenir le résultat de notre erosion
   vuint8** dilatation_mat = vui8matrix(nrl, hauteur, ncl, largeur);

   //On libère la mémoire lié à l'image
   free_ui8matrix(im, nrl, nrh, ncl, nch);


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

    //On libère la mémoire associé à im_mat

    //On retourne la matrice sous sa forme scalaire
    return (uint8**)dilatation_mat;
}

uint8** fermeture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){
    return erosion_SIMD(dilatation_SIMD(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

uint8** ouverture_SIMD(uint8** im, int nrl, int nrh, int ncl, int nch){
    return dilatation_SIMD(erosion_SIMD(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

// //TODO : A etudier par la suite pour l'optimisation
// void bords_SIMD_opti(uint8** im, int nrl, int* nrh, int ncl, int* nch){
//     int i, j, n, r;
//     vuint8 im0, im1, im2;
//     vuint8** marginIm;
//
//     marginIm = vui8matrix(nrl - R, nrh + R, ncl - R, nch + R);
//     //Slide 17 NRC
//     //Prendre l'image, caster sur vuint8**
//     //Dupliquer les bords
//
//     n = *nrh + 2*R;                                                         // prologue 1
//     r = n % DEROULAGE_MARGE;
//     for(i = nrl; i < n-r; i += DEROULAGE_MARGE){                            //boucle 1
//         marginIm[i][ncl   ] = 0; marginIm[i+1][ncl   ] = 0; marginIm[i+2][ncl     ] = 0;
//         marginIm[i][*nch+R] = 0; marginIm[i+1][*nch+R] = 0; marginIm[i+2][*nch+2*R] = 0;
//     }
//     switch(r){                                                              //epilogue 1
//         case 2:
//             marginIm[i+1][ncl     ] = 0;
//             marginIm[i+1][*nch+2*R] = 0;
//         case 1:
//             marginIm[i][ncl     ] = 0;
//             marginIm[i][*nch+2*R] = 0;
//         default:
//             break;
//     }
//
//     n = *nch + 2*R;                                                         // prologue 2
//     r = n % DEROULAGE_MARGE;
//     for(i = ncl; i < n-r; i += DEROULAGE_MARGE){                            //boucle 2
//         marginIm[nrl     ][j] = 0; marginIm[nrl     ][j+1] = 0; marginIm[nrl     ][j+2] = 0;
//         marginIm[*nrh+2*R][j] = 0; marginIm[*nrh+2*R][j+1] = 0; marginIm[*nrh+2*R][j+2] = 0;
//     }
//     switch(r){                                                              //epilogue 2
//         case 2:
//             marginIm[nrl     ][j+1] = 0;
//             marginIm[*nrh+2*R][j+1] = 0;
//         case 1:
//             marginIm[nrl     ][j] = 0;
//             marginIm[*nrh+2*R][j] = 0;
//         default:
//             break;
//     }
//
//     n = *nrh;                                                               // prologue 3
//     r = n % DEROULAGE_MARGE;
//     for(j = ncl; j < *nch; j++){                                            // boucle 3
//         for(i = nrl; i < *nrh; i++){
//             im0 = im[i+0][j];       im1 = im[i+1][j];       im2 = im[i+2][j];
//             marginIm[i][j] = im0;   marginIm[i+1][j] = im1; marginIm[i+2][j] = im2;
//         }
//     }
//     switch(r){                                                              // epilogue 3
//         case 2:
//             im1 = im[i+1][j];
//             marginIm[i+1][j] = im1;
//         case 1:
//             im0 = im[i+0][j];
//             marginIm[i][j] = im0;
//         default:
//             break;
//     }
//
// }
