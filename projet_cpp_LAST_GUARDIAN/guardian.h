#ifndef guardian_h
#define guardian_h

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "armes.h"

using namespace std ;

/**
 * @brief The Guardian class define the player with his items
 */
class Guardian : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    // variables
private :
    QGraphicsScene *scene ;
    int hauteur_sprite_guardian ;
    int largeur_sprite_guardian ;
    int vitesse ;
    QVector<Armes*> *armes_possede ;
    Armes *arme_equipe ;
    QString sprite_guardian ;

    // méthodes
public :
    Armes *get_arme_equipe() ;
    int get_hauteur_sprite_guardian() ;
    void move_up() ;
    void move_down() ;
    void fabrique_arme( int id_new_arme ) ;
    void change_arme_equipe( int id_arme_choisie ) ;
    int get_nb_armes_possede() ;

    // constructeurs / destructeurs
public :
    Guardian( QGraphicsScene *scene ) ;
    ~Guardian(){}
} ;

#endif // guardian_h
