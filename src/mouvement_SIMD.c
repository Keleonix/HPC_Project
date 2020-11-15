#include "mouvement_SIMD.h"
#include "simd_macro.h"
#include "my_vnrutil.h"


// t : instant de temps courant, servant à indicer les images
// It : image source en niveau de gris à l’instant t
// It−1 : l’image source à l’instant t-1,
// Mt : image de fond (image de moyenne),
// Ot : image de différence, en niveau de gris
// Vt : image de variance (d’écart type en fait) calculée pour tout pixel,
// Et : image d’étiquettes binaires (mouvement / fond), Et(x) = {0, 1} ou Et(x) = {0, 255} pour coder {fond,
// mouvement}
// x : le pixel courant de coordonnées (i,j)


//Premiere étape de l'algorithme SigmaDelta
void SigmaDelta_step0_SIMD(uint8** Io, vuint8* Mt_1, vuint8* Vt_1, int* nrl, int* nrh, int* ncl, int* nch, int nbVuint8){
    //Parcours de Io pour remplir Mo TODO:mettre dans la fct principale
    // vuint8* Mo = vui8vector(0, nbPixels);
    // printf("Affichage de Mo quand il est encore NULL\n\n");
    // display_vuint8(Mo[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Mo quand il est encore NULL\n\n");

    copy_ui8matrix_vui8vector(Io, *nrl, *nrh, *ncl, *nch, Mt_1);

    // printf("Affichage de Mo après copie de Io \n\n");
    // display_vuint8(Mo[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Mo après copie de Io\n\n");

    // printf("Affichage de Vo quand il est encore NULL\n\n");
    // display_vuint8(Vt_1[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Vo quand il est encore NULL\n\n");

    for(int i = 0; i < nbVuint8; i++){
        Vt_1[i] = init_vuint8((uint8)VMIN);
    }

    // printf("Affichage de Vo après initialisation à VMIN \n\n");
    // display_vuint8(Vt_1[0],"%d\n", NULL);
    // printf("Fin de l'affichage de Vo après initialisation à VMIN\n\n");

}

void SigmaDelta_step1_SIMD(vuint8* It, vuint8* Mt_1, vuint8* Mt, int nbVuint8){

        //TODO: fonction principale
        // char image1[] = "car3/car_3001.pgm";
        // uint8** It = LoadPGM_ui8matrix(image1, nrl, nrh, ncl, nch);
        //vuint8* Itvect = vui8vector(0, nbPixels);
        //copy_ui8matrix_vui8vector(It, *nrl, *nrh, *ncl, *nch, Itvect);
        //vuint8* Mt = vui8vector(0, nbPixels);
        //
        // printf("Affichage des 16 premiers pixels de It\n\n");
        //
        // printf("%d %d %d %d %d %d %d %d ", It[0][0], It[0][1], It[0][2], It[0][3], It[0][4], It[0][5], It[0][6], It[0][7]);
        // printf("%d %d %d %d %d %d %d %d\n\n", It[0][8], It[0][9], It[0][10], It[0][11], It[0][12], It[0][13], It[0][14], It[0][15]);
        //
        // printf("Fin de l'affichage des 16 premiers pixels\n\n");



        // printf("Affichage de It avant initialisation\n\n");
        // display_vuint8(Itvect[0],"%d\n", NULL);
        // printf("Fin de l'affichage de Vo avant initialisation\n\n");



        // printf("Affichage de It après initialisation\n\n");
        // display_vuint8(Itvect[0],"%d\n", NULL);
        // printf("Fin de l'affichage de Vo après initialisation\n\n");

        vuint8 pixelsIm, pixelsM, C1, C2, K1, K2, K, M;
        for(int i = 0; i < nbVuint8; i++){
            pixelsIm = vec_load(&It[i]);
            pixelsM = vec_load(&Mt_1[i]);

            C1 = vec_gt (pixelsIm, pixelsM); //Sont mis à 1 tout pixel où It > main
            C2 = vec_gt (pixelsM, pixelsIm); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0
            K1 = init_vuint8(1);
            K2 = init_vuint8(-1);
            K = vec_or(vec_and(C1, K1), vec_and(C2, K2));

            M = vec_add(K, pixelsM);
            vec_store(&Mt[i], M);

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
}

//Etape 2 : Ot, difference entre image source et moyenne
void SigmaDelta_step2_SIMD(vuint8* It,  vuint8* Mt, vuint8* Ot, int nbVuint8){

    vuint8 pixelsIm, pixelsM, pixelsO;
    for(int i = 0; i < nbVuint8; i++){
        pixelsIm = vec_load(&It[i]);
        pixelsM = vec_load(&Mt[i]);

        pixelsO = vec_sub(pixelsM, pixelsIm);
        pixelsO = vi8_abs(pixelsO);
        vec_store(&Ot[i], pixelsO);

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
}

//Etape 3 : Mise à jour de l'image de variance Vt
void SigmaDelta_step3_SIMD(vuint8* Ot, vuint8* Vt_1, vuint8* Vt, int nbVuint8){

    vuint8 vectN = init_vuint8(N);
    // vuint8* Vt = vui8vector(0, nbPixels); //TODO: Fonction principale
    vuint8 pixelsO, pixelsOtxN, pixelsVt_1, D1, D2, L, V;
    for(int i = 0; i < nbVuint8; i++){
        pixelsO = vec_load(&Ot[i]);

        pixelsOtxN = vi8_mul(pixelsO, init_vuint8(N));
        pixelsVt_1 = vec_load(&Vt_1[i]);

        D1 = vec_gt (pixelsOtxN, pixelsVt_1); //Sont mis à 1 tout pixel où N*Ot > Vt
        D2 = vec_gt (pixelsVt_1, pixelsOtxN); //On fait deux comparaisons pour s'assurer que les pixels égaux donnent 0

        L = vec_or(vec_and(D1, init_vuint8(1)), vec_and(D2, init_vuint8(-1)));

        V = vec_add(L, pixelsVt_1);
        V = vi8_max(vi8_min(V, init_vuint8(VMAX)), init_vuint8(VMIN));
        //vec_store(&Vt[i], V);

        // if(i == 45){
        //     printf("\n");
        //     display_vuint8(pixelsOtxN, "%d ", "OtxN ");
        //     printf("\n");
        //     display_vuint8(pixelsVt_1, "%d ", "Vt_1 ");
        //     printf("\n");
        //     display_vuint8(D1, "%d ", "D1 ");
        //     printf("\n");
        //     display_vuint8(D2, "%d ", "D2 ");
        //     printf("\n");
        //     display_vuint8(L, "%d ", "L ");
        //     printf("\n");
        //     display_vuint8(V, "%d ", "V ");
        //     printf("\n");
        //     printf("\n");
        //     display_vuint8(Vt[i], "%d ", "Vt ");
        //     printf("\n");
        // }
    }
    // uint8 pixelVt = 0;
    // uint8 pixelOt = 0;
    // for(int j = *nrl; j <= *nrh; j++){
    //     for(int k = *ncl; k <= *nch; k++){
    //         pixelVt = Vt_1[j][k];
    //         pixelOt = Ot[j][k];
    //
    //         if(pixelVt < N * pixelOt)
    //         {
    //             Vt[j][k] = pixelVt + 1;
    //         }
    //         else if(pixelVt > N * pixelOt){
    //             Vt[j][k] = pixelVt - 1;
    //         }
    //         else{
    //             Vt[j][k] = pixelVt;
    //         }
    //
    //         Vt[j][k] = MAX(MIN(Vt[j][k], VMAX), VMIN);
    //     }
    // }
}

//Etape 4 : Estimation de l'image d'etiquettes binaires Et
void SigmaDelta_step4_SIMD(vuint8* Ot, vuint8* Vt, vuint8* Et, int nbVuint8){

    //vuint8* Et = vui8vector(0, nbPixels); //TODO: Fonction principale

    vuint8 pixelsVt, pixelsOt, C, E;

    for(int i = 0; i < nbVuint8; i++){
        pixelsVt = vec_load(&Vt[i]);
        pixelsOt = vec_load(&Ot[i]);

        C = vec_lt(pixelsOt, pixelsVt); //A 0, Ot >= Vt et à 0xFF, Ot < Vt
        E = vec_and(C, init_vuint8(VMAX)); //A 0, Ot >= Vt et à VMAX, Ot < Ot
        //TODO: VMAX = 0xFF non ?
        // E = vec_add(K, pixelsVt_1);
        vec_store(&Et[i], E);

        // if(i == 45){
        //     printf("\n");
        //     display_vuint8(pixelsOt, "%d ", "Ot ");
        //     printf("\n");
        //     display_vuint8(pixelsVt, "%d ", "Vt");
        //     printf("\n");
        //     display_vuint8(C, "%d ", "C ");
        //     printf("\n");
        //     display_vuint8(E, "%d ", "E ");
        //     printf("\n");
        //     display_vuint8(Et[i], "%d ", "Et ");
        //     printf("\n");
        // }
    }
}

void main_mouvement_SIMD(){
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
    uint8** imagemat;
    vuint8* It = vui8vector(0, nbPixels);
    char image[18]; //17 caractères dans le chemin relatif de l'image

    //Allocation d'une matrice uint8 pour conserver le resultat Et
    uint8** Et_ui8 = ui8matrix(*nrl, *nrh, *ncl, *nch);

    //On commence l'algorithme à la deuxième image
    for(int i = 3001; i <= 3000+NOMBRE_IMAGE; i++){

        //Generation du nom de fichier de l'image suivante
        generate_filename_k_ndigit_extension("car3/car_", i, 0, "pgm", image);

        //Chargement de l'image
        imagemat = LoadPGM_ui8matrix(image, nrl, nrh, ncl, nch);
        copy_ui8matrix_vui8vector(imagemat, *nrl, *nrh, *ncl, *nch, Mt_1);

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
        generate_filename_k_ndigit_extension("test_SIMD/Et_", i, 0, "pgm", image);
        // printf("%s\n", image);
        copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        // }

        //Changement de variables
        Mt_1 = Mt;
        Vt_1 = Vt;
        //TODO: copy_vui8vector_vui8vector dans vnrutil
        //copy_ui8matrix_ui8matrix (Mt_1, *nrl, *nrh, *ncl, *nch, Mt);
        //copy_ui8matrix_ui8matrix (Vt_1, *nrl, *nrh, *ncl, *nch, Vt);
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
