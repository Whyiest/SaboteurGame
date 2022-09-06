#include "fonctions.h"

// Permet d'afficher les rôles des joueurs :  ----------------------------------------------

void affichageRole(joueur *JoueurListe, ALLEGRO_BITMAP *ensemblecartes, short *j, ALLEGRO_FONT *policeMenu65,
                   ALLEGRO_FONT *policeMenu35, ALLEGRO_MOUSE_STATE etat_souris, bool clic, ALLEGRO_SAMPLE *sonclick) {

    al_draw_filled_rectangle(200, HAUTEUR / 2 - 80, 1170, HAUTEUR / 2 + 80, al_map_rgba(35, 35, 35, 180));

    if (JoueurListe[*j].role == 1) {
        // Si le joueur est un policier :
        al_draw_textf(policeMenu65, al_map_rgb(240, 240, 240), LARGEUR / 2, HAUTEUR / 2.5, ALLEGRO_ALIGN_CENTER,
                      "%s est un", JoueurListe[*j].pseudo);
        al_draw_textf(policeMenu65, al_map_rgb(60, 60, 240), LARGEUR / 2, HAUTEUR / 2.5 + 70, ALLEGRO_ALIGN_CENTER,
                      "policier");

    } else {
        // Si le joueur est cambrioleur :
        al_draw_textf(policeMenu65, al_map_rgb(240, 240, 240), LARGEUR / 2, HAUTEUR / 2.5, ALLEGRO_ALIGN_CENTER,
                      "%s est un", JoueurListe[*j].pseudo);
        al_draw_textf(policeMenu65, al_map_rgb(240, 60, 60), LARGEUR / 2, HAUTEUR / 2.5 + 70, ALLEGRO_ALIGN_CENTER,
                      "cambrioleur");
    }
    if (bouton(etat_souris, LARGEUR/2+410, 700, 250, 40, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu35, 35, "Suivant",
               al_map_rgb(255, 255, 255), clic) == 1) {
        // Bouton suivant permettant de passer au jour suivant
        al_play_sample(sonclick, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *j = *j + 1; // Passage au jour suivant
    }
}

