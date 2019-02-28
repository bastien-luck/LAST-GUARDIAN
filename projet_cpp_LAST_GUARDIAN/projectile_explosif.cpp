#ifndef projectile_explosif_cpp
#define projectile_explosif_cpp

#include "projectile_explosif.h"

/**
 * @brief Projectile_explosif::Projectile_explosif constructeur de la classe Projectile_explosif
 * @param scene la scene où se déroule le jeu
 * @param pos_y position vertical de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectile_explosif::Projectile_explosif( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) : Projectiles( scene , pos_y , 3 , 25 + amelioration_degat , 97 , 68 , 12 , 12 , 68 , 27 , "projectile_explosif" , 15 , angle_balle , false , 0 , 200 )
{
    /* stats :
     * id du projectile : 3
     * dégat du projectile : 25
     * largeur du sprite du projectile : 97
     * hauteur du sprite du projectile : 68
     * largeur de la hitbox du projectile : 12
     * hauteur de la hitbox du projectile : 12
     * décalage en x de la hitbox du projectile par rapport à son image : 68
     * décalage en y de la hitbox du projectile par rapport à son image : 27
     * nom du projectile : projectile_explosif
     * vitesse du projectile : 15
    */
}

#endif // projectile_explosif_cpp
