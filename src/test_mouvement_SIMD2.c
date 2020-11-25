#include "test_mouvement_SIMD.h"


// void test_fct_vi8max_OK(){
//     vuint8 min = init_vuint8(VMIN);
//     vuint8 a = init_vuint8_all(1,1,0,1,1,1,0,1,1,-1,1,1,1,1,1,-1);
//
//     vuint8 attendu = init_vuint8_all(1,1,VMIN,1,1,1,VMIN,1,1,VMIN,1,1,1,1,1,VMIN);
//     vuint8 test = vi8_max(a, min);
//     vuint8 test_2 = vi8_max(min, a);
//
//     display_vuint8(test, "%d  ", "test : ");
//     printf("\n");
//
//     display_vuint8(test_2, "%d  ", "test 2 : ");
//     printf("\n");
//
//
//     display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
//     printf("\n");
//
//     display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
//     printf("\n");
// }
//
// void test_fct_vi8max_OK_2(){
//
// }
//
// void test_fct_vi8min_OK(){
//     vuint8 max = init_vuint8(240);
//     vuint8 a = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);
//
//     vuint8 attendu = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);
//     vuint8 test = vi8_min(a, max);
//     vuint8 test_2 = vi8_min(max, a);
//
//     vuint8 test_3 = _mm_min_epu8(a, max);
//     vuint8 test_4 = _mm_min_epu8(a, max);
//
//     display_vuint8(test, "%d  ", "test : ");
//     printf("\n");
//
//     display_vuint8(test_2, "%d  ", "test 2 : ");
//     printf("\n");
//
//     display_vuint8(test_3, "%d  ", "test 3 : ");
//     printf("\n");
//
//     display_vuint8(test_4, "%d  ", "test 4 : ");
//     printf("\n");
//
//     display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
//     printf("\n");
//
//     display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
//     printf("\n");
//
//     display_vuint8(vec_eq(attendu, test_3), "%d  ", "attendu 3 : ");
//     printf("\n");
//
//     display_vuint8(vec_eq(attendu, test_4), "%d  ", "attendu 4 : ");
//     printf("\n");
// }
//
// void test_fct_vi8min_vi8max_OK(){
// }

void test_vec_and(){
    vuint8 FF = init_vuint8(-1);
    vuint8 a = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);

    vuint8 attendu = init_vuint8_all(1,1,VMAX,1,1,1,VMAX,1,1,VMAX,1,1,1,1,1,VMAX);
    vuint8 test = vec_and(a, FF);
    vuint8 test_2 = vec_and(FF, a);

    display_vuint8(test, "%d  ", "test : ");
    printf("\n");

    display_vuint8(test_2, "%d  ", "test 2 : ");
    printf("\n");


    display_vuint8(vec_eq(attendu, test), "%d  ", "attendu 1 : ");
    printf("\n");

    display_vuint8(vec_eq(attendu, test_2), "%d  ", "attendu 2 : ");
    printf("\n");
}

//TODO: A supprimer, je garde au cas où, mais normalement, c'est pas utile
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

// Les images de la séquence ont un nombre de pixels qui est multiple de 16
// On va donc juste faire un tableau de vuint8 1D sans padding et on verra bien
// Sans bord, sans padding

//Etape 0 :
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
//     C1 = _mm_cmpgt_epi8 (vec_sub(pixelsIm, init_vuint8(127)), vec_sub(pixelsM, init_vuint8(127))); //Sont mis à 1 tout pixel où It > main
//     C2 = _mm_cmpgt_epi8 (vec_sub(pixelsM, init_vuint8(127)), vec_sub(pixelsIm, init_vuint8(127))); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
//     K1 = init_vuint8(1);
//     K2 = init_vuint8(-1);
//     K = _mm_or_si128(_mm_and_si128(C1, K1), _mm_and_si128(C2, K2));
//
//     M = _mm_add_epi8(K, pixelsM);
//     _mm_store_si128(&Mt[i], M);
//
//     if(i == 0){
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
//         printf("K  ");
//         display_vuint8(K,"%d ", NULL);
//         printf("\n");
//
//         printf("M  ");
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

// Etape 1 validée
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