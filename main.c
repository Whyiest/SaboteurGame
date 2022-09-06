#include "fonctions.h"

int main() {

    //---------------------------- Initialisation -------------------------//

    initialisation();
    al_set_new_display_flags(ALLEGRO_WINDOWED);//Permet d'avoir le jeu en fenetree
    ALLEGRO_DISPLAY *fenetre = al_create_display(LARGEUR, HAUTEUR); //Creation de la fenêtre
    ALLEGRO_MOUSE_STATE etat_souris; // Initialisation du peripherique: souris
    ALLEGRO_KEYBOARD_STATE etat_clavier;// Initialisation du peripherique: clavier
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 24.0);// 24 raffraichissement par seconde
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

    //Initialisation police
    ALLEGRO_FONT *policeMenu65 = al_load_ttf_font("../fonts/Montserrat-Regular.ttf", 65, 0);
    ALLEGRO_FONT *policeMenu35 = al_load_ttf_font("../fonts/Montserrat-Regular.ttf", 35, 0);
    ALLEGRO_FONT *policeGrasPlateau35 = al_load_ttf_font("../fonts/Montserrat-Bold.ttf", 35, 0);
    ALLEGRO_FONT *policePause120 = al_load_ttf_font("../fonts/Bungee-Regular.ttf", 120, 0);
    ALLEGRO_FONT *policeTitre80 = al_load_ttf_font("../fonts/Inversionz.ttf", 100, 0);

    //Initialisation Bitmap
    ALLEGRO_BITMAP *fondplateau = al_load_bitmap("../image/fondplateau.jpg");//1er fond d'ecran
    ALLEGRO_BITMAP *fondtitre = al_load_bitmap("../image/fondtitre.jpg");//2eme fond d'ecran
    ALLEGRO_BITMAP *ensemblecartes = al_load_bitmap("../image/bitmapreelfinal.png");// Correspond aux textures des cartes

    //Initialisation Effets sonores
    ALLEGRO_SAMPLE *musiquefond = al_load_sample("../son/musiquefond.wav");
    ALLEGRO_SAMPLE *sonclick = al_load_sample("../son/sonclick.wav");

    //Variable (hors ALLEGRO)
    short NbJoueur; // Correspond aux nombres de Joueurs
    short menu = 0;// Permet de naviguer entre les differents Menu
    short ordre = 0;// Sert dans la distribution des roles
    short NbCartesPioche = NBCARTES_PIOCHE; // Taille logique de la pioche
    short tour = 0; // Permet de determiner qui joue


    bool clic = false; //Eviter les doubles clique (gauche)
    bool clicdroit = false;//Eviter les doubles clique (droit)
    bool pseudo_joueur[JOUEUR_MAX] = {0, 0, 0, 0};//Utile dans l'attribution de pseudo
    bool aideenjeu = true; // Permet de savoir depuis quel menu l'aide est appelée
    bool possibilitebool = false;//Permet d'afficher les cases vertes au moment ou la carte est en mouvement (cartes chemins)
    bool possibiliteEboulement = false;//Permet d'afficher les cases vertes au moment ou la carte est en mouvement (cartes eboulements)
    bool fin = false;// Permet de finir le programme

    degrade degrades = {60, true}; //Structure pour un effet degrade (menu0)
    //Allocation dynamique
    joueur *JoueurListe = calloc(JOUEUR_MAX, sizeof(joueur));//Liste des joueurs de la partie
    carte *CarteListe = calloc(NBCARTES, sizeof(carte));// La pioche
    CasePlateau **cases = calloc(NB_CARTES_VERTICALES, sizeof(CasePlateau *));// Tableau des cases du plateau
    Zone *zoneAttente = calloc(1, sizeof(Zone));//Correspond aux zones d'interactions avec les autres joueurs
    Zone *zoneJoueurEnCours = calloc(1, sizeof(Zone));//Correspond a l'affichage des donnees du joueur en cours

    //Initialisation fenetre
    al_set_window_title(fenetre, "UnderGround");
    al_set_window_position(fenetre, 0, 0);

    //Inititalisation des valeurs dans les structures
    initialisationZoneJoueurEnAttente(zoneAttente);
    initialisationPlateau(cases);
    InitialisationCartes(CarteListe);
    initialisationZoneJoueurEnCours(zoneJoueurEnCours);

    //Recuperation des sources d'evenements
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //Lancement de la musique
    al_reserve_samples(2);
    al_play_sample(musiquefond, 1, (float) 0.0, (float) 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

    assert(queue != NULL);
    assert(fenetre != NULL);
    assert(musiquefond != NULL);
    assert(sonclick != NULL);

    //----------------------------- Début programme --------------------------//

    while (!fin) {

        ALLEGRO_EVENT event = {0};
        al_start_timer(timer);
        al_wait_for_event(queue, &event);
        al_get_mouse_state(&etat_souris);
        al_get_keyboard_state(&etat_clavier);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if ((event.mouse.button & 2) == 0) {
                        if (menu == 5 || menu == 8) {
                            if (etat_souris.x > 0 && etat_souris.x < 1368) {
                                poseCartesurPlateau(JoueurListe, &tour, cases, NbJoueur);
                                poseBonusMalus(JoueurListe, &tour, zoneAttente, NbJoueur);
                                deffause(JoueurListe, tour, CarteListe, &NbCartesPioche);
                            }
                            for (int a = 0; a < JOUEUR_MAX; ++a) {
                                for (int i = 0; i < NBCARTES; ++i) {
                                    JoueurListe[a].deck[i].mouvement = 0;
                                }
                            }
                            possibilitebool = false;
                            possibiliteEboulement = false;
                        }
                        clic = true;
                    }
                    if ((event.mouse.button & 1) == 0) {
                        clicdroit = true;
                    }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if ((event.mouse.button & 1) == 1) {
                        if (menu == 5 || menu == 8) {
                            for (int i = 0; i < JoueurListe[tour].nbCartesDansDeck; ++i) {
                                if (etat_souris.x > JoueurListe[tour].deck[i].positionX &&
                                    etat_souris.x < JoueurListe[tour].deck[i].positionX + LARGEUR_CARTE - 10 &&
                                    etat_souris.y > 30 &&
                                    etat_souris.y < 30 + HAUTEUR_CARTE) {

                                    JoueurListe[tour].deck[i].mouvement = 1;

                                    if (JoueurListe[tour].deck[i].chemin) {
                                        possibilitebool = true;
                                    }
                                    if (JoueurListe[tour].deck[i].actiontype == EBOULEMENT) {
                                        possibiliteEboulement = true;
                                    }
                                }
                            }
                            for (int i = 0; i < NB_CARTES_VERTICALES; ++i) {
                                for (int k = 0; k < NB_CARTES_HORIZONTALES; ++k) {
                                    cases[i][k].possible = 0;
                                }
                            }
                        }
                    }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    if (menu == 5 || menu==8) {
                        menu = 50;
                    }
                }
                switch (menu) {
                    case 0:
                        menu = 1;
                        break;
                    case 3:
                        saisirPseudo(pseudo_joueur, clic, JoueurListe, event.keyboard.keycode, &menu);
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                al_draw_bitmap(fondtitre, 0, 0, 0);
                Menu(etat_souris, &menu, &NbJoueur, clic, policeMenu65, policeMenu35, policePause120, policeTitre80,
                     pseudo_joueur,
                     JoueurListe, ensemblecartes, &ordre, CarteListe, &NbCartesPioche, cases, &fin, &aideenjeu,
                     sonclick, &degrades, &tour, clicdroit, possibilitebool, possibiliteEboulement,
                     zoneAttente, zoneJoueurEnCours, policeGrasPlateau35, fondplateau);
                clic = false;
                clicdroit = false;
                al_flip_display();
                break;
        }

    }

    //------------------------------------------- Fin du jeu --------------------------------------//

    liberation(zoneJoueurEnCours, CarteListe, zoneAttente, JoueurListe, cases,
               fondtitre, fondplateau, ensemblecartes, fenetre,
               queue, timer, policeMenu35, policePause120, policeMenu65, musiquefond, sonclick, fondtitre);
    return 0;
}