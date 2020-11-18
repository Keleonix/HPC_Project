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
#include "morpho.h"
// #include "test_mouvement.h"
// #include "bench_mouvement.h"

#include "mouvement_SIMD.h"
#include "morpho_SIMD.h"

#include "my_vnrutil.h"
#include "simd_macro.h"

#include "dtime.h"
#include "test_mouvement_SIMD.h"
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

//TODO: J'ai mis qu'erosion, dilatation, erosion, dilatation, voir si le reste
//est important
//Applique l'algorithme SigmaDelta, puis la morphologie aux images de la séquence
void chaine_complete(){

    printf("Début du programme principal.\n");
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    printf("Chargement de l'image.\n");
    printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    //Allocation des matrices pour l'algorithme
    uint8** Mt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_1 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Et = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch);

    //Allocation de It
    uint8** It;

    //Algorithme SigmaDelta
    //SigmaDelta_1step(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nrl, nrh, ncl, nch);
    char image[18]; //17 caractères dans le chemin relatif de l'image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        It = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);

        //TODO : Rajouter les macros chrono pour mesurer le temps de chaque fonction
        SigmaDelta_step1(It, Mt_1, Mt, nrl, nrh, ncl, nch);
        SigmaDelta_step2(It, Mt, Ot, nrl, nrh, ncl, nch);
        SigmaDelta_step3(Ot, Vt_1, Vt, nrl, nrh, ncl, nch);
        SigmaDelta_step4(Ot, Vt, Et, nrl, nrh, ncl, nch);

        Et = ouverture(Et, *nrl, *nrh, *ncl, *nch);
        Et = fermeture(Et, *nrl, *nrh, *ncl, *nch);


        // generate_filename_k_ndigit_extension("test/Mt_", i, 0, "pgm", image);
        // SavePGM_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, image);
        // generate_filename_k_ndigit_extension("test/Ot_", i, 0, "pgm", image);
        // SavePGM_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, image);
        // generate_filename_k_ndigit_extension("test/Vt_", i, 0, "pgm", image);
        // SavePGM_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("test/Etmorph_", i, 0, "pgm", image);
        SavePGM_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, image);


        copy_ui8matrix_ui8matrix (Mt, *nrl, *nrh, *ncl, *nch, Mt_1);
        copy_ui8matrix_ui8matrix (Vt, *nrl, *nrh, *ncl, *nch, Vt_1);
    }
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(It, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt_1, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch);
    free_ui8matrix(Et, *nrl, *nrh, *ncl, *nch);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);

}

//Applique l'algorithme SigmaDelta, puis la morphologie aux images de la séquence
//en SIMD
void chaine_complete_SIMD(){
    printf("Début du programme principal.\n");
    int* nrl = malloc(sizeof(int));
    int* nrh = malloc(sizeof(int));
    int* ncl = malloc(sizeof(int));
    int* nch = malloc(sizeof(int));
    char image0[] = "car3/car_3000.pgm";

    //Chargement de la 1ere image
    uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    printf("Chargement de l'image.\n");
    printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

    int nbPixels = (*nrh+1)*(*nch+1);

    //Calcule du nombre de vecteurs nécessaires pour l'image
    int nbVuint8 = nbPixels/16+1;

    //Allocation des matrices pour l'algorithme
    vuint8* Mt_1 = vui8vector(0, nbPixels);
    vuint8* Vt_1 = vui8vector(0, nbPixels);
    vuint8* Mt = vui8vector(0, nbPixels);
    vuint8* Vt = vui8vector(0, nbPixels);
    vuint8* Ot = vui8vector(0, nbPixels);
    vuint8* Et = vui8vector(0, nbPixels);

    //Initialisation de Mt_1 et Vt_1
    SigmaDelta_step0_SIMD(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

    //Allocation de It
    uint8** imagemat = ui8matrix(*nrl, *nrh, *ncl, *nch);
    vuint8* It = vui8vector(0, nbPixels);

    char* image = malloc(sizeof(char)*48); //17 caractères dans le chemin relatif de l'image

    //Allocation d'une matrice uint8 pour conserver le resultat Et
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Vt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Ot_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    uint8** Mt_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //On commence l'algorithme à la deuxième image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
        // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);

        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, It);
        //TODO: Le mode SinCity c'est quand je copiais l'image dans Mt_1 au lieu de It

        //TODO : Rajouter les macros chrono pour mesurer le temps de chaque fonction
        SigmaDelta_step1_SIMD(It, Mt_1, Mt, nbVuint8);
        SigmaDelta_step2_SIMD(It, Mt, Ot, nbVuint8);
        SigmaDelta_step3_SIMD(Ot, Vt_1, Vt, nbVuint8);
        SigmaDelta_step4_SIMD(Ot, Vt, Et, nbVuint8);

        //TODO : Test rapide, à retirer
        //Creation de fichiers pgm à partir des dix premieres frames traitées
        // if(i > 3070 && i < 3090){

            // generate_filename_k_ndigit_extension("test/Vt_", i, 0, "pgm", image);
            // copy_vui8vector_ui8matrix(vuint8* vect, long nrl, long nrh, long ncl, long nch, uint8** mat);
            // SavePGM_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, image);
        generate_filename_k_ndigit_extension("test_SIMD/Mt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, Mt_ui8);
        SavePGM_ui8matrix(Mt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("test_SIMD/Ot_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, Ot_ui8);
        SavePGM_ui8matrix(Ot_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("test_SIMD/Vt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, Vt_ui8);
        SavePGM_ui8matrix(Vt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("test_SIMD/Etmorph_", i, 0, "pgm", image);
        // printf("%s\n", image);
        // if(i == 3100){
        //     display_vuint8(Et[0],"%d ", NULL);
        //     display_vuint8(Et[1],"%d ", NULL);
        //     display_vuint8(Et[2],"%d ", NULL);
        //     printf("\n");
        // }
        copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);

        Et_ui8 = ouverture(Et_ui8, *nrl, *nrh, *ncl, *nch);
        Et_ui8 = fermeture(Et_ui8, *nrl, *nrh, *ncl, *nch);

        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        // }

        //Changement de variables
        Mt_1 = Mt;
        Vt_1 = Vt;
        // copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        // copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
    }

    //Algorithme SigmaDelta
    //Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    // free_vui8vector(Mt, 0, nbPixels);
    // free_vui8vector(Vt, 0, nbPixels);
    free_vui8vector(Ot, 0, nbPixels);
    free_vui8vector(Et, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}

int main(void){
    main_mvt_ref_SIMD();
    // test_algo_step1_1();

    // main_mouvement();
    // main_mouvement_SIMD();
    // test_imagePGM();
    // test1_step1_SIMD();
    // int tmp = dtime();
    // chaine_complete();
    // tmp = dtime() - tmp;
    // printf("Temps : %d\n", tmp);
    //
    // tmp = dtime();
    // chaine_complete_SIMD();
    // tmp = dtime() - tmp;
    // printf("Temps : %d\n", tmp);

    //TODO: Reparez ce max et ce min qui sont nuls
    // vuint8 a = init_vuint8_all(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    // vuint8 b = init_vuint8_all(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
    //
    // vuint8 c = vi8_max(a, b);
    // vuint8 d = vi8_min(a, b);
    //
    // vuint8 e = vec_gt(a, b);
    //
    // // pixelsVt = vec_load(&Vt[i]);
    // // pixelsOt = vec_load(&Ot[i]);
    //
    // vuint8 C = vec_lt(a, b); //A 0, Ot >= Vt et à 0xFF, Ot < Vt
    // vuint8 E = vec_and(C, init_vuint8(VMAX)); //A 0, Ot >= Vt et à VMAX, Ot < Ot
    //
    // display_vuint8(a, "%d ", "a ");
    // printf("\n");
    // display_vuint8(b, "%d ", "b ");
    // printf("\n");
    //
    // display_vuint8(C, "%d ", "C ");
    // printf("\n");
    // display_vuint8(E, "%d ", "E ");
    // printf("\n");
    // display_vuint8(c, "%d ", "c ");
    // printf("\n");
    // display_vuint8(d, "%d ", "d ");
    // printf("\n");
    // display_vuint8(e, "%d ", "e ");
    // printf("\n");


    //SIMD
    // int* nrl = malloc(sizeof(int));
    // int* nrh = malloc(sizeof(int));
    // int* ncl = malloc(sizeof(int));
    // int* nch = malloc(sizeof(int));
    // //Chargement de l'image O
    // // char image0[] = "img_test/rei2.pgm";
    // char image0[] = "car3/car_3000.pgm";
    // uint8** Io = LoadPGM_ui8matrix(image0, nrl, nrh, ncl, nch);
    // printf("Chargement de l'image.\n");
    // printf("nrl = %d\nnrh = %d\nncl = %d\nnch = %d\n", *nrl, *nrh, *ncl, *nch);
    //
    // //Copie de Io dans Mo, vuint8
    // int p = 0; //padding
    // int b = 0; //bord
    //
    // //sans bord
    // int nbPixels = (*nrh+1)*(*nch+1);
    // int nbVuint8 = nbPixels/16+1;
    // printf("Nombre de pixels = %d, pixels restants après division = %d => Nombre de vecteurs = %d\n,", nbPixels, nbPixels%16, nbVuint8);
    //
    // //Les images de la séquence ont un nombre de pixels qui est multiple de 16
    // //On va donc juste faire un tableau de vuint8 1D sans padding et on verra bien
    // //Sans bord, sans padding
    // //
    // //Etape 0 :
    //     //Parcours de Io pour remplir Mo
    //     vuint8* Mo = vui8vector(0, nbPixels);
    //     printf("Affichage de Mo quand il est encore NULL\n\n");
    //     display_vuint8(Mo[0],"%d\n", NULL);
    //     printf("Fin de l'affichage de Mo quand il est encore NULL\n\n");
    //
    //     copy_ui8matrix_vui8vector(Io, *nrl, *nrh, *ncl, *nch, Mo);
    //
    //     printf("Affichage de Mo après copie de Io \n\n");
    //     display_vuint8(Mo[0],"%d\n", NULL);
    //     printf("Fin de l'affichage de Mo après copie de Io\n\n");
    //
    //     //Initialisation de Vo
    //     vuint8* Vo = vui8vector(0, nbPixels);
    //
    //     printf("Affichage de Vo quand il est encore NULL\n\n");
    //     display_vuint8(Vo[0],"%d\n", NULL);
    //     printf("Fin de l'affichage de Vo quand il est encore NULL\n\n");
    //
    //     for(int i = 0; i < nbVuint8; i++){
    //         Vo[i] = init_vuint8((uint8)VMIN);
    //     }
    //
    //     printf("Affichage de Vo après initialisation à VMIN \n\n");
    //     display_vuint8(Vo[0],"%d\n", NULL);
    //     printf("Fin de l'affichage de Vo après initialisation à VMIN\n\n");
    //
    //
    // //Etape 0 validée
    //
    // //Etape 1
    // //Chargement de la première image
    // char image1[] = "car3/car_3001.pgm";
    // uint8** It = LoadPGM_ui8matrix(image1, nrl, nrh, ncl, nch);
    //
    // printf("Affichage des 16 premiers pixels de It\n\n");
    //
    // printf("%d %d %d %d %d %d %d %d ", It[0][0], It[0][1], It[0][2], It[0][3], It[0][4], It[0][5], It[0][6], It[0][7]);
    // printf("%d %d %d %d %d %d %d %d\n\n", It[0][8], It[0][9], It[0][10], It[0][11], It[0][12], It[0][13], It[0][14], It[0][15]);
    //
    // printf("Fin de l'affichage des 16 premiers pixels\n\n");
    //
    // vuint8* Itvect = vui8vector(0, nbPixels);
    //
    // printf("Affichage de It avant initialisation\n\n");
    // display_vuint8(Itvect[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Vo avant initialisation\n\n");
    //
    // copy_ui8matrix_vui8vector(It, *nrl, *nrh, *ncl, *nch, Itvect);
    //
    // printf("Affichage de It après initialisation\n\n");
    // display_vuint8(Itvect[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Vo après initialisation\n\n");
    //
    // vuint8* Mt = vui8vector(0, nbPixels);
    // vuint8 pixelsIm, pixelsM, C1, C2, K1, K2, K, M;
    // for(int i = 0; i < nbVuint8; i++){
    //     pixelsIm = _mm_load_si128(&Itvect[i]);
    //     pixelsM = _mm_load_si128(&Mo[i]);
    //
    //     C1 = _mm_cmpgt_epi8 (pixelsIm, pixelsM); //Sont mis à 1 tout pixel où It > main
    //     C2 = _mm_cmpgt_epi8 (pixelsM, pixelsIm); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
    //     K1 = init_vuint8(1);
    //     K2 = init_vuint8(-1);
    //     K = _mm_or_si128(_mm_and_si128(C1, K1), _mm_and_si128(C2, K2));
    //
    //     M = _mm_add_epi8(K, pixelsM);
    //     _mm_store_si128(&Mt[i], M);
    //
    //     if(i >= 45 && i < 65){
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
    // }
    // //
    // // Etape 1 validée
    // //
    // //Etape 2
    // //TODO: Faire une fonction abs_vuint8(vuint8) qui applique abs sur t
    // vuint8* Ot = vui8vector(0, nbPixels);
    // vuint8 O;
    // for(int i = 0; i < nbVuint8; i++){
    //     pixelsIm = _mm_load_si128(&Itvect[i]);
    //     pixelsM = _mm_load_si128(&Mt[i]);
    //
    //     O = _mm_sub_epi8(pixelsM, pixelsIm);
    //     if(i == 45){
    //         display_vuint8(O, "%d ", "O ");
    //     }
    //     O = vi8_abs(O);
    //     // O = abs(O);
    //     //Appliquer abs
    //     _mm_store_si128(&Ot[i], O);
    //
    //     // if(i == 45){
    //     //     printf("\n");
    //     //     display_vuint8(pixelsM, "%d ", "Mt ");
    //     //     printf("\n");
    //     //     display_vuint8(pixelsIm, "%d ", "It ");
    //     //     printf("\n");
    //     //     display_vuint8(O, "%d ", "ABS(O)");
    //     //     printf("\n");
    //     //     display_vuint8(Ot[i], "%d ", "Ot ");
    //     //     printf("\n");
    //     // }
    // }
    //
    // //Etape 3
    // vuint8 vectN = init_vuint8(N);
    // vuint8* Vt = vui8vector(0, nbPixels);
    // vuint8 pixelsO, pixelsOtxN, pixelsVt_1, D1, D2, L, V;
    // for(int i = 0; i < nbVuint8; i++){
    //     pixelsO = _mm_load_si128(&Ot[i]);
    //
    //     //pixelsOxN
    //     //TODO: faire une fonction mul_epi8
    //     pixelsOtxN = vi8_mul(pixelsO, init_vuint8(N));
    //     pixelsVt_1 = _mm_load_si128(&Vo[i]);
    //
    //     D1 = _mm_cmpgt_epi8 (pixelsOtxN, pixelsVt_1); //Sont mis à 1 tout pixel où N*Ot > Vt
    //     D2 = _mm_cmpgt_epi8 (pixelsVt_1, pixelsOtxN); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
    //
    //     L = _mm_or_si128(_mm_and_si128(D1, init_vuint8(1)), _mm_and_si128(D2, init_vuint8(-1)));
    //
    //     V = _mm_add_epi8(L, pixelsVt_1);
    //     _mm_store_si128(&Vt[i], V);
    //
    //     if(i == 45){
    //         printf("\n");
    //         display_vuint8(pixelsOtxN, "%d ", "OtxN ");
    //         printf("\n");
    //         display_vuint8(pixelsVt_1, "%d ", "Vt_1 ");
    //         printf("\n");
    //         display_vuint8(D1, "%d ", "D1 ");
    //         printf("\n");
    //         display_vuint8(D2, "%d ", "D2 ");
    //         printf("\n");
    //         display_vuint8(L, "%d ", "L ");
    //         printf("\n");
    //         display_vuint8(V, "%d ", "V ");
    //         printf("\n");
    //         printf("\n");
    //         display_vuint8(Vt[i], "%d ", "Vt ");
    //         printf("\n");
    //     }
    // }
    //
    // //Etape 4
    // vuint8* Et = vui8vector(0, nbPixels);
    // vuint8 pixelsVt;
    // vuint8 pixelsOt;
    // vuint8 C;
    // vuint8 E;
    //
    // for(int i = 0; i < nbVuint8; i++){
    //     pixelsVt = _mm_load_si128(&Vt[i]);
    //     pixelsOt = _mm_load_si128(&Ot[i]);
    //
    //     C = _mm_cmplt_epi8(pixelsOt, pixelsVt); //A 0, Ot >= Vt et à 0xFF, Ot < Vt
    //     E = _mm_and_si128(C, init_vuint8(VMAX)); //A 0, Ot >= Vt et à VMAX, Ot < Ot
    //     //TODO: VMAX = 0xFF non ?
    //     // E = _mm_add_epi8(K, pixelsVt_1);
    //     _mm_store_si128(&Et[i], E);
    //
    //     if(i == 45){
    //         printf("\n");
    //         display_vuint8(pixelsOt, "%d ", "Ot ");
    //         printf("\n");
    //         display_vuint8(pixelsVt, "%d ", "Vt");
    //         printf("\n");
    //         display_vuint8(C, "%d ", "C ");
    //         printf("\n");
    //         display_vuint8(E, "%d ", "E ");
    //         printf("\n");
    //         display_vuint8(Et[i], "%d ", "Et ");
    //         printf("\n");
    //     }
    // }
    //
    // uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);
    // copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
    // char image[18];
    // generate_filename_k_ndigit_extension("test_SIMD/Et_", 1, 0, "pgm", image);
    // SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);
    //
    //
    //
    // //On calcule le nombre de vecteurs correspondant à hxw
    // //On a un bord de 1 et on calcule le padding à partir du reste de
    // //de la division nbPixels/16
    // // vuint8** Mo = vui8matrix(*nrl, *nrh, *ncl, *nch);
    // // Mo = (vuint8**) Io;
    // // display_vui8matrix(Mo, *nrl, *nrh, *ncl, *nch, "%d",NULL);
    //
    // //Initialisation de Vo à VMIN (on mettra à VMAX quand on comprendra comment
    // //enregistrer une image PGM en SIMD)
    return 0;
}
