#include "mouvement_optim.h"
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


//Initialisation de la premiere image, image de fond et image de variance à t = 0
void SigmaDelta_step0_OPTIM(uint8** Io, vuint8* Mt_1, vuint8* Vt_1, int* nrl, int* nrh, int* ncl, int* nch, int nbVuint8){

    copy_ui8matrix_vui8vector(Io, *nrl, *nrh, *ncl, *nch, Mt_1);
    for(int i = 0; i < nbVuint8; i++){
        Vt_1[i] = init_vuint8((uint8)VMIN);
    }

}

//Etapes de l'algoritme SigmaDelta
//Etape 1 : estimation de l'image de fond (version SIMD)
//Etape 2 : Ot, difference entre image source et moyenne (version SIMD)
//Etape 3 : Mise à jour de l'image de variance Vt (version SIMD)
//Etape 4 : Estimation de l'image d'etiquettes binaires Et (version SIMD)
void SigmaDelta_steps_OPTIM(vuint8* It, vuint8* Mt_1, vuint8* Mt,\
     vuint8* Ot, vuint8* Vt_1, vuint8* Vt, vuint8* Et, int nbVuint8){

    //Variables de l'etape 1

    vuint8 vect_It, vect_Mt_1; //Vecteurs où sont chargés It, Mt_1, Mt
    vuint8 vect_It_127, vect_Mt_1_127; //Vecteurs après soustraction par 127
    vuint8 C1, C2, K1, K2, K; //Vecteurs de comparaison

    //Variables de l'etape 2

    vuint8 vect_Ot, vect_Mt; //Vecteurs où sont chargés Ot et Mt

    //Variables de l'etape 3

    vuint8 vectN = init_vuint8(N); //Vecteur permettant de multiplier un autre par N
    vuint8 vect_OtxN, vect_Vt_1; //Vecteurs où sont chargés Ot*N, Vt_1
    vuint8 vect_OtxN_127, vect_Vt_1_127; //Vecteurs après soustraction par 127
    vuint8 D1, D2, L; //Vecteurs de comparaison
    vuint8 V;         //Vecteur résultat

    //Variables de l'etape 4
    vuint8 vect_Vt, C;
    vuint8 vect_Vt_127, vect_Ot_127;//Vecteurs après soustraction par 127
    vuint8 vect_Et; //Vecteur résultat

    for(int i = 0; i < nbVuint8; i++){

        //ETAPE 1
        vect_It = vec_load(&It[i]);
        vect_Mt_1 = vec_load(&Mt_1[i]);

        //Les fonctions de comparaisons considerent que les entiers sont
        //signés, MSB est considéré comme le signe et les 7 LSB sont comparés
        //129 < 127, car 129 = 1000 0001b et 127 = 0111 1111b
        //On va alors soustraire 127 aux vecteurs avant la comparaison

        vect_It_127 = vec_sub(vect_It, init_vuint8(127));
        vect_Mt_1_127 = vec_sub(vect_Mt_1, init_vuint8(127));

        C1 = vec_gt (vect_It_127, vect_Mt_1_127); //IF(It > Mt_1)
        C2 = vec_gt (vect_Mt_1_127, vect_It_127); //ELSE IF(Mt_1 > It)
        K1 = init_vuint8(1);
        K2 = init_vuint8(-1);

        //IF(It > Mt_1) K = 1
        //ELSE IF(Mt_1 > It) K = -1
        //ELSE K = 0
        K = vec_or(vec_and(C1, K1), vec_and(C2, K2));

        vect_Mt = vec_add(K, vect_Mt_1);
        vec_store(&Mt[i], vect_Mt);

        //ETAPE 2
        // vect_It = vec_load(&It[i]); TODO: A retirer
        // vect_Mt = vec_load(&Mt[i]); TODO: A retirer

        vect_Ot = vec_sub(vect_Mt, vect_It); // Ot = Mt - It
        vect_Ot = vi8_abs(vect_Ot); //ABS(Ot)
        vec_store(&Ot[i], vect_Ot);

        //ETAPE 3
        // vect_Ot = vec_load(&Ot[i]); TODO: A retirer

        vect_OtxN = vi8_mul(vect_Ot, init_vuint8(N));
        vect_Vt_1 = vec_load(&Vt_1[i]);

        //Les fonctions de comparaisons considerent que les entiers sont
        //signés, MSB est considéré comme le signe et les 7 LSB sont comparés
        //129 < 127, car 129 = 1000 0001b et 127 = 0111 1111b
        //On va alors soustraire 127 aux vecteurs avant la comparaison

        vect_OtxN_127 = vec_sub(vect_OtxN, init_vuint8(127));
        vect_Vt_1_127 = vec_sub(vect_Vt_1, init_vuint8(127));

        D1 = vec_gt(vect_OtxN_127, vect_Vt_1_127); //IF (N*Ot - 127) > (Vt_1 - 127)
        D2 = vec_gt(vect_Vt_1_127, vect_OtxN_127); //IF (Vt_1 - 127) > (N*Ot - 127)

        //IF (N*Ot - 127) > (Vt_1 - 127) L = 1
        //ELSE IF(Vt_1 - 127) > (N*Ot - 127) L = -1
        //ELSE L = 0
        L = vec_or(vec_and(D1, init_vuint8(1)), vec_and(D2, init_vuint8(-1)));

        //Vt = Vt_1 + L
        V = vec_add(L, vect_Vt_1);

        //MAX(MIN(Vt, VMAX), VMIN);
        vect_Vt = vec_max(vec_min(V, init_vuint8(VMAX)), init_vuint8(VMIN));
        vec_store(&Vt[i], vect_Vt);


        //ETAPE 4
        // vect_Vt = vec_load(&Vt[i]); TODO: A retirer
        // vect_Ot = vec_load(&Ot[i]); TODO: A retirer

        //Les fonctions de comparaisons considerent que les entiers sont
        //signés, MSB est considéré comme le signe et les 7 LSB sont comparés
        //129 < 127, car 129 = 1000 0001b et 127 = 0111 1111b
        //On va alors soustraire 127 aux vecteurs avant la comparaison

        vect_Ot_127 = vec_sub(vect_Ot, init_vuint8(127));
        vect_Vt_127 = vec_sub(vect_Vt, init_vuint8(127));

        //IF (Ot - 127) < (Vt_1 - 127) C = 1
        //ELSE C = 0
        C = vec_lt(vect_Ot_127, vect_Vt_127);

        //IF (Ot - 127) < (Vt_1 - 127) E = 1
        //ELSE E = 0
        E = vec_andnot(C, init_vuint8(1));

        vec_store(&Et[i], E);
    }
}


void main_mouvement_OPTIM(){
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
    SigmaDelta_step0_OPTIM(Io, Mt_1, Vt_1, nrl, nrh, ncl, nch, nbVuint8);

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

        SigmaDelta_steps_OPTIM(It, Mt_1, Mt, Ot, Vt_1, Vt, Et, nbVuint8);

        generate_filename_k_ndigit_extension("test_OPTIM/Mt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Mt, *nrl, *nrh, *ncl, *nch, Mt_ui8);
        SavePGM_ui8matrix(Mt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("test_OPTIM/Ot_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Ot, *nrl, *nrh, *ncl, *nch, Ot_ui8);
        SavePGM_ui8matrix(Ot_ui8, *nrl, *nrh, *ncl, *nch, image);
        //
        generate_filename_k_ndigit_extension("test_OPTIM/Vt_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Vt, *nrl, *nrh, *ncl, *nch, Vt_ui8);
        SavePGM_ui8matrix(Vt_ui8, *nrl, *nrh, *ncl, *nch, image);

        generate_filename_k_ndigit_extension("test_OPTIM/Et_", i, 0, "pgm", image);
        copy_vui8vector_ui8matrix(Et, *nrl, *nrh, *ncl, *nch, Et_ui8);
        SavePGM_ui8matrix(Et_ui8, *nrl, *nrh, *ncl, *nch, image);

        copy_vui8vector_vui8vector(Mt, nbVuint8, Mt_1);
        copy_vui8vector_vui8vector(Vt, nbVuint8, Vt_1);
    }

    // Desallocation de la mémoire
    free_ui8matrix(Io, *nrl, *nrh, *ncl, *nch);
    free_vui8vector(It, 0, nbPixels);
    free_vui8vector(Mt_1, 0, nbPixels);
    free_vui8vector(Vt_1, 0, nbPixels);
    free_vui8vector(Mt, 0, nbPixels);
    free_vui8vector(Vt, 0, nbPixels);
    free_vui8vector(Ot, 0, nbPixels);
    free_vui8vector(Et, 0, nbPixels);
    free(nrl);
    free(nrh);
    free(ncl);
    free(nch);
}
