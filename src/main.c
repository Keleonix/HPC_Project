/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mouvement.h"
// #include "test_mouvement.h"
// #include "bench_mouvement.h"

#include "mouvement_SIMD.h"

#define VMIN 1
#define VMAX 254
#define N 3
#define NOMBRE_IMAGE 199

// void info(void)
// {
// #ifdef ENABLE_BENCHMARK
//     puts("mode Benchmark ON");
//     puts("DEBUG OFF");
// #else
//     puts("mode Benchmark OFF");
//     puts("DEBUG ON");
// #endif
// }

void copy_ui8matrix_vui8vector(uint8** mat, long nrl, long nrh, long ncl, long nch, vuint8* vect){

    int nbVect = (nch+1)/16; //Nombre de vecteur par ligne
    int i = 0; //Indice pour vui8vector
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k+=16){
            //TODO:Remplacer par _mm_set_epi8 ?
            vect[i] = init_vuint8_all(mat[j][k  ], mat[j][k+1], mat[j][k+2], mat[j][k+3], \
                                    mat[j][k+4], mat[j][k+5], mat[j][k+6], mat[j][k+7], \
                                    mat[j][k+8], mat[j][k+9], mat[j][k+10], mat[j][k+11], \
                                    mat[j][k+12], mat[j][k+13], mat[j][k+14], mat[j][k+15]);
            i++;
        }
    }
}

//Multiplie deux vuint8, a et b, entre eux et renvoie le produit c
vuint8 vi8_mul(vuint8 a, vuint8 b){

    vuint8 A[1];
    vuint8 B[1];
    vuint8 C[1];

    uint8* a_ = (uint8*) A;
    uint8* b_ = (uint8*) B;
    uint8* c_ = (uint8*) C;

    //vec_st(x, 0, T);
    _mm_store_si128(A, a);
    _mm_store_si128(B, b);

    for(int i = 0; i < 16; i++){
        c_[i] = a_[i]*b_[i];
    }

    return C[0];
}

//Applique abs au vecteur en faisant un if(vect < 0)
vuint8 vi8_abs(vuint8 vect){

    vuint8 cmp, neg, pos, ABS;

    cmp = _mm_cmpgt_epi8(init_vuint8(0), vect);//A 1, tous les uint8 < 0
    neg = _mm_and_si128(cmp, vect); //Vecteur avec seulement les nombres negatifs
    pos = _mm_andnot_si128(cmp, vect); //Vecteur avec seulement les positifs

    neg =  vi8_mul(neg, init_vuint8(-1));//Multiplication des negatifs par -1

    ABS = _mm_or_si128(pos, neg);

    return ABS;
}

//Compare les vecteurs a et b, et renvoie un vecteur composé des MAX(a[i], b[i])
vuint8 vi8_max(vuint8 a, vuint8 b){

}

//Compare les vecteurs a et b, et renvoie un vecteur composé des MIN(a[i], b[i])
vuint8 vi8_min(vuint8 a, vuint8 b){

}

void copy_vui8vector_ui8matrix(vuint8* vect, long nrl, long nrh, long ncl, long nch, uint8** mat){

    int i = 0;
    uint8 *p = (uint8*) vect;
    for(int j = nrl; j <= nrh; j++){
        for(int k = ncl; k <= nch; k++){
            mat[j][k] = p[i];
            i++;
            //TODO: Rajouter un if controlant la valeur de i depasse le nombre de pixels
        }
    }

}

int main(){
    // info();
    //main_mouvement();
    //SIMD
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    //Chargement de l'image O
    // char image0[] = "img_test/rei2.pgm";
    char image0[] = "car3/car_3000.pgm";
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    printf("Chargement de l'image.\n");
    printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Copie de Io dans Mo, vuint8
    int p = 0; //padding
    int b = 0; //bord

    //sans bord
    int nbPixels = (*nrh+1)*(*nch+1);
    int nbVuint8 = nbPixels/16+1;
    printf("Nombre de pixels = %d, pixels restants après division = %d => Nombre de vecteurs = %d\n,", nbPixels, nbPixels%16, nbVuint8);

    //Les images de la séquence ont un nombre de pixels qui est multiple de 16
    //On va donc juste faire un tableau de vuint8 1D sans padding et on verra bien
    //Sans bord, sans padding

    //Etape 0 :
        //Parcours de Io pour remplir Mo
        vuint8* Mo = vui8vector(0, nbPixels);
        printf("Affichage de Mo quand il est encore NULL\n\n");
        display_vuint8(Mo[0],"%d\n", NULL);
        printf("Fin de l'affichage de Mo quand il est encore NULL\n\n");

        copy_ui8matrix_vui8vector(Io, *nrl, *nrh, *ncl, *nch, Mo);

        printf("Affichage de Mo après copie de Io \n\n");
        display_vuint8(Mo[0],"%d\n", NULL);
        printf("Fin de l'affichage de Mo après copie de Io\n\n");

        //Initialisation de Vo
        vuint8* Vo = vui8vector(0, nbPixels);

        printf("Affichage de Vo quand il est encore NULL\n\n");
        display_vuint8(Vo[0],"%d\n", NULL);
        printf("Fin de l'affichage de Vo quand il est encore NULL\n\n");

        for(int i = 0; i < nbVuint8; i++){
            Vo[i] = init_vuint8((uint8)VMIN);
        }

        printf("Affichage de Vo après initialisation à VMIN \n\n");
        display_vuint8(Vo[0],"%d\n", NULL);
        printf("Fin de l'affichage de Vo après initialisation à VMIN\n\n");


    //Etape 0 validée

    //Etape 1
    //Chargement de la première image
    char image1[] = "car3/car_3001.pgm";
    uint8** It = LoadPGM_ui8matrix(image1, nrl, nrh, ncl, nch);

    printf("Affichage des 16 premiers pixels de It\n\n");

    printf("%d %d %d %d %d %d %d %d ", It[0][0], It[0][1], It[0][2], It[0][3], It[0][4], It[0][5], It[0][6], It[0][7]);
    printf("%d %d %d %d %d %d %d %d\n\n", It[0][8], It[0][9], It[0][10], It[0][11], It[0][12], It[0][13], It[0][14], It[0][15]);

    printf("Fin de l'affichage des 16 premiers pixels\n\n");

    vuint8* Itvect = vui8vector(0, nbPixels);

    printf("Affichage de It avant initialisation\n\n");
    display_vuint8(Itvect[0],"%d\n", NULL);
    printf("Fin de l'affichage de Vo avant initialisation\n\n");

    copy_ui8matrix_vui8vector(It, *nrl, *nrh, *ncl, *nch, Itvect);

    printf("Affichage de It après initialisation\n\n");
    display_vuint8(Itvect[0],"%d\n", NULL);
    printf("Fin de l'affichage de Vo après initialisation\n\n");

    vuint8* Mt = vui8vector(0, nbPixels);
    vuint8 pixelsIm, pixelsM, C1, C2, K1, K2, K, M;
    for(int i = 0; i < nbVuint8; i++){
        pixelsIm = _mm_load_si128(&Itvect[i]);
        pixelsM = _mm_load_si128(&Mo[i]);

        C1 = _mm_cmpgt_epi8 (pixelsIm, pixelsM); //Sont mis à 1 tout pixel où It > main
        C2 = _mm_cmpgt_epi8 (pixelsM, pixelsIm); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
        K1 = init_vuint8(1);
        K2 = init_vuint8(-1);
        K = _mm_or_si128(_mm_and_si128(C1, K1), _mm_and_si128(C2, K2));

        M = _mm_add_epi8(K, pixelsM);
        _mm_store_si128(&Mt[i], M);

    //     if(i >= 45 && i < 47){
    //
    //         printf("Vecteur %i \n\n", i);
    //
    //         printf("It ");
    //         display_vuint8(pixelsIm,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("Mo ");
    //         display_vuint8(pixelsM, "%d ", NULL);
    //         printf("\n");
    //
    //         printf("C1 ");
    //         display_vuint8(C1,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("C2 ");
    //         display_vuint8(C2,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("K1 ");
    //         display_vuint8(K1,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("K2 ");
    //         display_vuint8(K2,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("K ");
    //         display_vuint8(K,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("M ");
    //         display_vuint8(M,"%d ", NULL);
    //         printf("\n");
    //
    //         printf("Mt ");
    //         display_vuint8(Mt[i],"%d ", NULL);
    //         printf("\n");
    //
    //         printf("Fin du vecteur %i \n\n", i);
    //     }
    }

    //Etape 1 validée

    //Etape 2
    //TODO: Faire une fonction abs_vuint8(vuint8) qui applique abs sur t
    vuint8* Ot = vui8vector(0, nbPixels);
    vuint8 O;
    for(int i = 0; i < nbVuint8; i++){
        pixelsIm = _mm_load_si128(&Itvect[i]);
        pixelsM = _mm_load_si128(&Mt[i]);

        O = _mm_sub_epi8(pixelsM, pixelsIm);
        if(i == 45){
            display_vuint8(O, "%d ", "O ");
        }
        O = vi8_abs(O);
        // O = abs(O);
        //Appliquer abs
        _mm_store_si128(&Ot[i], O);

        // if(i == 45){
        //     printf("\n");
        //     display_vuint8(pixelsM, "%d ", "Mt ");
        //     printf("\n");
        //     display_vuint8(pixelsIm, "%d ", "It ");
        //     printf("\n");
        //     display_vuint8(O, "%d ", "ABS(O)");
        //     printf("\n");
        //     display_vuint8(Ot[i], "%d ", "Ot ");
        //     printf("\n");
        // }
    }

    //Etape 3
    vuint8 vectN = init_vuint8(N);
    vuint8* Vt = vui8vector(0, nbPixels);
    vuint8 pixelsO, pixelsOtxN, pixelsVt_1, D1, D2, L, V;
    for(int i = 0; i < nbVuint8; i++){
        pixelsO = _mm_load_si128(&Ot[i]);

        //pixelsOxN
        //TODO: faire une fonction mul_epi8
        pixelsOtxN = vi8_mul(pixelsO, init_vuint8(N));
        pixelsVt_1 = _mm_load_si128(&Vo[i]);

        D1 = _mm_cmpgt_epi8 (pixelsOtxN, pixelsVt_1); //Sont mis à 1 tout pixel où N*Ot > Vt
        D2 = _mm_cmpgt_epi8 (pixelsVt_1, pixelsOtxN); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0

        L = _mm_or_si128(_mm_and_si128(D1, init_vuint8(1)), _mm_and_si128(D2, init_vuint8(-1)));

        V = _mm_add_epi8(L, pixelsVt_1);
        _mm_store_si128(&Vt[i], V);

        if(i == 45){
            printf("\n");
            display_vuint8(pixelsOtxN, "%d ", "OtxN ");
            printf("\n");
            display_vuint8(pixelsVt_1, "%d ", "Vt_1 ");
            printf("\n");
            display_vuint8(D1, "%d ", "D1 ");
            printf("\n");
            display_vuint8(D2, "%d ", "D2 ");
            printf("\n");
            display_vuint8(L, "%d ", "L ");
            printf("\n");
            display_vuint8(V, "%d ", "V ");
            printf("\n");
            printf("\n");
            display_vuint8(Vt[i], "%d ", "Vt ");
            printf("\n");
        }
    }

    //Etape 4
    vuint8* Et = vui8vector(0, nbPixels);
    vuint8 pixelsVt;
    vuint8 pixelsOt;
    vuint8 C;
    vuint8 E;

    for(int i = 0; i < nbVuint8; i++){
        pixelsVt = _mm_load_si128(&Vt[i]);
        pixelsOt = _mm_load_si128(&Ot[i]);

        C = _mm_cmplt_epi8(pixelsOt, pixelsVt); //A 0, Ot >= Vt et à 0xFF, Ot < Vt
        E = _mm_and_si128(C, init_vuint8(VMAX)); //A 0, Ot >= Vt et à VMAX, Ot < Ot
        //TODO: VMAX = 0xFF non ?
        // E = _mm_add_epi8(K, pixelsVt_1);
        _mm_store_si128(&Et[i], E);

        if(i == 45){
            printf("\n");
            display_vuint8(pixelsOt, "%d ", "Ot ");
            printf("\n");
            display_vuint8(pixelsVt, "%d ", "Vt");
            printf("\n");
            display_vuint8(C, "%d ", "C ");
            printf("\n");
            display_vuint8(E, "%d ", "E ");
            printf("\n");
            display_vuint8(Et[i], "%d ", "Et ");
            printf("\n");
        }
    }

    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
    char image[18];
    generate_filename_k_ndigit_extension("test_SIMD/Et_", 1, 0, "pgm", image);
    SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);



    //On calcule le nombre de vecteurs correspondant à hxw
    //On a un bord de 1 et on calcule le padding à partir du reste de
    //de la division nbPixels/16
    // vuint8** Mo = vui8matrix(*nrl, *nrh, *ncl, *nch);
    // Mo = (vuint8**) Io;
    // display_vui8matrix(Mo, *nrl, *nrh, *ncl, *nch, "%d",NULL);

    //Initialisation de Vo à VMIN (on mettra à VMAX quand on comprendra comment
    //enregistrer une image PGM en SIMD)
    return 0;
}
