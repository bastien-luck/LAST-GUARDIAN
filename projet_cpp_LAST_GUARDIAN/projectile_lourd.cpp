#ifndef projectile_lourd_cpp
#define projectile_lourd_cpp

#include "projectile_lourd.h"

/**
 * @brief Projectile_lourd::Projectile_lourd constructeur de la classe Projectile_lourd
 * @param scene la scene où se déroule le jeu
 * @param pos_y position vertical de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectile_lourd::Projectile_lourd( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) : Projectiles( scene , pos_y , 2 , 20 + amelioration_degat , 112 , 72 , 55 , 8 , 29 , 31 , "projectile_lourd" , 30 , angle_balle )
{
    /* stats :
     * id du projectile : 2
     * dégat du projectile : 20
     * largeur du sprite du projectile : 112
     * hauteur du sprite du projectile : 72
     * largeur de la hitbox du projectile : 55
     * hauteur de la hitbox du projectile : 8
     * décalage en x de la hitbox du projectile par rapport à son image : 29
     * décalage en y de la hitbox du projectile par rapport à son image : 31
     * nom du projectile : projectile_lourd
     * vitesse du projectile : 30
    */
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // projectile_lourd_cpp
