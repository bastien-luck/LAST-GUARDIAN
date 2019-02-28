#ifndef projectile_lourd_h
#define projectile_lourd_h

#include "projectiles.h"

/**
 * @brief The Projectile_lourd class define the stats of the ammo called "lourd"
 */
class Projectile_lourd : public Projectiles
{
    Q_OBJECT
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Projectile_lourd( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) ;
    ~Projectile_lourd(){}
} ;

#endif // projectile_lourd_h
