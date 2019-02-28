#ifndef projectile_basique_cpp
#define projectile_basique_cpp

#include "projectile_basique.h"

/**
 * @brief Projectile_basique::Projectile_basique constructeur de la classe Projectile_basique
 * @param scene la scene où se déroule le jeu
 * @param pos_y position vertical de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectile_basique::Projectile_basique( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) : Projectiles( scene , pos_y , 0 , 1 + amelioration_degat , 24 , 22 , 10 , 4 , 7 , 9 , "projectile_basique" , 20 , angle_balle )
{
    /* stats :
     * id du projectile : 0
     * dégat du projectile : 1
     * largeur du sprite du projectile : 24
     * hauteur du sprite du projectile : 22
     * largeur de la hitbox du projectile : 10
     * hauteur de la hitbox du projectile : 4
     * décalage en x de la hitbox du projectile par rapport à son image : 7
     * décalage en y de la hitbox du projectile par rapport à son image : 9
     * nom du projectile : projectile_basique
     * vitesse du projectile : 20
    */
}

#endif // projectile_basique_cpp
