#ifndef base_h
#define base_h

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

using namespace std ;

/**
 * @brief The Base class define the SKIP fence which have to be destroy to make the game be loose
 */
class Base : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
    // variables
private :
    QGraphicsScene *scene ;
    int point_de_vie_total ;
    int point_de_vie_actuel ;

    // méthodes
public :
    bool detruite() ;
    void reparation_totale() ;
    void operator-( int degat ) ; // en gros c'est : quand la base est attaqué, elle perd des pvs

    // constructeurs / destructeurs
public:
    Base( QGraphicsScene *scene , int pv_base ) ;
    ~Base(){}
} ;

#endif // base_h
