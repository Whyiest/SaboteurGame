#include "fonctions.h"

//FONCTION QUI GERE LE DEGRADE AU DEBUT :

void fondudegrade(degrade *degrades) {
    if (degrades->croissance == true) {
        degrades->valeur += 3;
    } else { degrades->valeur -= 3; }
    if (degrades->valeur > 240) {
        degrades->croissance = false;
    }
    if (degrades->valeur < 60) {
        degrades->croissance = true;
    }
}

//FONCTION QUI PERMET DE CREER TOUS LES BOUTONS DU PROGRAMME :
short bouton(ALLEGRO_MOUSE_STATE mouse, int x, int y, int l, int h, ALLEGRO_COLOR cb1,
             ALLEGRO_COLOR cb2, short a, ALLEGRO_FONT *police, int ht, char *texte, ALLEGRO_COLOR ct, bool clic) {
    if (mouse.x < x + l && mouse.x > x && mouse.y < y + h &&
        mouse.y > y) {// On verifie les coordonées de la souris vis à vis de la fonction
        al_draw_filled_rectangle((float) x - (float) a, (float) y - (float) a, (float) x + (float) l + (float) a,
                                 (float) y + (float) h + (float) a, cb2);
        if (clic == true) {
            return 1; // La fonction retourne 1 en cas de clic sur le bouton.
        }
    } else {
        al_draw_filled_rectangle((float) x, (float) y, (float) (x + l), (float) (y + h),
                                 cb1); // Creer un agrandissement + change la couleur
    }
    al_draw_text(police, ct, (float) (x + (l / 2)), (float) ((y + (h / 2)) - (ht / 1.6)), ALLEGRO_ALIGN_CENTRE,
                 texte);//Place le texte au milieu du bouton
    return 0;
}

//FONCTION QUI PERMET D'INVERSER LES VALEURS DES CARTES CHEMINS
void rotation(carte *carte1) {
    if (carte1->chemin == 1) {
        carte1->rotation = !carte1->rotation;//Change la valeur de la variable booléene
        carte carte2 = *carte1; //Creer une copie pour pouvoir effectuer les changements
        if (carte2.gauche) {
            carte1->droite = 1;
        } else { carte1->droite = 0; }

        if (carte2.droite) {
            carte1->gauche = 1;
        } else { carte1->gauche = 0; }

        if (carte2.bas) {
            carte1->haut = 1;
        } else { carte1->haut = 0; }

        if (carte2.haut) {
            carte1->bas = 1;
        } else { carte1->bas = 0; }
    }
}

//VERIFICATION SI ON PEUT POSER UNE CARTE A COTE D'UNE AUTRE
void possibilite(CasePlateau **cases, joueur *JoueurListe, short tour) {
    for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
        for (int j = 0; j < NB_CARTES_HORIZONTALES; ++j) { //Verifie tout les valeurs du plateau
            if (cases[i][j].carteaffilie.cartefin == false) {
                for (int k = 0; k < JoueurListe[tour].nbCartesDansDeck; ++k) {//Verifie tout les cartes de la main du joueur
                    if (cases[i][j].utilise == 1 && JoueurListe[tour].deck[k].mouvement == 1) {//Agit seulement quand une carte est en mvt et sur les cartes deja posées
                        if (cases[i][j].carteaffilie.droite == 1 && JoueurListe[tour].deck[k].gauche == 1) {
                            cases[i][j + 1].possible = 1;//Est ce qu'il y a un chemin depuis le haut
                        }

                        if (cases[i][j].carteaffilie.gauche == 1 && JoueurListe[tour].deck[k].droite == 1) {
                            cases[i][j - 1].possible = 1;//Est ce qu'il y a un chemin depuis la gauche
                        }
                        if (i < 4) {
                            if (cases[i][j].carteaffilie.bas == 1 && JoueurListe[tour].deck[k].haut == 1) {
                                cases[i + 1][j].possible = 1;//Est ce qu'il y a un chemin depuis le bas
                            }
                        }
                        if (i > 0) {
                            if (cases[i][j].carteaffilie.haut == 1 && JoueurListe[tour].deck[k].bas == 1) {
                                cases[i - 1][j].possible = 1;//Est ce qu'il y a un chemin depuis la droite
                            }
                        }

                    }
                }
            } else { //Pour les cartes fins
                if (i > 0) {//Est ce qu'il y a un chemin depuis le haut
                    if (cases[i - 1][j].utilise == 1 && cases[i - 1][j].carteaffilie.bas == 1) {
                        cases[i][j].carteaffilie.cartefin = 0;
                    }
                }
                if (i < 4) {//Est ce qu'il y a un chemin depuis le bas
                    if (cases[i + 1][j].utilise == 1 && cases[i + 1][j].carteaffilie.haut == 1) {
                        cases[i][j].carteaffilie.cartefin = 0;
                    }
                }
                //Est ce qu'il y a un chemin depuis la gauche
                if (cases[i][j - 1].utilise == 1 && cases[i][j - 1].carteaffilie.droite == true) {
                    cases[i][j].carteaffilie.cartefin = 0;
                }
            }
        }
    }
}

//FONCTION QUI PERMET DE PASSER LE TOUR
void passerletour(short *tour, short Nbjoueur, ALLEGRO_MOUSE_STATE etat_souris, ALLEGRO_FONT *policemenu, bool clic) {
    if (bouton(etat_souris, 900, 50, 200, 50, al_map_rgba(114, 114, 114, 150), al_map_rgb(180, 180, 180), 2, policemenu,
               35, "Passer", al_map_rgb(50, 50, 50), clic)==1) {
        *tour = (short) ((*tour + 1) % Nbjoueur); }
}

//FONCTION QUI GERE LA LIBERATION
void liberation(Zone *zoneJoueurEnCours, carte *CarteListe, Zone *zoneAttente, joueur *JoueurListe, CasePlateau **cases,
                ALLEGRO_BITMAP *fondmenu, ALLEGRO_BITMAP *fondplateau, ALLEGRO_BITMAP *ensemblecartes, ALLEGRO_DISPLAY *fenetre,
                ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_FONT *policeMenu35, ALLEGRO_FONT *policePause120,
                ALLEGRO_FONT *policeMenu65, ALLEGRO_SAMPLE *musiquefond, ALLEGRO_SAMPLE *sonclick,ALLEGRO_BITMAP* fondtitre) {
    JoueurListe = NULL;
    zoneJoueurEnCours = NULL;
    zoneAttente=NULL;
    CarteListe = NULL;
    free(zoneAttente);
    free(JoueurListe);
    free(zoneJoueurEnCours);
    free(CarteListe);
    for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
        cases[i] = NULL;
        free(cases[i]);
    }
    cases = NULL;
    free(cases);
    ensemblecartes=NULL;
    al_destroy_bitmap(ensemblecartes);
    fondtitre=NULL;
    al_destroy_bitmap(fondtitre);
    al_destroy_event_queue(queue);
    timer=NULL;
    al_destroy_timer(timer);
    policeMenu65=NULL;
    al_destroy_font(policeMenu65);
    policeMenu35=NULL;
    al_destroy_font(policeMenu35);
    policePause120=NULL;
    al_destroy_font(policePause120);
    musiquefond=NULL;
    al_destroy_sample(musiquefond);
    sonclick=NULL;
    al_destroy_sample(sonclick);
    fondmenu=NULL;
    al_destroy_bitmap(fondmenu);
    fondplateau=NULL;
    al_destroy_bitmap(fondplateau);
    fenetre=NULL;
    al_destroy_display(fenetre);

}

