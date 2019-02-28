#ifndef explosion_h
#define explosion_h

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

using namespace std ;

/**
 * @brief The Explosion class define how work explosion visual effect
 */
class Explosion : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    //variables
private :
    QGraphicsScene *scene ;
    int hauteur_sprite_explosion ;
    int largeur_sprite_explosion ;
    int hauteur_hitbox_explosion ;
    int largeur_hitbox_explosion ;
    int declage_x_hitbox_et_sprite_explosion ;
    int declage_y_hitbox_et_sprite_explosion ;
    QString sprite_explosion ;
    int nombre_sprite ;
    int numero_sprite_actuel ;

    // méthodes
public :
    bool explosion_en_cours() ;
    int get_largeur_hitbox_bombe() ;
    int get_hauteur_hitbox_bombe() ;
    int get_decalage_x_hitbox_et_sprites_bombe() ;
    int get_decalage_y_hitbox_et_sprites_bombe() ;

    // constructeurs / destructeurs
public :
    Explosion( QGraphicsScene *scene , qreal x , qreal y , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , QString nom_image , int nombre_sprite_explosion ) ;
    ~Explosion()
    {
        this->scene->removeItem( this ) ;
    }
} ;

#endif // explosion_h
