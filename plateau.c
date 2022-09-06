#include "fonctions.h"

void preparationJeu(joueur* JoueurListe, short NbJoueur,carte* cartes, short* NbCartesPioche,CasePlateau** cases){
    JoueurListe[rand()%NbJoueur].role = 1;
    for (int i = 0; i < NbJoueur; ++i) {
        for (int j = 0; j < PSEUDOMAX; ++j) {
            JoueurListe[i].pseudo[j]='\0';
        }
        for (int j = 0; j < DECK_MAX; ++j) {
            JoueurListe[i].deck[j].rotation=false;
        }
        for (int k = 0; k < 6; ++k) {
            piocher(JoueurListe, cartes, NbCartesPioche, (short)i);
        }
    }
    cases[2][0].carteaffilie=cartes[72];
    cases[2][0].utilise=1;
    int val1=rand()%3;
    int val2=rand()%2+1;
    int tab[3];
    tab[0]=val1;
    tab[1]=(val1+val2)%3;
    for (int i=0; i < 3 ;++i){
        if (i!= tab[1] && i!= tab[0]){
            tab[2]=i;
        }
    }
    cases[2*tab[0]][8].carteaffilie=cartes[69];
    cases[2*tab[0]][8].utilise=1;
    cases[2*tab[1]][8].carteaffilie=cartes[70];
    cases[2*tab[1]][8].utilise=1;
    cases[2*tab[2]][8].carteaffilie=cartes[71];
    cases[2*tab[2]][8].utilise=1;

}
void dessinFondTableauCartes(CasePlateau** cases,ALLEGRO_BITMAP *ensemblecartes, bool boolpossibilite, bool possibiliteEboulement) {
    for (int i = 0; i < NB_CARTES_VERTICALES; i++) {
        for (int j = 0; j < NB_CARTES_HORIZONTALES; j++){
            cases[i][j].positionX1 =(short)(j * LARGEUR_CARTE);
            cases[i][j].positionY1 =(short)(i * HAUTEUR_CARTE+POSITION_DEBUT_PLATEAU);
            cases[i][j].couleurFond = al_map_rgba(0,0,0,130);
        }
    }
    for (int i = 0; i < NB_CARTES_VERTICALES; i++) {
        for (int j = 0; j < NB_CARTES_HORIZONTALES; j++) {
            al_draw_filled_rectangle(cases[i][j].positionX1, cases[i][j].positionY1,
                                     LARGEUR_CARTE + cases[i][j].positionX1, HAUTEUR_CARTE + cases[i][j].positionY1,
                                     cases[i][j].couleurFond);
            if (boolpossibilite == true && cases[i][j].possible == 1) {
                al_draw_filled_rectangle(cases[i][j].positionX1, cases[i][j].positionY1,
                                         LARGEUR_CARTE + cases[i][j].positionX1, HAUTEUR_CARTE + cases[i][j].positionY1,
                                         al_map_rgba(114, 214, 114, 230));
            }
            if (cases[i][j].utilise == true) {
                if (cases[i][j].carteaffilie.rotation == false) {
                    al_draw_bitmap_region(ensemblecartes, cases[i][j].carteaffilie.x, cases[i][j].carteaffilie.y,
                                          LARGEUR_CARTE, HAUTEUR_CARTE, cases[i][j].positionX1, cases[i][j].positionY1,
                                          0);

                } else {
                    al_draw_tinted_scaled_rotated_bitmap_region(ensemblecartes, cases[i][j].carteaffilie.x,
                                                                cases[i][j].carteaffilie.y, LARGEUR_CARTE,
                                                                HAUTEUR_CARTE, al_map_rgba(255, 255, 255, 255),
                                                                LARGEUR_CARTE / 2, HAUTEUR_CARTE / 2,
                                                                (float)(cases[i][j].positionX1 + LARGEUR_CARTE / 2),
                                                                (float)(cases[i][j].positionY1 + HAUTEUR_CARTE / 2),
                                                                1, 1, (float)3.1415926535, 0);

                }
                al_draw_rectangle(cases[i][j].positionX1, cases[i][j].positionY1,
                                  LARGEUR_CARTE + cases[i][j].positionX1, HAUTEUR_CARTE + cases[i][j].positionY1,
                                  al_map_rgba(20, 20, 20, 130), 1);
                if (possibiliteEboulement == true && cases[i][j].carteaffilie.cartefin == 0 &&
                    cases[i][j].carteaffilie.premiere == 0) {
                    al_draw_filled_rectangle(cases[i][j].positionX1, cases[i][j].positionY1,
                                             LARGEUR_CARTE + cases[i][j].positionX1,
                                             HAUTEUR_CARTE + cases[i][j].positionY1,
                                             al_map_rgba(114, 174, 114, 50));
                }
            }
            if (cases[i][j].carteaffilie.cartefin==true) {
                al_draw_bitmap_region(ensemblecartes, 6 * LARGEUR_CARTE, 0, LARGEUR_CARTE, HAUTEUR_CARTE,
                                      cases[i][j].positionX1, cases[i][j].positionY1, 0);
            }
        }
    }
}



void dessinZoneJoueurEnAttente(joueur *unJoueur, Zone *zoneAttente, short Nbjoueur, ALLEGRO_FONT* policeMenu, ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP* ensemblecartes){
    for(int i = 0; i < Nbjoueur; i++){
        al_draw_filled_rectangle(zoneAttente->positionX,(float)(zoneAttente->positionY+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)),(float)(zoneAttente->largeur+zoneAttente->positionX),(float)(zoneAttente->positionY+zoneAttente->hauteur+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)),zoneAttente->fond);
        al_draw_rectangle(zoneAttente->positionX,(float)(zoneAttente->positionY+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)),(float)(zoneAttente->largeur+zoneAttente->positionX),(float)(zoneAttente->positionY+zoneAttente->hauteur+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)),al_map_rgb(20,20,20),1);
        al_draw_text(policeMenu,al_map_rgb(25, 25, 25),(float)(zoneAttente->positionX+10),(float)(zoneAttente->positionY+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)+20),0,unJoueur[i].pseudo);
        al_draw_textf(policeGrasPlateau35,al_map_rgb(25, 25, 25),(float)(zoneAttente->positionX+10),(float)(zoneAttente->positionY+i*(zoneAttente->hauteur+ESPACE_ENTRE_ZONES_PLATEAU)+70),0,"Score: %d", unJoueur->score);

        if (unJoueur[i].pioche==0) {
            al_draw_bitmap_region(ensemblecartes, HAUTEUR_LARGEUR_BONUS_MALUS, 3 * HAUTEUR_CARTE, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)(zoneAttente->positionX + 200),
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }else{
            al_draw_bitmap_region(ensemblecartes, HAUTEUR_LARGEUR_BONUS_MALUS, (3 * HAUTEUR_CARTE)+HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)(zoneAttente->positionX + 200),
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }
        if (unJoueur[i].lampe==false) {
            al_draw_bitmap_region(ensemblecartes, 3*HAUTEUR_LARGEUR_BONUS_MALUS, 3 * HAUTEUR_CARTE, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)(zoneAttente->positionX + 260+180),
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }else{
            al_draw_bitmap_region(ensemblecartes, 3*HAUTEUR_LARGEUR_BONUS_MALUS, 3 * HAUTEUR_CARTE+HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)zoneAttente->positionX + 260+180,
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }
        if (unJoueur[i].marteau==false) {
            al_draw_bitmap_region(ensemblecartes, 2*HAUTEUR_LARGEUR_BONUS_MALUS, 3 * HAUTEUR_CARTE, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)zoneAttente->positionX + 260+60,
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }else{
            al_draw_bitmap_region(ensemblecartes, 2*HAUTEUR_LARGEUR_BONUS_MALUS, 3 * HAUTEUR_CARTE+HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, HAUTEUR_LARGEUR_BONUS_MALUS, (float)zoneAttente->positionX + 260+60,
                                  (float)(zoneAttente->positionY + i * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) + 70),
                                  0);
        }
    }
}


void dessinZoneJoueurEnCours(joueur *JoueurListe, Zone *zoneJoueurEnCours, ALLEGRO_FONT* policeMenu,short tour, ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP* ensemblecartes) {
    for (int i = 0; i < JoueurListe[tour].nbCartesDansDeck; ++i) {
        al_draw_filled_rectangle(zoneJoueurEnCours->positionX, zoneJoueurEnCours->positionY,
                                 (float) zoneJoueurEnCours->largeur + (float) zoneJoueurEnCours->positionX,
                                 (float) zoneJoueurEnCours->hauteur + (float) zoneJoueurEnCours->positionY,
                                 zoneJoueurEnCours->fond);
        al_draw_rectangle((float) zoneJoueurEnCours->positionX, (float) zoneJoueurEnCours->positionY,
                          (float) zoneJoueurEnCours->largeur + (float) zoneJoueurEnCours->positionX,
                          (float) zoneJoueurEnCours->hauteur + (float) zoneJoueurEnCours->positionY,
                          al_map_rgb(10, 10, 10), 1);
        al_draw_text(policeGrasPlateau35, al_map_rgb(25, 25, 25),
                     (float) zoneJoueurEnCours->positionX + ESPACE_ENTRE_ZONES_PLATEAU,
                     (float) zoneJoueurEnCours->positionY + ESPACE_ENTRE_ZONES_PLATEAU, 0, JoueurListe[tour].pseudo);
        al_draw_textf(policeMenu, al_map_rgb(25, 25, 25),
                      (float) zoneJoueurEnCours->positionX + ESPACE_ENTRE_ZONES_PLATEAU,
                      (float) zoneJoueurEnCours->positionY + 5 * ESPACE_ENTRE_ZONES_PLATEAU, 0, "Rôle :");
        if (JoueurListe[tour].role == 1) {
            al_draw_textf(policeGrasPlateau35, al_map_rgb(25, 25, 185),
                          (float) zoneJoueurEnCours->positionX + ESPACE_ENTRE_ZONES_PLATEAU,
                          (float) zoneJoueurEnCours->positionY + 8 * ESPACE_ENTRE_ZONES_PLATEAU, 0, "policier");
        } else {
            al_draw_textf(policeGrasPlateau35, al_map_rgb(185, 25, 25),
                          (float) zoneJoueurEnCours->positionX + ESPACE_ENTRE_ZONES_PLATEAU,
                          (float) zoneJoueurEnCours->positionY + 8 * ESPACE_ENTRE_ZONES_PLATEAU, 0, "cambrioleur");
        }
    }
}

//vérifier si le chemin créé par les cartes est possible
