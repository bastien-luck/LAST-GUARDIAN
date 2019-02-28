#ifndef weapon_blaster_minigun_h
#define weapon_blaster_minigun_h

#include "armes.h"

/**
 * @brief The Weapon_blaster_minigun class define the caracteristics of the weapon called "blaster minigun"
 */
class Weapon_blaster_minigun : public Armes
{
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Weapon_blaster_minigun( QGraphicsScene *scene ) ;
    ~Weapon_blaster_minigun(){}
} ;

#endif // weapon_blaster_minigun_h
