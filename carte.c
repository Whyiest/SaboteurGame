#include "fonctions.h"
void dessinCartes(joueur *joueurQuiPioche,ALLEGRO_BITMAP *ensemblecartes,short a,ALLEGRO_MOUSE_STATE etat_souris,bool clicdroit) {
    for (int i = 0; i < joueurQuiPioche[a].nbCartesDansDeck; ++i) {
        if (joueurQuiPioche[a].deck[i].mouvement==0) {
            joueurQuiPioche[a].deck[i].positionX = 400 + i * (LARGEUR_CARTE - 10);
            joueurQuiPioche[a].deck[i].positionY = 30;
        }
    }
    for (int i = 0; i < joueurQuiPioche[a].nbCartesDansDeck; ++i) {
        if (joueurQuiPioche[a].deck[i].rotation == 0) {
            al_draw_bitmap_region(ensemblecartes, joueurQuiPioche[a].deck[i].x,
                                  joueurQuiPioche[a].deck[i].y, LARGEUR_CARTE,
                                  HAUTEUR_CARTE, (float)joueurQuiPioche[a].deck[i].positionX,
                                  (float)joueurQuiPioche[a].deck[i].positionY,
                                  0);
        } else {
            al_draw_tinted_scaled_rotated_bitmap_region(ensemblecartes,
                                                        joueurQuiPioche[a].deck[i].x,
                                                        joueurQuiPioche[a].deck[i].y,
                                                        LARGEUR_CARTE,
                                                        HAUTEUR_CARTE,
                                                        al_map_rgba(255, 255, 255, 255),
                                                        LARGEUR_CARTE / 2, HAUTEUR_CARTE / 2,
                                                        (float)(joueurQuiPioche[a].deck[i].positionX +
                                                                LARGEUR_CARTE / 2),
                                                        (float)(joueurQuiPioche[a].deck[i].positionY +
                                                                HAUTEUR_CARTE / 2),
                                                        1, 1, (float)3.1415926535, 0);
        }
        if (joueurQuiPioche[a].deck[i].mouvement == 0) {
            if (etat_souris.x > joueurQuiPioche[a].deck[i].positionX &&
                etat_souris.x < joueurQuiPioche[a].deck[i].positionX + LARGEUR_CARTE - 10 && etat_souris.y > 30 &&
                etat_souris.y < 30 + HAUTEUR_CARTE) {
                if (joueurQuiPioche[a].deck[i].rotation==0) {
                    al_draw_scaled_bitmap(ensemblecartes, joueurQuiPioche[a].deck[i].x, joueurQuiPioche[a].deck[i].y,
                                          LARGEUR_CARTE, HAUTEUR_CARTE, (float)(400 + i * (LARGEUR_CARTE - 10) - 5), 30 - 5,
                                          LARGEUR_CARTE + 12, HAUTEUR_CARTE + 8, 0);
                }else{
                    al_draw_tinted_scaled_rotated_bitmap_region(ensemblecartes, joueurQuiPioche[a].deck[i].x,
                                                                joueurQuiPioche[a].deck[i].y, LARGEUR_CARTE,
                                                                HAUTEUR_CARTE, al_map_rgba(255,255, 255, 255),
                                                                LARGEUR_CARTE/2, HAUTEUR_CARTE/2,
                                                                (float)(joueurQuiPioche[a].deck[i].positionX+LARGEUR_CARTE/2), (float)(joueurQuiPioche[a].deck[i].positionY+HAUTEUR_CARTE/2),
                                                                (float)1.1, (float)1.1, (float)3.1415926535 , 0);
                }

                if (clicdroit==true){
                    rotation(&joueurQuiPioche[a].deck[i]);
                }

            }
        }else {/*
            if (joueurQuiPioche[a].deck[i].rotation==0) {
                al_draw_bitmap_region(ensemblecartes, joueurQuiPioche[a].deck[i].x, joueurQuiPioche[a].deck[i].y,
                                      LARGEUR_CARTE,
                                      HAUTEUR_CARTE, (float)(400 + i * (LARGEUR_CARTE - 10)), 30, 0);}else {
                al_draw_tinted_scaled_rotated_bitmap_region(ensemblecartes, joueurQuiPioche[a].deck[i].x,
                                                            joueurQuiPioche[a].deck[i].y, LARGEUR_CARTE,
                                                            HAUTEUR_CARTE, al_map_rgba(255, 255, 255, 255),
                                                            LARGEUR_CARTE / 2, HAUTEUR_CARTE / 2,
                                                            (float)(joueurQuiPioche[a].deck[i].positionX +
                                                            LARGEUR_CARTE / 2),
                                                            (float)(joueurQuiPioche[a].deck[i].positionY +
                                                            HAUTEUR_CARTE / 2),
                                                            1, 1, (float)3.1415926535, 0);
            }
            al_draw_rectangle((float)(400 + i * (LARGEUR_CARTE - 10)), 30,(float)(400 + i * (LARGEUR_CARTE - 10) + LARGEUR_CARTE),
                              30 + HAUTEUR_CARTE, al_map_rgb(10, 10, 10), 2);
        */}
    }
}

