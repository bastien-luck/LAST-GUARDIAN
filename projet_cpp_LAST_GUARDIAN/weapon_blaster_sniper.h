#ifndef weapon_blaster_sniper_h
#define weapon_blaster_sniper_h

#include "armes.h"

/**
 * @brief The Weapon_blaster_sniper class define the caracteristics of the weapon called "blaster sniper"
 */
class Weapon_blaster_sniper : public Armes
{
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Weapon_blaster_sniper( QGraphicsScene *scene ) ;
    ~Weapon_blaster_sniper(){}
} ;

#endif // weapon_blaster_sniper_h
