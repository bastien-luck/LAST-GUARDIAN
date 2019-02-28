#ifndef projectile_rapide_cpp
#define projectile_rapide_cpp

#include "projectile_rapide.h"

/**
 * @brief Projectile_rapide::Projectile_rapide constructeur de la classe Projectile_rapide
 * @param scene la scene où se déroule le jeu
 * @param pos_y position vertical de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectile_rapide::Projectile_rapide( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) : Projectiles( scene , pos_y , 4 , 1 + amelioration_degat , 9 , 9 , 3 , 3 , 3 , 3 , "projectile_rapide" , 15 , angle_balle )
{
    /* stats :
     * id du projectile : 4
     * dégat du projectile : 1
     * largeur du sprite du projectile : 9
     * hauteur du sprite du projectile : 9
     * largeur de la hitbox du projectile : 3
     * hauteur de la hitbox du projectile : 3
     * décalage en x de la hitbox du projectile par rapport à son image : 3
     * décalage en y de la hitbox du projectile par rapport à son image : 3
     * nom du projectile : projectile_rapide
     * vitesse du projectile : 15
    */
}

#endif // projectile_rapide_cpp
