#ifndef barre_de_vie_h
#define barre_de_vie_h

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

using namespace std ;

/**
 * @brief The Barre_de_vie class define the visible hp bar of every Ennemis
 */
class Barre_de_vie
{
    // variables
private :
    QGraphicsScene *scene ;
    QGraphicsPixmapItem *barre_pv_supp ;
    QGraphicsPixmapItem *barre_pv_actuel ;
    int largeur_barre_pv ;
    int hauteur_barre_pv ;

    // méthodes
public :
    QGraphicsPixmapItem *get_barre_supp() ;
    QGraphicsPixmapItem *get_barre_actuel() ;
    void perte_pv( qreal pourcent_pv_restant , bool empoisonner , bool more_hp_barre_to_display = false ) ;
    void move_hp( qreal vitesse_mob ) ;

    // constructeurs / destructeurs
public:
    Barre_de_vie( QGraphicsScene *scene , qreal pos_x , qreal pos_y , int largeur_barre ) ; // barre de vie des ennemis normaux
    Barre_de_vie( QGraphicsScene *scene ) ; // barre de vie des boss
    ~Barre_de_vie()
    {
        delete this->barre_pv_supp ;
        delete this->barre_pv_actuel ;
    }
} ;

#endif // barre_de_vie_h
