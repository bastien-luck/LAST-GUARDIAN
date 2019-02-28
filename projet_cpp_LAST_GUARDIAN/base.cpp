#ifndef base_cpp
#define base_cpp

#include "base.h"

/**
 * @brief Base::Base constructeur de la classe Base
 * @param scene la scene où se déroule le jeu
 * @param pv_base pv que possède la base
 */

Base::Base( QGraphicsScene *scene , int pv_base )
{
    this->scene = scene ;
    this->point_de_vie_actuel = pv_base ;
    this->point_de_vie_total = pv_base ;
    this->setPos( 100 , 0 ) ;
}

/**
 * @brief Base::detruite vérifie si la base n'est pas détruite
 * @return true si la base n'a plus de pv
 */

bool Base::detruite()
{
    return this->point_de_vie_actuel <= 0 ;
}

/**
 * @brief Base::reparation_totale permet de réparer la base à chaque fin de niveau
 */

void Base::reparation_totale()
{
    this->point_de_vie_actuel = this->point_de_vie_total ;
}

/**
 * @brief Base::operator - fait perdre de la vie à la base lorsqu'elle est attaqué par un ennemi
 * @param degat dégat infligé par l'attaque reçu
 */

void Base::operator-( int degat )
{
    this->point_de_vie_actuel = this->point_de_vie_actuel - degat ;
}

#endif // base_cpp
