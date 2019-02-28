#ifndef gestion_input_cpp
#define gestion_input_cpp

#include "gestion_input.h"
#include "frame.h"

/**
 * @brief Gestion_input::Gestion_input constructeur de la classe Gestion_input
 */

Gestion_input::Gestion_input()
{
    this->tire_munition = false ;
    this->fin = false ;
    this->haut = false ;
    this->bas = false ;
    this->auto_fire = false ;
    this->validation = false ;
    this->choix_arme = 0 ;
    this->left_click_pressed = false ;
    this->left_click_released = false ;
    this->give_me_a_B = false ;
    this->give_me_a_U = false ;
    this->give_me_a_G = false ;
    this->setRect( -10 , -10 , Frame::largeur_ecran+20 , Frame::hauteur_ecran+20 ) ; // permet de garder le focus lors des clics hourra :)
}

/**
 * @brief Gestion_input::keyPressEvent permet de savoir quoi et quand un joueur appui sur une touche du clavier
 * @param event les données associé à une touche de clavier
 */

void Gestion_input::keyPressEvent( QKeyEvent * event )
{
    if ( event->isAutoRepeat() == false ) // permet de ne pas être embété par l'autorepeat du clavier
    {
        if ( event->key() == Qt::Key_Up )
        {
            this->haut = true ;
        }
        else if ( event->key() == Qt::Key_Down )
        {
            this->bas = true ;
        }
        else if ( event->key() == Qt::Key_Space )
        {
            this->tire_munition = true ;
        }
        else if ( event->key() == Qt::Key_Escape )
        {
            this->fin = true ;
        }
        else if ( event->key() == Qt::Key_T )
        {
            this->auto_fire = true ;
        }
        else if ( (event->key() == Qt::Key_Enter) | (event->key() == Qt::Key_Enter-1) ) // va savoir pourquoi la touche entrée côté pavé numérique est différente de la touche entrée du côté alphanumérique...
        {
            this->validation = true ;
        }
        else if ( event->key() == Qt::Key_Ampersand ) // &
        {
            this->choix_arme = 0 ;
        }
        else if ( event->key() == Qt::Key_Eacute ) // é
        {
            this->choix_arme = 1 ;
        }
        else if ( event->key() == Qt::Key_QuoteDbl ) // "
        {
            this->choix_arme = 2 ;
        }
        else if ( event->key() == Qt::Key_Apostrophe ) // '
        {
            this->choix_arme = 3 ;
        }
        else if ( event->key() == Qt::Key_ParenLeft ) // (
        {
            this->choix_arme = 4 ;
        }
        else if ( event->key() == Qt::Key_B )
        {
            this->give_me_a_B = true ;
        }
        else if ( event->key() == Qt::Key_U )
        {
            this->give_me_a_U = true ;
        }
        else if ( event->key() == Qt::Key_G )
        {
            this->give_me_a_G = true ;
        }
    }
}

/**
 * @brief Gestion_input::keyReleaseEvent permet de savoir quoi et quand un joueur lache son appui une touche du clavier
 * @param event les données associé à une touche de clavier
 */

void Gestion_input::keyReleaseEvent( QKeyEvent *event )
{
    if ( event->isAutoRepeat() == false ) // permet de ne pas être embété par l'autorepeat du clavier
    {
        if ( event->key() == Qt::Key_Up )
        {
            this->haut = false ;
        }
        else if ( event->key() == Qt::Key_Down )
        {
            this->bas = false ;
        }
        else if ( event->key() == Qt::Key_Space )
        {
            this->tire_munition = false ;
        }
        else if ( event->key() == Qt::Key_T ) // pas utile car il est nécessaire de mettre à false après le changement
        {
            this->auto_fire = false ;
        }
        else if ( (event->key() == Qt::Key_Enter) | (event->key() == Qt::Key_Enter-1) )
        {
            this->validation = false ;
        }
        else if ( event->key() == Qt::Key_B )
        {
            this->give_me_a_B = false ;
        }
        else if ( event->key() == Qt::Key_U )
        {
            this->give_me_a_U = false ;
        }
        else if ( event->key() == Qt::Key_G )
        {
            this->give_me_a_G = false ;
        }
    }
}

/**
 * @brief Gestion_input::mousePressEvent permet de savoir quoi et quand un joueur appui sur un bouton de la souris
 * @param event les données associé a un bouton de la souris
 */

void Gestion_input::mousePressEvent( QGraphicsSceneMouseEvent *event ) // il n'y a bien pas d'erreur : avoir une partie pressed et released permet de "repenser" son clique à la dernière seconde
{
    if ( event->button() == Qt::LeftButton )
    {
        this->left_click_pressed = true ;
    }

}

/**
 * @brief Gestion_input::mouseReleaseEvent permet de savoir quoi et quand un joueur lache son appui sur un bouton de la souris
 * @param event les données associé a un bouton de la souris
 */

void Gestion_input::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
    {
        this->left_click_released = true ;
        this->left_click_pressed = false ;
    }
}

/**
 * @brief Gestion_input::mouseMoveEvent permet de savoir où se situe le curseur lors d'un déplacement effectué lors de l'appui continu sur un bouton de la souris
 * @param event les données associé a un bouton de la souris
 * non utilisé mais était prévu pour gérer les barres de défilement
 */

void Gestion_input::mouseMoveEvent( QGraphicsSceneMouseEvent *event ) // ne marche que si un bouton de la souris est utilisé
{

}

#endif // gestion_input_cpp
