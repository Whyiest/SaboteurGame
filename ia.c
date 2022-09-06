#include "fonctions.h"

void jouerCarteaction(joueur *JoueurListe, short *tour,bool* choix) {
    for (int i = 0; i < JoueurListe[*tour].nbCartesDansDeck; ++i) {
        if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS ||
            JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_PIOCHE) {
            if (JoueurListe[0].pioche == false) {
                JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                JoueurListe[0].pioche=true;
                if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS){
                    JoueurListe[0].pioche=true;
                    JoueurListe[0].lampe=true;
                    JoueurListe[0].marteau=true;
                }
                *choix=0;
                *tour=0;
            }
        }
        if (*choix==1){
            if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS ||
                JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_LAMPE) {
                if (JoueurListe[0].lampe == false) {
                    JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                    JoueurListe[0].lampe=true;
                    if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS){
                        JoueurListe[0].pioche=true;
                        JoueurListe[0].lampe=true;
                        JoueurListe[0].marteau=true;
                    }
                    *choix=0;
                    *tour=0;
                }
            }
        }
        if (*choix==1){
            if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS ||
                JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_MARTEAU_PIQUEUR) {
                if (JoueurListe[0].marteau == false) {
                    JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                    JoueurListe[0].marteau=true;
                    if (JoueurListe[*tour].deck[i].actiontype == DESTRUCTION_TOUS_OUTILS){
                        JoueurListe[0].pioche=true;
                        JoueurListe[0].lampe=true;
                        JoueurListe[0].marteau=true;
                    }
                    *choix=0;
                    *tour=0;
                }
            }
        }
        if (*choix==1){
            if (JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE_LAMPE ||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_PIOCHE) {
                if (JoueurListe[*tour].pioche == true) {
                    JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                    JoueurListe[*tour].pioche=false;
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE_LAMPE){
                        JoueurListe[*tour].pioche=false;
                        JoueurListe[*tour].lampe=false;
                    }
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_PIOCHE){
                        JoueurListe[*tour].pioche=false;
                        JoueurListe[*tour].marteau=false;
                    }
                    *choix=0;
                    *tour=0;
                }
            }
        }
        if (*choix==1){
            if (JoueurListe[*tour].deck[i].actiontype == REPARATION_LAMPE||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE_LAMPE ||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_LAMPE) {
                if (JoueurListe[*tour].lampe == true) {
                    JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                    JoueurListe[*tour].lampe=false;
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_PIOCHE_LAMPE){
                        JoueurListe[*tour].pioche=false;
                        JoueurListe[*tour].lampe=false;
                    }
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_LAMPE){
                        JoueurListe[*tour].pioche=false;
                        JoueurListe[*tour].lampe=false;
                    }
                    *choix=0;
                    *tour=0;
                }
            }
        }
        if (*choix==1){
            if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_LAMPE ||
                JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_PIOCHE) {
                if (JoueurListe[*tour].marteau == true) {
                    JoueurListe[*tour].deck[i].pioche_deffause_main=1;
                    JoueurListe[*tour].marteau=false;
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_LAMPE){
                        JoueurListe[*tour].marteau=false;
                        JoueurListe[*tour].lampe=false;
                    }
                    if (JoueurListe[*tour].deck[i].actiontype == REPARATION_MARTEAU_PIQUEUR_PIOCHE){
                        JoueurListe[*tour].pioche=false;
                        JoueurListe[*tour].marteau=false;
                    }
                    *choix=0;
                    *tour=0;
                }
            }
        }
    }
}

void jouerCartechemin(joueur *JoueurListe, short* tour, CasePlateau **cases,bool* choix) {
    for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
        for (int j = 0; j < NB_CARTES_HORIZONTALES; ++j) {
            for (int k = 0; k < JoueurListe[*tour].nbCartesDansDeck; ++k) {
                if (cases[i][j].utilise == 1 && cases[i][j].carteaffilie.cartefin==0) {
                    if (j < 8) {
                        if (*choix==1) {
                            if (JoueurListe[*tour].deck[k].chemintype == IMPASSE &&
                                cases[i][j].carteaffilie.droite == 1 &&
                                cases[i][j + 1].utilise == 0) {
                                cases[i][j + 1].carteaffilie = JoueurListe[*tour].deck[k];
                                JoueurListe[*tour].deck[k].pioche_deffause_main = 1;
                                cases[i][j + 1].utilise = 1;
                                *choix = 0;
                                *tour = 0;
                            }
                    }
                    }
                    if(j>0) {
                        if (*choix == 1) {
                            if (JoueurListe[*tour].deck[k].chemintype == DROIT || JoueurListe[*tour].deck[k].chemintype == T_HORIZONTAL || JoueurListe[*tour].deck[k].chemintype == T_VERTICAL || JoueurListe[*tour].deck[k].chemintype == CARREFOUR) {
                                if (cases[i][j].carteaffilie.gauche == 1 &&
                                    cases[i][j - 1].utilise == 0) {
                                    cases[i][j - 1].carteaffilie = JoueurListe[*tour].deck[k];
                                    JoueurListe[*tour].deck[k].pioche_deffause_main = 1;
                                    cases[i][j - 1].utilise = 1;
                                    *choix = 0;
                                    *tour = 0;
                                }
                            }
                        }
                    }
                    if(i<8){
                        if (*choix==1) {
                            if (JoueurListe[*tour].deck[k].chemintype == CARREFOUR ||  JoueurListe[*tour].deck[k].chemintype == T_HORIZONTAL) {
                                if (cases[i][j].carteaffilie.bas == 1 &&
                                    cases[i + 1][j].utilise == 0) {
                                    cases[i + 1][j].carteaffilie = JoueurListe[*tour].deck[k];
                                    JoueurListe[*tour].deck[k].pioche_deffause_main = 1;
                                    cases[i + 1][j].utilise = 1;
                                    *choix = 0;
                                    *tour = 0;
                                }
                            }
                        }
                    }
                    if (i>0){
                        if (*choix==1) {
                            if (JoueurListe[*tour].deck[k].chemintype == CARREFOUR ||  JoueurListe[*tour].deck[k].chemintype == T_HORIZONTAL) {
                                if (cases[i][j].carteaffilie.haut == 1 &&
                                    cases[i - 1][j].utilise == 0) {
                                    cases[i - 1][j].carteaffilie = JoueurListe[*tour].deck[k];
                                    JoueurListe[*tour].deck[k].pioche_deffause_main = 1;
                                    cases[i - 1][j].utilise = 1;
                                    *choix = 0;
                                    *tour = 0;
                                }
                            }
                        }
                    }
                    if (j<8){
                        if (*choix==1) {
                            if (JoueurListe[*tour].deck[k].chemintype == DROIT ||JoueurListe[*tour].deck[k].chemintype == IMPASSE || JoueurListe[*tour].deck[k].chemintype == T_VERTICAL ) {
                                if (cases[i][j].carteaffilie.droite == 1 &&
                                    cases[i][j + 1].utilise == 0) {
                                    cases[i][j + 1].carteaffilie = JoueurListe[*tour].deck[k];
                                    JoueurListe[*tour].deck[k].pioche_deffause_main = 1;
                                    cases[i][j + 1].utilise = 1;
                                    *choix = 0;
                                    *tour = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

