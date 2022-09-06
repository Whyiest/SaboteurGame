#include "fonctions.h"
void saisirPseudo(bool* pseudo_joueur, bool clic, joueur *JoueurListe, int keycode, short* menu) {
    for (int i = 0; i < 4; ++i) {
        if (keycode == 67) {
            *menu = 4;
        }
        if (pseudo_joueur[i] == 1) {
            if (JoueurListe[i].numeroLettre < PSEUDOMAX - 1) {
                if (keycode < 27) {
                    JoueurListe[i].pseudo[JoueurListe[i].numeroLettre] = keycode + 64 ;
                    JoueurListe[i].numeroLettre++;
                }
                if (keycode == 75) {
                    JoueurListe[i].pseudo[JoueurListe[i].numeroLettre] = ' ';
                    JoueurListe[i].numeroLettre++;
                }
            }
            if (keycode == 63 && JoueurListe[i].numeroLettre > 0) {
                JoueurListe[i].numeroLettre--;
                JoueurListe[i].pseudo[JoueurListe[i].numeroLettre] = '\0';
            }
        }
    }
}
