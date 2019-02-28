#ifndef projectile_explosif_h
#define projectile_explosif_h

#include "projectiles.h"

/**
 * @brief The Projectile_explosif class define the stats of the ammo called "explosif"
 */
class Projectile_explosif : public Projectiles
{
    Q_OBJECT
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Projectile_explosif( QGraphicsScene *scene , qreal pos_y , int angle , int amelioration_degat ) ;
    ~Projectile_explosif(){}
} ;

#endif // projectile_explosif_h
