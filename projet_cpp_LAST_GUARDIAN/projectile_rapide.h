#ifndef projectile_rapide_h
#define projectile_rapide_h

#include "projectiles.h"

/**
 * @brief The Projectile_rapide class define the stats of the ammo called "rapide"
 */
class Projectile_rapide : public Projectiles
{
    Q_OBJECT
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Projectile_rapide( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) ;
    ~Projectile_rapide(){}
} ;

#endif // projectile_rapide_h
