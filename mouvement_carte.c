#include "fonctions.h"

  //----------------------------------------------------------------------------------------------------------------//
 //                            Gère le mouvement des cartes                                                        //
//----------------------------------------------------------------------------------------------------------------//

void mouvementCartes(ALLEGRO_MOUSE_STATE etat_souris, ALLEGRO_BITMAP *ensemblecartes, joueur *JoueurListe, short a) {
    for (int i = 0; i < NBCARTES_PIOCHE; ++i) {
        if (JoueurListe[a].deck[i].mouvement == 1) { // Si un mouvement dans le deck par le joueur est détecté
            JoueurListe[a].deck[i].positionX = etat_souris.x - LARGEUR_CARTE / 2;
            JoueurListe[a].deck[i].positionY = etat_souris.y - HAUTEUR_CARTE / 2;
        }
    }
}

  //-------------------------------------------------------------------------------------------------//
 //                            Gère la pose des malus joueurs                                       //
//-------------------------------------------------------------------------------------------------//

void poseBonusMalus(joueur *JoueurListe, short *tour, Zone *zoneAttente, short Nbjoueur){
    for (int k = 0; k < Nbjoueur; ++k) {
        for (int i = 0; i < JoueurListe[*tour].nbCartesDansDeck; ++i) {
            if (JoueurListe[*tour].deck[i].mouvement == 1 &&
                JoueurListe[*tour].deck[i].pioche_deffause_main == 2 &&
                JoueurListe[*tour].deck[i].action == 1 &&
                JoueurListe[*tour].deck[i].positionX + (LARGEUR_CARTE / 2) > zoneAttente->positionX &&
                JoueurListe[*tour].deck[i].positionX + (LARGEUR_CARTE / 2) < zoneAttente->largeur + zoneAttente->positionX &&
                JoueurListe[*tour].deck[i].positionY + (HAUTEUR_CARTE / 2) > zoneAttente->positionY + k * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU) &&
                JoueurListe[*tour].deck[i].positionY + (HAUTEUR_CARTE / 2) < zoneAttente->positionY + zoneAttente->hauteur + k * (zoneAttente->hauteur + ESPACE_ENTRE_ZONES_PLATEAU))
            {

                // On va exécuter un code selon le type d'action qui est utilisée.

                if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_LAMPE && JoueurListe[k].lampe == false){
                    JoueurListe[k].lampe=true;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_PIOCHE && JoueurListe[k].pioche == false){
                    JoueurListe[k].pioche=true;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_MARTEAU_PIQUEUR && JoueurListe[k].marteau == false){
                    JoueurListe[k].marteau=true;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE && JoueurListe[k].pioche == true){
                    JoueurListe[k].pioche=false;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_LAMPE && JoueurListe[k].lampe == true){
                    JoueurListe[k].lampe=false;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR && JoueurListe[k].marteau == true){
                    JoueurListe[k].marteau=false;
                    JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                    *tour=(*tour+1)%Nbjoueur;
                }
                if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS){
                    if (JoueurListe[k].pioche==false || JoueurListe[k].lampe==false || JoueurListe[k].marteau==false){
                        JoueurListe[k].pioche=true;
                        JoueurListe[k].lampe=true;
                        JoueurListe[k].marteau=true;
                        JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                        *tour=(*tour+1)%Nbjoueur;
                    }
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE_LAMPE){
                    if (JoueurListe[k].pioche == true || JoueurListe[k].lampe == true){
                        JoueurListe[k].pioche=false;
                        JoueurListe[k].lampe=false;
                        JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                        *tour=(*tour+1)%Nbjoueur;
                    }
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_LAMPE){
                    if (JoueurListe[k].marteau == true || JoueurListe[k].lampe == true){
                        JoueurListe[k].marteau=false;
                        JoueurListe[k].lampe=false;
                        JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                        *tour=(*tour+1)%Nbjoueur;
                    }
                }
                if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_PIOCHE){
                    if (JoueurListe[k].marteau == true || JoueurListe[k].pioche == true){
                        JoueurListe[k].marteau=false;
                        JoueurListe[k].pioche=false;
                        JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                        *tour=(*tour+1)%Nbjoueur;
                    }
                }
            }
        }
    }
}

  //----------------------------------------------------------------------------------------------------------------//
 //                            Gère la pose des cartes sur le plateau                                              //
//----------------------------------------------------------------------------------------------------------------//
void poseCartesurPlateau(joueur *JoueurListe, short* tour, CasePlateau **cases, short Nbjoueur) {

    for (int j = 0; j < NB_CARTES_VERTICALES; ++j) {

        for (int k = 0; k < NB_CARTES_HORIZONTALES; ++k) {

            for (int i = 0; i < JoueurListe[*tour].nbCartesDansDeck; ++i) {
                if (JoueurListe[*tour].deck[i].mouvement == 1 &&
                    JoueurListe[*tour].deck[i].pioche_deffause_main == 2 &&
                    JoueurListe[*tour].deck[i].positionX + (LARGEUR_CARTE / 2) > cases[j][k].positionX1 &&
                    JoueurListe[*tour].deck[i].positionX + (LARGEUR_CARTE / 2) < cases[j][k].positionX1 + LARGEUR_CARTE &&
                    JoueurListe[*tour].deck[i].positionY + (HAUTEUR_CARTE / 2) > cases[j][k].positionY1 &&
                    JoueurListe[*tour].deck[i].positionY + (HAUTEUR_CARTE / 2) < cases[j][k].positionY1 + HAUTEUR_CARTE) {

                    // Le test ci dessus vérifie que :
                    // - La carte est une carte mouvement
                    // - Qu'elle est bien dans la main du joueur
                    // - Vérifie que la carte est posée dans une case
                    //if(JoueurListe[*tour].pioche== 0 && JoueurListe[*tour].lampe== 0 && JoueurListe[*tour].marteau== 0) {
                        if (JoueurListe[*tour].deck[i].chemin == 1 && cases[j][k].utilise == 0 &&
                            cases[j][k].possible == 1) {
                            cases[j][k].carteaffilie = JoueurListe[*tour].deck[i];
                            cases[j][k].utilise = 1;
                            JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                            *tour = (*tour + 1) % Nbjoueur;
                        }else if (JoueurListe[*tour].deck[i].actiontype == EBOULEMENT && cases[j][k].utilise == 1 &&
                        cases[j][k].carteaffilie.premiere != 1 && cases[j][k].carteaffilie.cartefin != 1) {
                            JoueurListe[*tour].deck[i].pioche_deffause_main = 1;
                            cases[j][k].utilise = 0;
                            *tour = (*tour + 1) % Nbjoueur;
                        }/*else if (JoueurListe[*tour].deck[i].actiontype == PLAN && cases[j][k].carteaffilie.cartefin != 0 ) {
                        JoueurListe[*tour].deck[i].pioche_deffause_main =1;
                        cases[j][k].utilise =0;
                        *tour=(*tour+1)%Nbjoueur;
                    }*/
                    //}
                }
            }
        }
    }
}