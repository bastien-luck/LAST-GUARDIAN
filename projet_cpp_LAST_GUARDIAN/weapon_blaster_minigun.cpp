#ifndef weapon_blaster_minigun_cpp
#define weapon_blaster_minigun_cpp

#include "weapon_blaster_minigun.h"

/**
 * @brief Weapon_blaster_minigun::Weapon_blaster_minigun constructeur de la classe Weapon_blaster_minigun
 * @param scene la scene où se déroule le jeu
 */

Weapon_blaster_minigun::Weapon_blaster_minigun( QGraphicsScene *scene ) : Armes( scene , 4 , 1 , 4 , 5 , 1 , 1 , 0 , 0 , 1 , 1  , 4 )
{
    /* stats :
     * id de l'arme : 4
     * nombre de balles tirée : 1
     * delais entre les tirs : 4 frames
     * angle maximum des balles tirées : 5
     * nombre de fois qu'est améliorable la cadence de tir : 1
     * amélioration par niveau de la cadence de tir en nombre de frames : 1
     * nombre de fois qu'est améliorable le nombre de balle tiré en même temps : 0
     * amélioration par niveau du nombre de balles tirés : 0
     * nombre de fois qu'est améliorable les dégat des munitions tirés : 1
     * amélioration par niveau des dégats : 1
     * balle tiré : projectile_rapide ( id : 4 )
    */
}

#endif // weapon_blaster_minigun_cpp
