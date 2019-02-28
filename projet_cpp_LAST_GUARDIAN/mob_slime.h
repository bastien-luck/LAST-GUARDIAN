#ifndef mob_slime_h
#define mob_slime_h

#include <iostream>
#include "ennemis.h"

using namespace std ;

/**
 * @brief The Mob_slime class define how act the mob called "slime"
 */
class Mob_slime : public Ennemis
{
    Q_OBJECT
    // variables
private :


    // méthodes
public :


    // constructeurs / destructeurs
public :
    Mob_slime( QGraphicsScene *scene , int summon_pos_x = 0 , int summon_pos_y = 0 ) ;
    ~Mob_slime(){}
} ;

#endif // mob_slime_h
