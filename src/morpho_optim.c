#include "morpho_optim.h"
#include <omp.h>

#define R 1                                     // On défini le rayon R pour l'espace B de convolution ici R = 1
#define BORD 1
#define NUM_THREADS 4


vuint8** bords_OPTIM(uint8** im, int nrl, int hauteur, int ncl, int largeur, int val_Bords){
    //Creer une vui8matrix avec des bords
    //Initialiser les bords à 0, tout en dupliquant les données de l'image à
    //l'interieur
    //liberer la memoire lié à l'image de base
    //Renvoyer la nouvelle image

    //Matrice avec bords
    vuint8** im_mat = vui8matrix(nrl-BORD, hauteur+BORD, ncl-BORD, largeur+BORD);

    //Matrice avec l'image
    vuint8** im_vect = (vuint8**) im;
    // omp_set_num_threads(NUM_THREADS);

    //Premiere ligne et derniere ligne
    //On parallélise le parcour des boucles, en donnant l'image en variable commune,
    //ainsi que ses dimensions ncl, nrl, nch et nrh
    #pragma omp parallel for shared(im_mat)
    for(int i = ncl-BORD; i <= largeur+BORD; i++){
        vec_store(&im_mat[nrl-BORD][i], init_vuint8(val_Bords));
        vec_store(&im_mat[hauteur+BORD][i], init_vuint8(val_Bords));
    }

    for(int j = nrl; j <= hauteur; j++){

        //Bord gauche
        im_mat[j][ncl-BORD] = init_vuint8(val_Bords);

        //On duplique cette ligne de l'image dans le im_mat
        #pragma omp parallel for shared(im_mat)
        for (int k = ncl; k <= largeur; k++) {
            vec_store(&im_mat[j][k], im_vect[j][k]);
        }

        //Bord droit
        im_mat[j][largeur+BORD] = init_vuint8(val_Bords);

    }

    // free_vui8matrix(im_vect)

    return im_mat;
}


//TODO: A ajouter loop unrolling et 1 bit si on a le temps
uint8** erosion_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch){

    //Nombre de pixels de l'image
    int nbPixels_ligne = nch;

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels_ligne/16;

    //On alloue la matrice necessaire
    //Dimensions :
    //hauteur : -b à nrh+b
    //largeur : -b à nbVuint8+b
    int hauteur = nrh;
    int largeur = nbVuint8;

    //On déclare les variables de boucles
    int j;
    int k;

    //TODO: Retirer les variables inutiles/non-utilisés
    //TODO: Une fonction par optimisation ou
    //Vecteurs dans lesquels nos pixels seront chargés
    vuint8 a0, b0, c0;
    vuint8 a1, b1, c1;
    vuint8 a2, b2, c2;

    //Vecteurs nous permettant de faire nos shifts left et gauche
    vuint8 aa0, cc0;
    vuint8 aa1, cc1;
    vuint8 aa2, cc2;

    //Vecteurs pour nos opérations and
    vuint8 and_1ereligne;
    vuint8 and_2emeligne;
    vuint8 and_3emeligne;
    vuint8 and_noyau;

    vuint8** im_mat;
    vuint8** erosion_mat;

    #pragma omp sections
    {
        //On crée une matrice vuint8** comprenant l'image avec des bords
        #pragma omp section
        im_mat = bords_OPTIM(im, nrl, hauteur, ncl, largeur, 1);

        //On cree une matrice qui va contenir le résultat de notre erosion
        #pragma omp section
        erosion_mat = vui8matrix(nrl, hauteur, ncl, largeur);
    }

    //On parcourt l'image de vecteur en vecteur
    # pragma omp for schedule (dynamic) private(a1, b1)
    for(j = nrl; j <= hauteur; j++){

        //On charge a(n) et b(n) pour le début de l'algorithme (fusion)
        #pragma omp sections
        {
            #pragma omp section
            a0 = vec_load(&im_mat[j-1][ncl-1]);
            #pragma omp section
            b0 = vec_load(&im_mat[j-1][ncl]);
            #pragma omp section
            a1 = vec_load(&im_mat[j  ][ncl-1]);
            #pragma omp section
            b1 = vec_load(&im_mat[j  ][ncl]);
            #pragma omp section
            a2 = vec_load(&im_mat[j+1][ncl-1]);
            #pragma omp section
            b2 = vec_load(&im_mat[j+1][ncl]);
        }

        # pragma omp for schedule (dynamic) shared(erosion_mat) private(b0, b2, c1, aa1, cc1, and_2emeligne, and_3emeligne, and_noyau)
        for(int k = ncl; k <= largeur; k++){

            //fusion des loads et shifts
            #pragma omp sections
            {
                #pragma omp section
                c0 = vec_load(&im_mat[j-1][k+1]);
                #pragma omp section
                c1 = vec_load(&im_mat[j  ][k+1]);
                #pragma omp section
                c2 = vec_load(&im_mat[j+1][k+1]);

                #pragma omp section
                aa0 = vec_left1(a0, b0);
                #pragma omp section
                aa1 = vec_left1(a1, b1);
                #pragma omp section
                aa2 = vec_left1(a2, b2);
            }

            //and Horizontal
            #pragma omp sections
            {
                #pragma omp section
                cc0 = vec_right1(b0, c0);
                #pragma omp section
                cc1 = vec_right1(b1, c1);
                #pragma omp section
                cc2 = vec_right1(b2, c2);
            }

            #pragma omp sections
            {
                #pragma omp section
                and_1ereligne = vec_and3(aa0, b0, cc0);
                #pragma omp section
                and_2emeligne = vec_and3(aa1, b1, cc1);
                #pragma omp section
                and_3emeligne = vec_and3(aa2, b2, cc2);
            }

            //and du noyau
            and_noyau = vec_and3(and_1ereligne, and_2emeligne, and_3emeligne);

            //On place le résultat du and dans la matrice resultat
            vec_store(&erosion_mat[j][k], and_noyau);

            //Rotation registres
            a0 = b0; b0 = c0;
            a1 = b1; b1 = c1;
            a2 = b2; b2 = c2;

        }
    }

    //On retourne la matrice sous sa forme scalaire
    //TODO: Utiliser une fonction convertissant dans le cas où le nombre de pixels par
    //ligne n'est pas multiple de 16 ?
    return (uint8**)erosion_mat;
}


uint8** dilatation_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch){

    //Nombre de pixels de l'image
    int nbPixels_ligne = nch;

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels_ligne/16;

    //On alloue la matrice necessaire
    //Dimensions :
    //hauteur : -b à nrh+b
    //largeur : -b à nbVuint8+b
    int hauteur = nrh;
    int largeur = nbVuint8;

    //On déclare les variables de boucles
    int j;
    int k;

    //TODO: Retirer les variables inutiles/non-utilisés
    //TODO: Une fonction par optimisation ou
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

    vuint8** im_mat;
    vuint8** dilatation_mat;

    #pragma omp sections
    {
        //On crée une matrice vuint8** comprenant l'image avec des bords
        #pragma omp section
        im_mat = bords_OPTIM(im, nrl, hauteur, ncl, largeur, 0);

        //On cree une matrice qui va contenir le résultat de notre dilatation
        #pragma omp section
        dilatation_mat = vui8matrix(nrl, hauteur, ncl, largeur);
    }

    //On parcourt l'image de vecteur en vecteur
    # pragma omp for schedule (dynamic) private(a1, b1)
    for(j = nrl; j <= hauteur; j++){

        //On charge a(n) et b(n) pour le début de l'algorithme (fusion)
        #pragma omp sections
        {
            #pragma omp section
            a0 = vec_load(&im_mat[j-1][ncl-1]);
            #pragma omp section
            b0 = vec_load(&im_mat[j-1][ncl]);
            #pragma omp section
            a1 = vec_load(&im_mat[j  ][ncl-1]);
            #pragma omp section
            b1 = vec_load(&im_mat[j  ][ncl]);
            #pragma omp section
            a2 = vec_load(&im_mat[j+1][ncl-1]);
            #pragma omp section
            b2 = vec_load(&im_mat[j+1][ncl]);
        }

        # pragma omp for schedule (dynamic) shared(dilatation_mat) private(b0, b2, c1, aa1, cc1, or_2emeligne, or_3emeligne, or_noyau)
        for(int k = ncl; k <= largeur; k++){

            //fusion des loads et shifts
            #pragma omp sections
            {
                #pragma omp section
                c0 = vec_load(&im_mat[j-1][k+1]);
                #pragma omp section
                c1 = vec_load(&im_mat[j  ][k+1]);
                #pragma omp section
                c2 = vec_load(&im_mat[j+1][k+1]);

                #pragma omp section
                aa0 = vec_left1(a0, b0);
                #pragma omp section
                aa1 = vec_left1(a1, b1);
                #pragma omp section
                aa2 = vec_left1(a2, b2);
            }

            //or Horizontal
            #pragma omp sections
            {
                #pragma omp section
                cc0 = vec_right1(b0, c0);
                #pragma omp section
                cc1 = vec_right1(b1, c1);
                #pragma omp section
                cc2 = vec_right1(b2, c2);
            }

            #pragma omp sections
            {
                #pragma omp section
                or_1ereligne = vec_or3(aa0, b0, cc0);
                #pragma omp section
                or_2emeligne = vec_or3(aa1, b1, cc1);
                #pragma omp section
                or_3emeligne = vec_or3(aa2, b2, cc2);
            }

            //or du noyau
            or_noyau = vec_or3(or_1ereligne, or_2emeligne, or_3emeligne);

            //On place le résultat du or dans la matrice resultat
            vec_store(&dilatation_mat[j][k], or_noyau);

            //Rotation registres
            a0 = b0; b0 = c0;
            a1 = b1; b1 = c1;
            a2 = b2; b2 = c2;

        }
    }

    //On retourne la matrice sous sa forme scalaire
    return (uint8**)dilatation_mat;
}

uint8** fermeture_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch){
    return erosion_OPTIM(dilatation_OPTIM(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

uint8** ouverture_OPTIM(uint8** im, int nrl, int nrh, int ncl, int nch){
    return dilatation_OPTIM(erosion_OPTIM(im, nrl, nrh, ncl, nch), nrl, nrh, ncl, nch);
}

// //TODO : A etudier par la suite pour l'optimisation
// void bords_OPTIM_opti(uint8** im, int nrl, int* nrh, int ncl, int* nch){
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
//     r = n % DEROULAGE_BORDS;
//     for(i = nrl; i < n-r; i += DEROULAGE_BORDS){                            //boucle 1
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
//     r = n % DEROULAGE_BORDS;
//     for(i = ncl; i < n-r; i += DEROULAGE_BORDS){                            //boucle 2
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
//     r = n % DEROULAGE_BORDS;
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