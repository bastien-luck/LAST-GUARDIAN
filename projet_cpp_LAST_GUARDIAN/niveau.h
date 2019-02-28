#ifndef niveau_h
#define niveau_h

#include <iostream>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include "ennemis.h"

using namespace std ;

/**
 * @brief The Niveau class define the current level that the player is playing
 */
class Niveau
{
    // variables
private :
    int numero_niveau ;
    int delais_spawn ; // spawn rate du niveau ( != delais dans ennemis )
    QVector<Ennemis*> *spawn_ennemi ;
    QVector<int> *spawn_order ;

    // méthodes
public :
    bool niveau_terminer() ;
    QVector<Ennemis*> *get_spawn_ennemi() ;
    int get_delais_spawn() ;
    QVector<int> *get_spawn_order() ;

    // constructeurs / destructeurs
public :
    Niveau( int level ) ;
    ~Niveau()
    {
        for ( QVector<Ennemis*>::iterator ennemi_still_alive = this->spawn_ennemi->begin() ; ennemi_still_alive != this->spawn_ennemi->end() ; ++ennemi_still_alive )
        {
            delete (*ennemi_still_alive) ;
            (*ennemi_still_alive) = nullptr ;
            ennemi_still_alive = this->spawn_ennemi->erase( ennemi_still_alive ) ;
            --ennemi_still_alive ;
        }
        delete this->spawn_ennemi ;
        this->spawn_ennemi = nullptr ;
        delete this->spawn_order ;
        this->spawn_order = nullptr ;
    }
} ;

#endif // niveau_h
