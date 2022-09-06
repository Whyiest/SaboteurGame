#include "fonctions.h"

void piocher(joueur *joueurQuiPioche, carte cartes[], short *NbCartesPioche,short i) {
    short a=rand()%*NbCartesPioche;
    joueurQuiPioche[i].deck[joueurQuiPioche[i].nbCartesDansDeck]=cartes[a];
    joueurQuiPioche[i].deck[joueurQuiPioche[i].nbCartesDansDeck].x=cartes[a].x;
    joueurQuiPioche[i].deck[joueurQuiPioche[i].nbCartesDansDeck].y=cartes[a].y;
    joueurQuiPioche[i].deck[joueurQuiPioche[i].nbCartesDansDeck].pioche_deffause_main=2;
    if (a!=*NbCartesPioche){
        cartes[a]=cartes[*NbCartesPioche];
    }
    joueurQuiPioche[i].nbCartesDansDeck++;
    joueurQuiPioche[i].deck[joueurQuiPioche[i].nbCartesDansDeck].pioche_deffause_main=2;
    *NbCartesPioche=*NbCartesPioche-1;
}
void deffause(joueur *JoueurListe, short a, carte *cartes, short *NbCartesPioche) {

    short r = rand() % *NbCartesPioche;

    for (int i = 0; i < JoueurListe[a].nbCartesDansDeck; ++i) {

        if (JoueurListe[a].deck[i].pioche_deffause_main == 1) {
            JoueurListe[a].deck[i] = cartes[r];

            if (r != *NbCartesPioche) {
                cartes[r] = cartes[*NbCartesPioche];
            }
            JoueurListe[a].deck[i].pioche_deffause_main = 2;
            *NbCartesPioche = *NbCartesPioche - 1;
        }
    }
}



