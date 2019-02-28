#ifndef mob_skeleton_h
#define mob_skeleton_h

#include <iostream>
#include "ennemis.h"

using namespace std ;

/**
 * @brief The Mob_skeleton class define how act the mob called "skeleton"
 */
class Mob_skeleton : public Ennemis
{
    Q_OBJECT
    // variables
private :


    // méthodes
public :


    // constructeurs / destructeurs
public :
    Mob_skeleton( QGraphicsScene *scene , int summon_pos_x = 0 , int summon_pos_y = 0 ) ;
    ~Mob_skeleton(){}
} ;

#endif // mob_skeleton_h
