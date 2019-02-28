#ifndef projectile_corrosif_cpp
#define projectile_corrosif_cpp

#include "projectile_corrosif.h"

/**
 * @brief Projectile_corrosif::Projectile_corrosif constructeur de la classe Projectile_corrosif
 * @param scene la scene où se déroule le jeu
 * @param pos_y position vertical de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectile_corrosif::Projectile_corrosif( QGraphicsScene *scene , qreal pos_y , int angle_balle , int amelioration_degat ) : Projectiles( scene , pos_y , 1 , 0 + amelioration_degat , 18 , 18 , 4 , 4 , 8 , 8 , "projectile_corrosif" , 10 , angle_balle , false , 2 )
{
    /* stats :
     * id du projectile : 1
     * dégat du projectile : 0
     * largeur du sprite du projectile : 18
     * hauteur du sprite du projectile : 18
     * largeur de la hitbox du projectile : 4
     * hauteur de la hitbox du projectile : 4
     * décalage en x de la hitbox du projectile par rapport à son image : 8
     * décalage en y de la hitbox du projectile par rapport à son image : 8
     * nom du projectile : projectile_corrosif
     * vitesse du projectile : 10
     * transperce les ennemis : false
     * dommage dot : 2
    */
}

#endif // projectile_corrosif_cpp
