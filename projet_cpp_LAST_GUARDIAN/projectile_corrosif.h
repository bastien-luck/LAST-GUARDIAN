#ifndef projectile_corrosif_h
#define projectile_corrosif_h

#include "projectiles.h"

/**
 * @brief The Projectile_corrosif class define the stats of the ammo called "corrosif"
 */
class Projectile_corrosif : public Projectiles
{
    Q_OBJECT
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public:
    Projectile_corrosif( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) ;
    ~Projectile_corrosif(){}
} ;

#endif // projectile_corrosif_h
