#include "fonctions.h"
void initialisation() {
    //------------------- Assertion d'installation d'Allegro 5 ----------------//
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_init_image_addon());
    assert(al_install_audio());
    assert(al_init_acodec_addon());
    al_reserve_samples(3);
    al_init_image_addon();
    srand(time(NULL));
    al_reserve_samples(3);

}
void initialisationPlateau(CasePlateau** cases) {
    for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
        cases[i] = calloc(NB_CARTES_HORIZONTALES, sizeof(CasePlateau));
    }
    /*
    for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
        for (int j = 0; j < NB_CARTES_HORIZONTALES; ++j) {
         cases[i][j].carteaffilie=calloc(1,sizeof(carte));
        }
    }
}*/
}
void initialisationZoneJoueurEnAttente(Zone* zoneAttente){
    zoneAttente->positionX = NB_CARTES_HORIZONTALES * LARGEUR_CARTE + 2*ESPACE_ENTRE_ZONES_PLATEAU;
    zoneAttente->positionY = HAUTEUR - (NB_CARTES_VERTICALES * HAUTEUR_CARTE)+1.5*ESPACE_ENTRE_ZONES_PLATEAU;
    zoneAttente->largeur = LARGEUR_ZONE_JOUEUR_ATTENTE;
    zoneAttente->hauteur = HAUTEUR_ZONE_JOUEUR_ATTENTE;
    zoneAttente->fond= al_map_rgba(114,114,114,150);
}
void initialisationZoneJoueurEnCours(Zone *zoneJoueurEnCours) {
    zoneJoueurEnCours->positionX = 10;
    zoneJoueurEnCours->positionY = 10;
    zoneJoueurEnCours->hauteur = HAUTEUR_ZONE_JOUEUR_EN_COURS;
    zoneJoueurEnCours->fond = al_map_rgba(84,84,84,150);
    zoneJoueurEnCours->largeur = LARGEUR_ZONE_JOUEUR_EN_COURS;
}
void InitialisationCartes(carte *cartes) {

    //---------------- Structure ------------------//
    /*
    unsigned char actiontype;          --> Type d'action de la cart
    bool mouvement;                    --> La carte est-elle en mouvement ?
    bool cartefin;                     --> Est-ce une carte de fin ?
    bool action;                       --> Est-ce une carte action ?
    bool chemin;                       --> Est-ce une carte mouvement ?
    bool or;                           --> Est-ce une carte or ?
    bool premiere;                     --> Première carte du jeu
    bool haut;                         --> Carte mouvement : permet-elle d'aller en haut ?
    bool droite;                       --> Carte mouvement : permet-elle d'aller à droite ?
    bool bas                           --> Carte mouvement : permet-elle d'aller en bas ?
    bool gauche;                       --> Carte mouvement : permet-elle d'aller à gauche ?
    short pioche_deffause_main;        --> Position de la carte dans le jeu (pioche, defausse ou main)
    short x;                           -->Position X sur le Bitmap
    short y;                           -->Position Y sur le Bitmap
    bool rotation;                     --> Rotation de la carte (0 ou 180)
    int positionY;                     --> Position X
    int positionX;                     --> Position Y
     */
    //--------------- CARTE D'ACTION ------------------//

    for (int i = 0; i != 24; i++) {
        cartes[i].action = true;
    }
    cartes[0].actiontype = DESTRUCTION_PIOCHE;        // Destruction pioche
    cartes[0].x = 5 * LARGEUR_CARTE;
    cartes[0].y = 3 * HAUTEUR_CARTE;

    cartes[1].actiontype = DESTRUCTION_PIOCHE;        // Destruction pioche
    cartes[1].x = 5 * LARGEUR_CARTE;
    cartes[1].y = 3 * HAUTEUR_CARTE;

    cartes[2].actiontype = DESTRUCTION_LAMPE;         // Destruction lampe
    cartes[2].x = 2 * LARGEUR_CARTE;
    cartes[2].y = 2 * HAUTEUR_CARTE;

    cartes[3].actiontype = DESTRUCTION_LAMPE;         // Destruction lampe
    cartes[3].x = 2 * LARGEUR_CARTE;
    cartes[3].y = 2 * HAUTEUR_CARTE;

    cartes[4].actiontype = DESTRUCTION_MARTEAU_PIQUEUR;   // Destruction marteau piqueur
    cartes[4].x = 0 * LARGEUR_CARTE;
    cartes[4].y = 1 * HAUTEUR_CARTE;

    cartes[5].actiontype = DESTRUCTION_MARTEAU_PIQUEUR;   // Destruction marteau piqueur
    cartes[5].x = 0 * LARGEUR_CARTE;
    cartes[5].y = 1 * HAUTEUR_CARTE;

    cartes[6].actiontype = DESTRUCTION_TOUS_OUTILS;        // Destruction tous les outils
    cartes[6].x = 5 * LARGEUR_CARTE;
    cartes[6].y = 2 * HAUTEUR_CARTE;

    cartes[7].actiontype = DESTRUCTION_TOUS_OUTILS;             // Destruction tous les outils
    cartes[7].x = 5 * LARGEUR_CARTE;
    cartes[7].y = 2 * HAUTEUR_CARTE;

    cartes[8].actiontype = REPARATION_PIOCHE;             // Reparation pioche
    cartes[8].x = 6 * LARGEUR_CARTE;
    cartes[8].y = 3 * HAUTEUR_CARTE;

    cartes[9].actiontype = REPARATION_PIOCHE;            // Réparation pioche
    cartes[9].x = 6 * LARGEUR_CARTE;
    cartes[9].y = 3 * HAUTEUR_CARTE;

    cartes[10].actiontype = REPARATION_LAMPE;             // Réparation lampe
    cartes[10].x = 1 * LARGEUR_CARTE;
    cartes[10].y = 2 * HAUTEUR_CARTE;

    cartes[11].actiontype = REPARATION_LAMPE;             // Réparation lampe
    cartes[11].x = 1 * LARGEUR_CARTE;
    cartes[11].y = 2 * HAUTEUR_CARTE;

    cartes[12].actiontype = REPARATION_MARTEAU_PIQUEUR;   // Réparation marteau
    cartes[12].x = 0 * LARGEUR_CARTE;
    cartes[12].y = 2 * HAUTEUR_CARTE;

    cartes[13].actiontype = REPARATION_MARTEAU_PIQUEUR;   // Réparation marteau
    cartes[13].x = 0 * LARGEUR_CARTE;
    cartes[13].y = 2 * HAUTEUR_CARTE;

    cartes[14].actiontype = REPARATION_MARTEAU_PIQUEUR_LAMPE;     // Réparation marteau-piqueur lampe
    cartes[14].x = 3 * LARGEUR_CARTE;
    cartes[14].y = 2 * HAUTEUR_CARTE;

    cartes[15].actiontype = REPARATION_MARTEAU_PIQUEUR_LAMPE;        // Réparation marteau-piqueur lampe
    cartes[15].x = 3 * LARGEUR_CARTE;
    cartes[15].y = 2 * HAUTEUR_CARTE;

    cartes[16].actiontype = REPARATION_PIOCHE_LAMPE;              // Réparation pioche lampe
    cartes[16].x = 4 * LARGEUR_CARTE;
    cartes[16].y = 2 * HAUTEUR_CARTE;

    cartes[17].actiontype = REPARATION_PIOCHE_LAMPE;            // Réparation pioche lampe
    cartes[17].x = 4 * LARGEUR_CARTE;
    cartes[17].y = 2 * HAUTEUR_CARTE;

    cartes[18].actiontype = REPARATION_MARTEAU_PIQUEUR_PIOCHE;        // Réparation marteau-piqueur pioche
    cartes[18].x = 6 * LARGEUR_CARTE;
    cartes[18].y = 2 * HAUTEUR_CARTE;

    cartes[19].actiontype = REPARATION_MARTEAU_PIQUEUR_PIOCHE;          // Réparation marteau-piqueur pioche
    cartes[19].x = 6 * LARGEUR_CARTE;
    cartes[19].y = 2 * HAUTEUR_CARTE;

    cartes[20].actiontype = EBOULEMENT;
    cartes[20].x = 4 * LARGEUR_CARTE;
    cartes[20].y = 1 * HAUTEUR_CARTE;

    cartes[21].actiontype = EBOULEMENT;        // Eboulement
    cartes[21].x = 4 * LARGEUR_CARTE;
    cartes[21].y = 1 * HAUTEUR_CARTE;

    cartes[22].actiontype = PLAN;              //  Plan
    cartes[22].x = 3 * LARGEUR_CARTE;
    cartes[22].y = 1 * HAUTEUR_CARTE;

    cartes[23].actiontype = PLAN;               // Plan
    cartes[23].x = 3 * LARGEUR_CARTE;
    cartes[23].y = 1 * HAUTEUR_CARTE;

    //---------------------------------- CARTE DE MOUVEMENT  --------------------------------------//

    for (int i = 24; i != 69; i++) {
        cartes[i].chemin = true;
        cartes[i].actiontype=27;
    }
    for (int i = 24; i < 33; i++) {   // Carte[25]->carte[34] carte chemin
        cartes[i].x = 0 * LARGEUR_CARTE;
        cartes[i].y = 0 * HAUTEUR_CARTE;
        cartes[i].gauche = true;
        cartes[i].droite = true;
        cartes[i].chemintype =DROIT;

    }
    for (int i = 33; i < 42; i++) {   // Carte[34]->carte[42] carte T vertical
        cartes[i].x = 1 * LARGEUR_CARTE;
        cartes[i].y = 0 * HAUTEUR_CARTE;
        cartes[i].gauche = true;
        cartes[i].droite = true;
        cartes[i].haut = true;
        cartes[i].chemintype=T_VERTICAL;
    }
    for (int i = 42; i < 51; i++) {   // Carte[43]->carte[51] carte T horizontal
        cartes[i].x = 2 * LARGEUR_CARTE;
        cartes[i].y = 0 * HAUTEUR_CARTE;
        cartes[i].bas = true;
        cartes[i].droite = true;
        cartes[i].haut = true;
        cartes[i].chemintype=T_HORIZONTAL;
    }
    for (int i = 51; i < 60; i++) {   // Carte[52]->carte[60] carte carrefour
        cartes[i].x = 3 * LARGEUR_CARTE;
        cartes[i].y = 0 * HAUTEUR_CARTE;
        cartes[i].bas = true;
        cartes[i].droite = true;
        cartes[i].haut = true;
        cartes[i].gauche = true;
        cartes[i].chemintype=CARREFOUR;

    }
    for (int i = 60; i < 69; i++) {   //carte[61]->carte[69] carte impasse
        cartes[i].x = 4 * LARGEUR_CARTE;
        cartes[i].y = 0 * HAUTEUR_CARTE;
        cartes[i].gauche = true;
        cartes[i].chemintype=IMPASSE;
    }

    //--------------------------------------- CARTE D'OBJECTIF  ------------------------------------//

    cartes[69].cartefin = true;
    cartes[69].or = true;
    cartes[69].bas = true;
    cartes[69].droite = true;
    cartes[69].haut = true;
    cartes[69].gauche = true;
    cartes[69].x = 5 * LARGEUR_CARTE;
    cartes[69].y = 1 * HAUTEUR_CARTE;
    cartes[69].pioche_deffause_main=3;

    cartes[70].cartefin = true;
    cartes[70].gauche = true;
    cartes[70].bas = true;
    cartes[70].x = 5 * LARGEUR_CARTE;
    cartes[70].y = 0 * HAUTEUR_CARTE;

    cartes[71].cartefin = true;
    cartes[71].gauche = true;
    cartes[71].haut = true;
    cartes[71].x = 6 * LARGEUR_CARTE;
    cartes[71].y = 1 * HAUTEUR_CARTE;

    cartes[72].premiere = true;
    cartes[72].bas = true;
    cartes[72].droite = true;
    cartes[72].haut = true;
    cartes[72].gauche = true;
    cartes[72].x = 1 * LARGEUR_CARTE;
    cartes[72].y = 1 * HAUTEUR_CARTE;
}
