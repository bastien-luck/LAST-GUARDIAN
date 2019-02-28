#ifndef frame_h
#define frame_h

#include <iostream>
#include <QObject>
#include <QVector>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "gestion_input.h"
#include "guardian.h"
#include "niveau.h"
#include "fonction_globale.h"
#include "base.h"
#include "gui.h"
#include "gestion_son.h"
#include "explosion.h"

using namespace std ;

/**
 * @brief The Frame class define how is working the game with all its asset together
 */
class Frame : public QObject
{
    Q_OBJECT
    // variables
public :
    QGraphicsScene *scene ;
    QGraphicsView *view  ;
    static const int largeur_ecran = 1350 ;
    static const int hauteur_ecran = 714 ;
    static const int hauteur_spawn_min = 210 ;
    static const int hauteur_spawn_max = 594 ;
    QTime dieTime ;
    Gestion_input * keylistener ;
    int endroit_actuel ; // 0 : close game , 1 : menu demarrage , 2 : en combat , 3 : écran victoire , 4 : écran défaite, 5 : écran upgrade, 6 : écran crédit
    Guardian *joueur ;
    QVector<Projectiles*> *projectiles_presents ;
    Niveau *niveau_actuel ;
    int numero_ennemi_spawned ;
    int nombre_ennemi_mort ;
    int attente_prochain_spawn ;
    Base *bunker ;
    Gui *interface_graphique ;
    bool items_deja_present ; // permet de ne pas recharger plusieurs fois les objets uniques sans faire une méthode "compliqué"
    bool pause ;
    Gestion_son *jukebox ;
    bool option ;
    int nb_image_dans_scene_sans_le_menu_option ;
    int nb_texte_dans_scene_sans_le_menu_option ;
    int numero_niveau_actuel ;
    QVector<Explosion*> *explosions_presentes ;
    bool tir_automatique ;
    int arme_upgrade_show ;

    // méthodes
public :
    void change_endroit_actuel( int endroit_suivant ) ;
    void start_screen() ;
    void play() ;
    void loosing_screen() ;
    void winning_screen() ;
    void menu_option() ;
    void upgrade_screen() ;
    void credit_screen() ;

    // constructeurs / destructeurs
public :
    Frame() ;
    ~Frame(){}
} ;

#endif // frame_h
