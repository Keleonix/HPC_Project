#include "my_vnrutil.h"


void copy_ui8matrix_vui8vector(uint8** mat, long nrl, long nrh, long ncl, long nch, vuint8* vect){

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
    //TODO: Rajouter le cas où le nombre de pixels n'est pas un multiple de 16
    //Pour ça, verifier i et sortir de la boucle quand on atteint le dernier
    //vecteur, initialiser 16 uint8 à 0, et faire une boucle allant de 0 à nbPixels
    //restants,
    // uint8 dernier[16];
    //init à 0
    // for(int k = 0; k < nbPixRestants; i++){
    //      dernier[k] = mat[nrh][k]:
    // }
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