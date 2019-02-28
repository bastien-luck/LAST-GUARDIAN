#ifndef projectile_basique_h
#define projectile_basique_h

#include "projectiles.h"

/**
 * @brief The Projectile_basique class define the stats of the ammo called "basique"
 */
class Projectile_basique : public Projectiles
{
    Q_OBJECT
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Projectile_basique( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) ;
    ~Projectile_basique(){}
} ;

#endif // projectile_basique_h
