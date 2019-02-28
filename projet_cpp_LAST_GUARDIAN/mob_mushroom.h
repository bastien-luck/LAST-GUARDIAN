#ifndef mob_mushroom_h
#define mob_mushroom_h

#include "ennemis.h"

/**
 * @brief The Mob_mushroom class define how act the mob called "mushroom"
 */
class Mob_mushroom : public Ennemis
{
    Q_OBJECT
    // variables
private :


    // méthodes
public :


    // constructeurs / destructeurs
public :
    Mob_mushroom( QGraphicsScene *scene , int summon_pos_x = 0 , int summon_pos_y = 0 ) ;
    ~Mob_mushroom(){}
} ;

#endif // mob_mushroom_h
