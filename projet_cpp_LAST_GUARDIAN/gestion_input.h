#ifndef gestion_input_h
#define gestion_input_h

#include <iostream>
#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

using namespace std ;

/**
 * @brief The Gestion_input class manage all the keyboard and mouse input available in the game
 */
class Gestion_input : public QObject , public QGraphicsRectItem
{
    Q_OBJECT
    // variables
public :
    bool tire_munition ;
    bool fin ;
    bool haut ;
    bool bas ;
    bool auto_fire ;
    bool validation ;
    bool left_click_pressed ;
    bool left_click_released ;
    int choix_arme ;
    bool give_me_a_B ;
    bool give_me_a_U ;
    bool give_me_a_G ;

    // méthodes
public :
    void keyPressEvent( QKeyEvent * event ) ;
    void keyReleaseEvent( QKeyEvent *event ) ;
    void mousePressEvent( QGraphicsSceneMouseEvent *event ) ; // va savoir pourquoi QMouseEvent ne marche pas...
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *event ) ;
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event ) ;

    // constructeurs / destructeurs
public :
    Gestion_input();
    ~Gestion_input(){}
} ;

#endif // gestion_input_h
