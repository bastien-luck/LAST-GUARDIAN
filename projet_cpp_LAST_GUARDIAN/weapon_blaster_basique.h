#ifndef weapon_blaster_basique_h
#define weapon_blaster_basique_h

#include "armes.h"

/**
 * @brief The Weapon_blaster_basique class define the caracteristics of the weapon called "blaster basique"
 */
class Weapon_blaster_basique : public Armes
{
    // variables
private :

    // méthodes
public :

    // constructeurs / destructeurs
public :
    Weapon_blaster_basique( QGraphicsScene *scene ) ;
    ~Weapon_blaster_basique(){}
} ;

#endif // weapon_blaster_basique_h
