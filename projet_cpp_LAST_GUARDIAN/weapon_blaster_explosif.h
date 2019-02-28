#ifndef weapon_blaster_explosif_h
#define weapon_blaster_explosif_h

#include "armes.h"

/**
 * @brief The Weapon_blaster_explosif class define the caracteristics of the weapon called "blaster explosif"
 */
class Weapon_blaster_explosif : public Armes
{
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Weapon_blaster_explosif( QGraphicsScene *scene ) ;
    ~Weapon_blaster_explosif(){}
} ;

#endif // weapon_blaster_explosif_h
