#include "fonctions.h"

void Menu(ALLEGRO_MOUSE_STATE etat_souris, short *menu, short *NbJoueur, bool clic, ALLEGRO_FONT *policeMenu65,
          ALLEGRO_FONT *policeMenu35, ALLEGRO_FONT *policePause120, ALLEGRO_FONT *policeTitre80, bool *pseudo_joueur,
          joueur *JoueurListe, ALLEGRO_BITMAP *ensemblecartes, short *ordre, carte* cartes, short *NbCartesPioche,
          CasePlateau **cases, bool *Fin, bool *aideenjeu, ALLEGRO_SAMPLE *sonclick,
          degrade *degrades, short *tour, bool clicdroit, bool possibilitebool, bool possibiliteEboulement,
          Zone *zoneAttente, Zone *zoneJoueurEnCours, ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP *fondplateau) {

    //------------------------------------------------------------------------------------------------------------------//
    //                             La variable menu définit le menu à affiché                                          //
    //----------------------------------------------------------------------------------------------------------------//
    switch (*menu) {
        case 0:
            Menu0(policeTitre80, policeMenu35, degrades, clic, menu);
            break;
        case 1:
            Menu1(aideenjeu, etat_souris, policeMenu65, clic, menu, sonclick);
            break;
        case 2:
            Menu2(etat_souris, policeMenu65, clic, menu, sonclick, JoueurListe, NbJoueur, cartes, NbCartesPioche,
                  cases);
            break;
        case 3:
            Menu3(aideenjeu, *NbJoueur, etat_souris, policeMenu65, clic, menu, sonclick, pseudo_joueur, JoueurListe,
                  policeMenu35);
            break;
        case 4:
            Menu4(ordre, NbJoueur, JoueurListe, ensemblecartes, policeMenu65, policeMenu35, etat_souris, clic,
                  sonclick, menu,NbCartesPioche,cartes);
            break;
        case 5:
            // Affichage du plateau
            al_draw_bitmap(fondplateau, 0, 0, 0);
                dessinZoneJoueurEnAttente(JoueurListe, zoneAttente, *NbJoueur, policeMenu35, policeGrasPlateau35,
                                          ensemblecartes);
                mouvementCartes(etat_souris, ensemblecartes, JoueurListe, *tour);
                dessinFondTableauCartes(cases, ensemblecartes, possibilitebool, possibiliteEboulement);
                dessinZoneJoueurEnCours(JoueurListe, zoneJoueurEnCours, policeMenu35, *tour, policeGrasPlateau35,
                                        ensemblecartes);
                dessinCartes(JoueurListe, ensemblecartes, *tour, etat_souris, clicdroit);
                possibilite(cases, JoueurListe, *tour);
                passerletour(tour, *NbJoueur, etat_souris, policeMenu35, clic);
            for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
                if (cases[i][8].carteaffilie.or == 1 && cases[i][8].possible == 1) {
                    *menu = 6;
                }
            }
            if (*NbCartesPioche==0) {
                *menu =7;
            }
                break;
        case 6:
            Menu6(policeMenu65,etat_souris,clic,sonclick,Fin);
                break;
        case 7:
            Menu7(policeMenu65,etat_souris,clic,sonclick,Fin);
            break;
        case 8:
            al_draw_bitmap(fondplateau, 0, 0, 0);
            if (*tour==0) {
                dessinZoneJoueurEnAttente(JoueurListe, zoneAttente, *NbJoueur, policeMenu35, policeGrasPlateau35,
                                          ensemblecartes);
                mouvementCartes(etat_souris, ensemblecartes, JoueurListe, *tour);
                dessinFondTableauCartes(cases, ensemblecartes, possibilitebool, possibiliteEboulement);
                dessinZoneJoueurEnCours(JoueurListe, zoneJoueurEnCours, policeMenu35, *tour, policeGrasPlateau35,
                                        ensemblecartes);
                dessinCartes(JoueurListe, ensemblecartes, *tour, etat_souris, clicdroit);
                possibilite(cases, JoueurListe, *tour);
                passerletour(tour, *NbJoueur, etat_souris, policeMenu35, clic);
            }else{
                bool choix = true;
                jouerCarteaction(JoueurListe,tour,&choix);
                jouerCartechemin(JoueurListe,tour,cases,&choix);
                deffause(JoueurListe, *tour, cartes, NbCartesPioche);
                dessinCartes(JoueurListe, ensemblecartes, *tour, etat_souris, clicdroit);
                passerletour(tour, *NbJoueur, etat_souris, policeMenu35, clic);
            }
            for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
                if (cases[i][8].carteaffilie.or == 1 && cases[i][8].possible == 1) {
                    *menu = 6;
                }
            }
            break;
        case 30:
            Aide0(*aideenjeu, etat_souris, clic, menu, policeMenu35, sonclick);
            break;
        case 31:
            Aide1(*aideenjeu, etat_souris, clic, menu, policeMenu35, sonclick);
            break;
        case 32:
            Aide2(*aideenjeu, etat_souris, clic, menu, policeMenu35, sonclick);
            break;
        case 40:
            ChargerPartie(etat_souris, clic,menu,policeMenu35,sonclick);
            break;
        case 50 :
            MenuEchape0(etat_souris, clic, menu, policeMenu35, policePause120, sonclick);
            break;
        case 51:
            MenuEchape1(etat_souris, clic, menu, policeMenu35, policePause120, sonclick, Fin);
            break;
    }
}


//------------------------------------------------------------------------------------------------------------------//
//                              Définition de chaque menu appelé et de son contenu                                 //
//----------------------------------------------------------------------------------------------------------------//

void Menu0(ALLEGRO_FONT *policeTitre80, ALLEGRO_FONT *policeMenu35, degrade *degrades, bool clic, short *menu) {
    al_draw_filled_rectangle(0, 307, LARGEUR, 377, al_map_rgba(0, 0, 0, 80));
    al_draw_textf(policeTitre80, al_map_rgb(255, 255, 255), LARGEUR / 2, 307, ALLEGRO_ALIGN_CENTER,
                  "U n d e r g r o u n d");//Affichage Titre
    al_draw_textf(policeMenu35, al_map_rgb(degrades->valeur, degrades->valeur, degrades->valeur),
                  LARGEUR / 2, 550, ALLEGRO_ALIGN_CENTER, "Appuie sur une touche pour commencer");//Afficahge texte
    fondudegrade(degrades);
    if (clic == true) {
        *menu = 1;//Change pour le menu
    }
}

void Menu1(bool *aideenjeu, ALLEGRO_MOUSE_STATE etat_souris, ALLEGRO_FONT *policeMenu65, bool clic, short *menu,
           ALLEGRO_SAMPLE *sonclick) {
    *aideenjeu = false;
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7, 2 * LARGEUR / 3, 100, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "Nouvelle Partie",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *menu = 2; //Lance une nouvelle Partie
    }
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7 + 200, 2 * LARGEUR / 3, 100,
               al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "Charger Partie",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *menu = 40;//Ne fais rien mais faut pas le dire
    }
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7 + 400, 2 * LARGEUR / 3, 100,
               al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "Aide",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *menu = 30;//Acces à la premiere page de l'aide
    }
}

void
Menu2(ALLEGRO_MOUSE_STATE etat_souris, ALLEGRO_FONT *policeMenu65, bool clic, short *menu, ALLEGRO_SAMPLE *sonclick,
      joueur *JoueurListe, short *NbJoueur, carte *cartes, short *NbCartesPioche, CasePlateau **cases) {
    if (bouton(etat_souris, 50, 50, 100, 100, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "IA",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *NbJoueur = 1;//Choix du nombre de joueur
        preparationJeu(JoueurListe, *NbJoueur, cartes, NbCartesPioche,
                       cases);//Initialise la pioche + carte debut et fin
        *menu = 3;//Passe au choix des pseudos
    }
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7, 2 * LARGEUR / 3, 100, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "2 Joueurs",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *NbJoueur = 2;//Choix du nombre de joueur
        preparationJeu(JoueurListe, *NbJoueur, cartes, NbCartesPioche,
                       cases);//Initialise la pioche + carte debut et fin
        *menu = 3;//Passe au choix des pseudos
    }
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7 + 200, 2 * LARGEUR / 3, 100,
               al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "3 Joueurs",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *NbJoueur = 3;//Choix du nombre de joueur
        preparationJeu(JoueurListe, *NbJoueur, cartes, NbCartesPioche,
                       cases);//Initialise la pioche + carte debut et fin
        *menu = 3;//Passe au choix des pseudos

    }
    if (bouton(etat_souris, LARGEUR / 6, HAUTEUR / 7 + 400, 2 * LARGEUR / 3, 100,
               al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "4 Joueurs",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *NbJoueur = 4;//Choix du nombre de joueur
        preparationJeu(JoueurListe, *NbJoueur, cartes, NbCartesPioche,
                       cases);//Initialise la pioche + carte debut et fin
        *menu = 3;//Passe au choix des pseudos
    }
}

void Menu3(bool *aideenjeu, short NbJoueur, ALLEGRO_MOUSE_STATE etat_souris, ALLEGRO_FONT *policeMenu65, bool clic,
           short *menu, ALLEGRO_SAMPLE *sonclick, bool *pseudo_joueur, joueur *JoueurListe,
           ALLEGRO_FONT *policeMenu35) {
    *aideenjeu = true;
    for (int i = 0; i < NbJoueur; i++) {
        ALLEGRO_COLOR couleur_bouton = al_map_rgb(225, 225, 225);
        al_draw_filled_rectangle(LARGEUR / 10,
                                 (float) ((HAUTEUR / (3.5 * NbJoueur)) + (i * (4 / NbJoueur) * 150)),
                                 LARGEUR / 10 + 300,
                                 (float) ((HAUTEUR / (3.5 * NbJoueur)) + (i * (4 / NbJoueur) * 150) + 80),
                                 al_map_rgb(63, 63, 67));
        al_draw_textf(policeMenu35, al_map_rgb(225, 225, 225), LARGEUR / 10 + 300 / 2,
                      (float) ((HAUTEUR / (3.5 * NbJoueur)) + (i * (4 / NbJoueur) * 150) + 20),
                      ALLEGRO_ALIGN_CENTRE, "Joueur %d", i + 1);
        if (pseudo_joueur[i] == 1) {
            couleur_bouton = al_map_rgb(150, 150, 150);
        }
        if (bouton(etat_souris, LARGEUR / 10 + 300,
                   (int) ((HAUTEUR / (3.5 * NbJoueur)) + (i * (4 / NbJoueur) * 150)),
                   8 * LARGEUR / 10 - 300, 80, couleur_bouton, couleur_bouton, 0, policeMenu35, 35,
                   JoueurListe[i].pseudo,
                   al_map_rgb(20, 20, 20), clic) == 1) {
            for (int f = 0; f < NbJoueur; f++) {
                pseudo_joueur[f] = false;
            }
            pseudo_joueur[i] = true;
        }
    }

    if (bouton(etat_souris, LARGEUR / 2 - 150, 5 * HAUTEUR / 7 + 70, 400, 100,
               al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "START",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

        *menu = 4;
    }
}

void
Menu4(short *ordre, short* NbJoueur, joueur *JoueurListe, ALLEGRO_BITMAP *ensemblecartes, ALLEGRO_FONT *policeMenu65,
      ALLEGRO_FONT *policeMenu35, ALLEGRO_MOUSE_STATE etat_souris, bool clic, ALLEGRO_SAMPLE *sonclick, short *menu,short* NbCartesPioche,carte *cartes) {
   if  (*NbJoueur==1){
       JoueurListe[0].role=0;
   }
    if (*ordre < *NbJoueur) {
        affichageRole(JoueurListe, ensemblecartes, ordre, policeMenu65, policeMenu35, etat_souris, clic,
                      sonclick);
    } else {
        for (int a = 0; a < JOUEUR_MAX; ++a) {
            for (int i = 0; i < NBCARTES; ++i) {
                JoueurListe[a].deck[i].mouvement = 0;
            }
        }
        if (*NbJoueur !=1){
        *menu = 5;}
        else{
            *NbJoueur =2;
            for (int k = 0; k < 6; ++k) {
                piocher(JoueurListe, cartes, NbCartesPioche,1);
            }
            *menu = 8;
        }
    }
}

void Menu6(ALLEGRO_FONT* policeMenu65,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE* sonclick,bool* Fin) {
    al_draw_filled_rectangle(200, HAUTEUR / 2 - 80, 1170, HAUTEUR / 2 + 80, al_map_rgba(35, 35, 35, 180));
    al_draw_textf(policeMenu65, al_map_rgb(240, 240, 240), LARGEUR / 2, HAUTEUR / 2.5, ALLEGRO_ALIGN_CENTER,
                  "Victoire des");
    al_draw_textf(policeMenu65, al_map_rgb(240, 60, 60), LARGEUR / 2, HAUTEUR / 2.5 + 70, ALLEGRO_ALIGN_CENTER,
                  "cambrioleurs");
    if (bouton(etat_souris, LARGEUR / 2-400, 3*HAUTEUR / 4, 750, 80, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "Fin de Partie",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *Fin=1;
    }
}
void Menu7(ALLEGRO_FONT* policeMenu65,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE* sonclick,bool* Fin) {
    al_draw_filled_rectangle(200, HAUTEUR / 2 - 80, 1170, HAUTEUR / 2 + 80, al_map_rgba(35, 35, 35, 180));
    al_draw_textf(policeMenu65, al_map_rgb(240, 240, 240), LARGEUR / 2, HAUTEUR / 2.5, ALLEGRO_ALIGN_CENTER,
                  "Victoire des");
    al_draw_textf(policeMenu65, al_map_rgb(60, 60, 240), LARGEUR / 2, HAUTEUR / 2.5 + 70, ALLEGRO_ALIGN_CENTER,
                  "policier");
    if (bouton(etat_souris, LARGEUR / 2-400, 3*HAUTEUR / 4, 750, 80, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu65, 65, "Fin de Partie",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);//Son du clic
        *Fin=1;
    }
}

//--------------------- MENU D'AIDE -------------------------//

void Aide0(bool aideenjeu, ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
           ALLEGRO_SAMPLE *sonclick) {
    al_draw_filled_rectangle(100, 100, 1300, 700, al_map_rgba(35, 35, 35, 220));
    al_draw_filled_circle(1250, 140, 20, al_map_rgb(212, 66, 62));
    if ((etat_souris.x - 1250) < 20 && (etat_souris.x - 1250) > -20 && (etat_souris.y - 140) < 20 &&
        (etat_souris.y - 140) > -20) {
        if (clic == true) {
            if (aideenjeu == true) {
                *menu = 50;
            } else {
                *menu = 1;
            }
        }
        al_draw_filled_circle(1250, 140, 23, al_map_rgb(242, 96, 92));
    }
    al_draw_line(1240, 130, 1260, 150, al_map_rgb(205, 205, 205), 3);
    al_draw_line(1240, 150, 1260, 130, al_map_rgb(205, 205, 205), 3);
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 150, 0,"Joueur:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 185, 0,"Le nombre de joueurs sera saisi (entre 2 et 4). Chaque joueur");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 220, 0,"se voit attribuer une carte de rôle : saboteur ou chercheur d’or.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 255, 0,"Il y aura toujours un saboteur. Le rôle de chacun est caché aux");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 290, 0,"adversaires.Chaque joueur reçoit 6 cartes de la pioche.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 340, 0,"Pioche:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 375, 0,"L'ensemble des cartes galerie et action sera mélangé et posé");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 410, 0,"dans la partie vert foncé.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 460, 0,"Tour d'un joueur:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 495, 0,"A chaque tour le joueur peut au choix:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 530, 0,"- Piocher une carte et la jouer.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 565, 0,"    - Si c'est une carte galerie, il la pose  selon sa forme à");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 600, 0,"      côté d’une carte galerie déjà posée. La 1ère carte");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 635, 0,"      galerie est obligatoirement posée à côté de l’entrée de ");




    al_draw_filled_triangle(1250, 630, 1250, 660, 1275, 645, al_map_rgb(205, 205, 205));
    if ((etat_souris.x - 1260) < 10 && (etat_souris.x - 1260) > -10 && (etat_souris.y - 645) < 10 &&
        (etat_souris.y - 645) > -10) {
        if (clic == true) {
            al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            *menu = 31;
        }
        al_draw_filled_triangle(1247, 628, 1247, 662, 1277, 645, al_map_rgb(87, 103, 227));
    }
}

void Aide1(bool aideenjeu, ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
           ALLEGRO_SAMPLE *sonclick) {
    al_draw_filled_rectangle(100, 100, 1300, 700, al_map_rgba(35, 35, 35, 220));
    al_draw_filled_circle(1250, 140, 20, al_map_rgb(212, 66, 62));
    if ((etat_souris.x - 1250) < 20 && (etat_souris.x - 1250) > -20 && (etat_souris.y - 140) < 20 &&
        (etat_souris.y - 140) > -20) {
        if (clic == true) {
            al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            if (aideenjeu == true) {
                *menu = 50;
            } else {
                *menu = 1;
            }
        }
        al_draw_filled_circle(1250, 140, 23, al_map_rgb(242, 96, 92));
    }
    al_draw_line(1240, 130, 1260, 150, al_map_rgb(205, 205, 205), 3);
    al_draw_line(1240, 150, 1260, 130, al_map_rgb(205, 205, 205), 3);
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 150, 0,"       la mine.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 185, 0,"    - Si c'est une carte action:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 220, 0,"- Carte de la map : il peut regarder une des cartes des pépites");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 255, 0,"  retournées (click gauche de la souris maintenu sur la carte");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 290, 0,"  pour la voir)");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 325, 0,"  Carte casser : il la donne à un de ses adversaires (sélection");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 360, 0,"  de la carte -click droit- et drag and drop de la carte vers le");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 395, 0,"  joueur");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 430, 0,"- Carte ‘réparer’ : il la pose devant soi ou devant un autre joueur");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 465, 0,"  s’il y a un outils/chariot est cassé sélection de la carte -click");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 500, 0,"  droit- et ‘drag and drop’ de la carte vers la carte à réparer)");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 535, 0,"- Carte éboulement : il la pose sur la grille au bout d’une galerie");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 570, 0,"  en construction (sélection de la carte - click droit- et ‘drag and");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 605, 0,"  drop’ de la carte à côté d’un bout de tunnel existant)");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 640, 0,"- Défausser 3 cartes (sélection de la(les) carte(s) -click droit-");

    al_draw_filled_triangle(1250, 630, 1250, 660, 1275, 645, al_map_rgb(205, 205, 205));
    if ((etat_souris.x - 1260) < 10 && (etat_souris.x - 1260) > -10 && (etat_souris.y - 645) < 10 &&
        (etat_souris.y - 645) > -10) {
        if (clic == true) {
            al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            *menu = 32;
        }
        al_draw_filled_triangle(1247, 628, 1247, 662, 1277, 645, al_map_rgb(87, 103, 227));
    }

    al_draw_filled_triangle(150, 630, 150, 660, 125, 645, al_map_rgb(205, 205, 205));
    if ((etat_souris.x - 140) < 10 && (etat_souris.x - 140) > -10 && (etat_souris.y - 645) < 10 &&
        (etat_souris.y - 645) > -10) {
        if (clic == true) {
            *menu = 30;
        }
        al_draw_filled_triangle(153, 628, 153, 662, 123, 645, al_map_rgb(87, 103, 227));
    }
}

void Aide2(bool aideenjeu, ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
           ALLEGRO_SAMPLE *sonclick) {
    al_draw_filled_rectangle(100, 100, 1300, 700, al_map_rgba(35, 35, 35, 220));
    al_draw_filled_circle(1250, 140, 20, al_map_rgb(212, 66, 62));
    if ((etat_souris.x - 1250) < 20 && (etat_souris.x - 1250) > -20 && (etat_souris.y - 140) < 20 &&
        (etat_souris.y - 140) > -20) {
        if (clic == true) {
            if (aideenjeu == true) {
                *menu = 50;
            } else {
                *menu = 1;
            }
        }
        al_draw_filled_circle(1250, 140, 23, al_map_rgb(242, 96, 92));
    }
    al_draw_line(1240, 130, 1260, 150, al_map_rgb(205, 205, 205), 3);
    al_draw_line(1240, 150, 1260, 130, al_map_rgb(205, 205, 205), 3);
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 150, 0,"  et ‘drag and drop’ de la carte vers la défausse et en reprendre");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 185, 0,"  3 de la pioche (automatique).");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 225, 0,"A la fin de son tour, c’est au joueur suivant de jouer");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 260, 0,"La partie se termine quand:");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 295, 0,"- Un des chercheurs a retourné une cartede pépites. Les autres");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 330, 0,"  cartes seront données aux deux joueurs (chercheurs d'or ");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 365, 0,"  uniquement) suivant l'ordre de passage après le gagnant. Le ");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 400, 0,"  score de chacun dépend du nombre de pépites d'or obtenue.");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 450, 0,"Le saboteur a gagné : si la pioche est vide ou si les chercheurs");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 485, 0,"n’ont pas réussi à atteindre le trésor et sont bloqués. Le");
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 520, 0,"saboteur reçoit alors le score des trois cartes réunies : 6 points.");
    al_draw_filled_triangle(150, 630, 150, 660, 125, 645, al_map_rgb(205, 205, 205));
    if ((etat_souris.x - 140) < 10 && (etat_souris.x - 140) > -10 && (etat_souris.y - 645) < 10 &&
        (etat_souris.y - 645) > -10) {
        if (clic == true) {
            al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            *menu = 31;
        }
        al_draw_filled_triangle(153, 628, 153, 662, 123, 645, al_map_rgb(87, 103, 227));
    }
}

//--------------------- ECHAP -------------------------//

void MenuEchape0(ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
                 ALLEGRO_FONT *policePause120, ALLEGRO_SAMPLE *sonclick) {
    if (bouton(etat_souris, LARGEUR / 2 - LARGEUR / 6, 350, LARGEUR / 3, 50, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu35, 35, "Retour au jeu",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *menu = 5;
    }
    if (bouton(etat_souris, LARGEUR / 2 - LARGEUR / 6, 450, LARGEUR / 3, 50, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu35, 35, "Aide",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *menu = 30;
    }
    if (bouton(etat_souris, LARGEUR / 2 - LARGEUR / 6, 550, LARGEUR / 3, 50, al_map_rgb(63, 63, 67),
               al_map_rgb(87, 103, 227), 5, policeMenu35, 35, "Quitter le jeu",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *menu = 51;
    }
    al_draw_filled_rectangle(0, 140, LARGEUR, 280, al_map_rgba(0, 0, 0, 80));
    al_draw_textf(policePause120, al_map_rgb(205, 205, 205), 455, 150, 0,
                  "Pause");
}

void MenuEchape1(ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
                 ALLEGRO_FONT *policePause120, ALLEGRO_SAMPLE *sonclick, bool *Fin) {
    al_draw_filled_rectangle(0, 180, LARGEUR, 330, al_map_rgba(0, 0, 0, 80));
    al_draw_textf(policePause120, al_map_rgb(205, 205, 205), 190, 200, 0,
                  "Etes-vous sûr ?");
    if (bouton(etat_souris, 680, 450, LARGEUR / 5, 50, al_map_rgb(63, 63, 67),
               al_map_rgb(170, 0, 0), 5, policeMenu35, 35, "Oui",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *Fin = 1;
    }
    if (bouton(etat_souris, 380, 450, LARGEUR / 5, 50, al_map_rgb(63, 63, 67),
               al_map_rgb(0, 170, 0), 5, policeMenu35, 35, "Retour",
               al_map_rgb(255, 255, 255), clic) == 1) {
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        *menu = 50;
        al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }
}

//--------------------- CHARGER PARTIE -------------------------//


void ChargerPartie(ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,
                   ALLEGRO_SAMPLE *sonclick){
    al_draw_filled_rectangle(100, 100, 1300, 700, al_map_rgba(35, 35, 35, 220));
    al_draw_filled_circle(1250, 140, 20, al_map_rgb(212, 66, 62));
    if ((etat_souris.x - 1250) < 20 && (etat_souris.x - 1250) > -20 && (etat_souris.y - 140) < 20 &&
        (etat_souris.y - 140) > -20) {
        if (clic == true) {
                *menu = 1;
            al_play_sample(sonclick, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        al_draw_filled_circle(1250, 140, 23, al_map_rgb(242, 96, 92));
    }
    al_draw_line(1240, 130, 1260, 150, al_map_rgb(205, 205, 205), 3);
    al_draw_line(1240, 150, 1260, 130, al_map_rgb(205, 205, 205), 3);
    al_draw_textf(policeMenu35, al_map_rgb(205, 205, 205), 150, 150, 0,
                  "AUCUNE SAUVEGARDE TROUVEE...");

}