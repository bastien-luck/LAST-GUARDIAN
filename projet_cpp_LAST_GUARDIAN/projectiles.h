#ifndef projectiles_h
#define projectiles_h

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtMath>
#include "explosion.h"

using namespace std ;

/**
 * @brief The Projectiles class define all the projectiles available in the game
 */
class Projectiles : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    //variables
private :
    QGraphicsScene *scene ;
    int id_balle ;
    int degat ;
    int dot ;
    int hauteur_sprite_projectile ;
    int largeur_sprite_projectile ;
    int hauteur_hitbox_projectile ;
    int largeur_hitbox_projectile ;
    int declage_x_hitbox_et_sprite_projectile ;
    int declage_y_hitbox_et_sprite_projectile ;
    bool penetration ;
    qreal vitesse ;
    qreal angle ;
    qreal rayon_explosion ;
    QString sprite_projectile ;

    // méthodes
public :
    void move_projectile() ;
    int get_hauteur_balle() ;
    int get_largeur_balle() ;
    int get_hauteur_hitbox_balle() ;
    int get_largeur_hitbox_balle() ;
    int get_decalage_x_hitbox_et_sprites_balle() ;
    int get_decalage_y_hitbox_et_sprites_balle() ;
    int get_degat() ;
    int get_degat_poison() ;
    bool transperce() ;
    qreal get_aoe() ;
    Explosion *explose() ;

    // constructeurs / destructeurs
public :
    Projectiles( QGraphicsScene *scene , qreal y , int id_balle , int dmg , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , QString nom_image , qreal speed , int angle_balle , bool pierce = false , int dot = 0 ,  qreal aoe = 0 , int amelioration_degat = 0 ) ;
    ~Projectiles()
    {
        this->scene->removeItem( this ) ;
    }
} ;

#endif // projectiles_h
