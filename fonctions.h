#ifndef SABOTEUR_FONCTIONS_H
#define SABOTEUR_FONCTIONS_H

//------------------------- Includes ------------------------//

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//------------------------- Macros --------------------------//

#define LARGEUR 1366
#define HAUTEUR 768
#define NBCARTES_PIOCHE 68
#define NBCARTES 73
#define PSEUDOMAX 10
#define JOUEUR_MAX 4
#define DECK_MAX 6
#define HAUTEUR_CARTE 120
#define LARGEUR_CARTE 80
#define NB_CARTES_VERTICALES 5
#define NB_CARTES_HORIZONTALES 9
#define HAUTEUR_LARGEUR_BONUS_MALUS 60
#define LARGEUR_ZONE_JOUEUR_ATTENTE 620
#define HAUTEUR_ZONE_JOUEUR_ATTENTE 137
#define LARGEUR_ZONE_JOUEUR_EN_COURS 370
#define HAUTEUR_ZONE_JOUEUR_EN_COURS 134
#define ESPACE_ENTRE_ZONES_PLATEAU 10
#define POSITION_DEBUT_PLATEAU 168

//-------------------------- Enum -----------------------//


enum {
    NUL,
    EBOULEMENT,
    REPARATION_MARTEAU_PIQUEUR,
    REPARATION_LAMPE,
    REPARATION_PIOCHE,
    REPARATION_MARTEAU_PIQUEUR_LAMPE,
    REPARATION_PIOCHE_LAMPE,
    REPARATION_MARTEAU_PIQUEUR_PIOCHE,
    DESTRUCTION_TOUS_OUTILS,
    DESTRUCTION_MARTEAU_PIQUEUR,
    DESTRUCTION_PIOCHE,
    DESTRUCTION_LAMPE,
    PLAN
};
enum{
    NUL2,
    DROIT,
    T_VERTICAL,
    T_HORIZONTAL,
    CARREFOUR,
    IMPASSE
};

//-------------------------- Structure -----------------------/

typedef struct {
    unsigned char actiontype; //
    unsigned char chemintype;
    bool mouvement;
    bool cartefin;
    bool action;
    bool chemin;
    bool or;
    bool premiere;
    bool haut;
    bool droite;
    bool bas;
    bool gauche;
    short pioche_deffause_main;
    short x;
    short y;
    bool rotation;
    int positionY;
    int positionX;
} carte;


typedef struct {
    short logox;
    short logoy;
    char pseudo[PSEUDOMAX];
    short numeroLettre;
    short nbCartesDansDeck;
    short score;
    bool role;
   carte deck[DECK_MAX];
    int lampe;
    int pioche;
    int marteau;
    bool plan;
} joueur;

typedef struct {
    short positionX, positionY;
    short largeur, hauteur;
    struct ALLEGRO_COLOR fond;
} Zone;

typedef struct{
    short positionX1,positionY1;
    ALLEGRO_COLOR couleurFond;
    bool utilise;
    carte carteaffilie;
    bool possible;
} CasePlateau;

typedef struct {
    short valeur;
    bool croissance;
}degrade;

//------------------ INITIALISATION ------------------------//
void initialisation();
void InitialisationCartes (carte* cartes);
void initialisationPlateau(CasePlateau** cases);
void initialisationZoneJoueurEnAttente(Zone* zoneAttente);
void initialisationZoneJoueurEnCours(Zone *zoneJoueurEnCours);

//---------------------- MENU -----------------------------//
void saisirPseudo(bool pseudo_joueur[4], bool clic, joueur *JoueurListe, int keycode, short *menu);
void Menu(ALLEGRO_MOUSE_STATE etat_souris, short *menu, short *NbJoueur, bool clic, ALLEGRO_FONT *policeMenu65,
          ALLEGRO_FONT *policeMenu35, ALLEGRO_FONT *policePause120, ALLEGRO_FONT *policeTitre80, bool *pseudo_joueur,
          joueur *JoueurListe, ALLEGRO_BITMAP *ensemblecartes, short *ordre, carte cartes[], short *NbCartesPioche,
          CasePlateau **cases, bool *Fin, bool *aideenjeu, ALLEGRO_SAMPLE *sonclick,
          degrade *degrades, short *tour, bool clicdroit, bool possibilitebool, bool possibiliteEboulement,
          Zone *zoneAttente, Zone *zoneJoueurEnCours, ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP *fondplateau);
void Menu0(ALLEGRO_FONT* policeTitre80,ALLEGRO_FONT* policeMenu35,degrade* degrades,bool clic,short* menu);
void Menu1(bool* aideenjeu,ALLEGRO_MOUSE_STATE etat_souris,ALLEGRO_FONT* policeMenu65,bool clic,short* menu,ALLEGRO_SAMPLE* sonclick);
void Menu2(ALLEGRO_MOUSE_STATE etat_souris,ALLEGRO_FONT* policeMenu65,bool clic,short* menu,ALLEGRO_SAMPLE* sonclick,joueur* JoueurListe, short *NbJoueur,carte* cartes, short* NbCartesPioche,CasePlateau** cases);
void Menu3(bool* aideenjeu,short NbJoueur,ALLEGRO_MOUSE_STATE etat_souris,ALLEGRO_FONT* policeMenu65,bool clic,short* menu,ALLEGRO_SAMPLE* sonclick,bool* pseudo_joueur,joueur* JoueurListe,ALLEGRO_FONT*policeMenu35);
void Menu4(short *ordre, short *NbJoueur,joueur* JoueurListe,ALLEGRO_BITMAP* ensemblecartes, ALLEGRO_FONT* policeMenu65, ALLEGRO_FONT* policeMenu35,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE *sonclick,short* menu,short* NbCartesPioche,carte *cartes);
void Menu6(ALLEGRO_FONT* policeMenu65,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE* sonclick,bool* Fin);
void Menu7(ALLEGRO_FONT* policeMenu65,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE* sonclick,bool* Fin);
void Aide0(bool aideenjeu,ALLEGRO_MOUSE_STATE etat_souris,bool clic, short* menu,ALLEGRO_FONT* policeMenu35,ALLEGRO_SAMPLE* sonclick);
void Aide1(bool aideenjeu,ALLEGRO_MOUSE_STATE etat_souris,bool clic, short* menu,ALLEGRO_FONT* policeMenu35,ALLEGRO_SAMPLE* sonclick);
void Aide2(bool aideenjeu,ALLEGRO_MOUSE_STATE etat_souris,bool clic, short* menu,ALLEGRO_FONT* policeMenu35,ALLEGRO_SAMPLE* sonclick);
void MenuEchape0(ALLEGRO_MOUSE_STATE etat_souris,bool clic, short* menu,ALLEGRO_FONT* policeMenu35,ALLEGRO_FONT* policePause120,ALLEGRO_SAMPLE* sonclick);
void MenuEchape1(ALLEGRO_MOUSE_STATE etat_souris,bool clic, short* menu,ALLEGRO_FONT* policeMenu35,ALLEGRO_FONT* policePause120,ALLEGRO_SAMPLE* sonclick,bool* Fin);
void ChargerPartie(ALLEGRO_MOUSE_STATE etat_souris, bool clic, short *menu, ALLEGRO_FONT *policeMenu35,ALLEGRO_SAMPLE *sonclick);
void fondudegrade(degrade* degrades);

//----------------SOURIS----------------------//
void sourisUp(short menu, CasePlateau **cases, joueur *JoueurListe, short tour, ALLEGRO_EVENT event,
             ALLEGRO_MOUSE_STATE etat_souris, bool *possibilitebool, bool *possibiliteEboulement,short NbJoueur,Zone* zoneAttente,carte* CarteListe,short* NbCartesPioche,bool* clic,bool* clicdroit);
void sourisDown(short menu, CasePlateau **cases, joueur *JoueurListe, short tour, ALLEGRO_EVENT event,
                ALLEGRO_MOUSE_STATE etat_souris, bool *possibilitebool, bool *possibiliteEboulement);

//---------------PLATEAU------------------------//
void preparationJeu(joueur* JoueurListe, short NbJoueur,carte* cartes, short* NbCartesPioche,CasePlateau** cases);
void dessinFondTableauCartes(CasePlateau** cases,ALLEGRO_BITMAP *ensemblecartes, bool boolpossibilite, bool possibiliteEboulement) ;
void dessinZoneJoueurEnAttente(joueur *unJoueur, Zone* zoneAttente, short Nbjoueur, ALLEGRO_FONT* policeMenu35,  ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP* ensemblecartes);
void dessinZoneJoueurEnCours(joueur *JoueurListe, Zone *zoneJoueurEnCours, ALLEGRO_FONT* policeMenu,short tour, ALLEGRO_FONT *policeGrasPlateau35, ALLEGRO_BITMAP* ensemblecartes);
//---------MVT-CARTE-------------//
void mouvementCartes(ALLEGRO_MOUSE_STATE etat_souris,ALLEGRO_BITMAP *ensemblecartes,joueur* JoueurListe,short tour);
void poseCartesurPlateau(joueur* JoueurListe, short *tour, CasePlateau** cases, short Nbjoueur);
void poseBonusMalus(joueur *JoueurListe, short *tour, Zone *zoneAttente, short Nbjoueur);

//------------CARTE--------------//
void dessinCartes(joueur *joueurQuiPioche,ALLEGRO_BITMAP *ensemblecartes,short tour,ALLEGRO_MOUSE_STATE etat_souris,bool clic);

//------------------ PIOCHE ------------------------//
void piocher(joueur *joueurQuiPioche, carte* cartes, short *NbCartesPioche,short i);
void deffause(joueur* JoueurListe,short tour,carte* cartes,short* NbCartesPioche);

//------------------ ROLE ------------------------//
void affichageRole(joueur* JoueurListe,ALLEGRO_BITMAP* ensemblecartes,short* j, ALLEGRO_FONT* policeMenu65, ALLEGRO_FONT* policeMenu35,ALLEGRO_MOUSE_STATE etat_souris,bool clic,ALLEGRO_SAMPLE *sonclick);

//-------------------UTILITAIRE--------------------//
void rotation(carte *carte1);
short bouton(ALLEGRO_MOUSE_STATE mouse, int x, int y, int l, int h, ALLEGRO_COLOR cb1,
             ALLEGRO_COLOR cb2, short a, ALLEGRO_FONT *police, int ht, char *texte, ALLEGRO_COLOR ct, bool clic);
void possibilite(CasePlateau** cases,joueur* JoueurListe,short tour);
void passerletour( short* tour,short Nbjoueur,ALLEGRO_MOUSE_STATE etat_souris,ALLEGRO_FONT* policemenu,bool clic);

//--------------------IA-------------------//
void jouerCarteaction(joueur *JoueurListe, short *tour,bool* choix);
void jouerCartechemin(joueur *JoueurListe, short* tour, CasePlateau **cases,bool* choix);
//------------------ LIBERATION ------------------------//
void liberation(Zone *zoneJoueurEnCours, carte *CarteListe, Zone *zoneAttente, joueur *JoueurListe, CasePlateau **cases,
                ALLEGRO_BITMAP *fondmenu, ALLEGRO_BITMAP *fondplateau, ALLEGRO_BITMAP *ensemblecartes, ALLEGRO_DISPLAY *fenetre,
                ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_FONT *policeMenu35, ALLEGRO_FONT *policePause120,
                ALLEGRO_FONT *policeMenu65, ALLEGRO_SAMPLE *musiquefond, ALLEGRO_SAMPLE *sonclick,ALLEGRO_BITMAP* fondtitre);

#endif //SABOTEUR_FONCTIONS_H
