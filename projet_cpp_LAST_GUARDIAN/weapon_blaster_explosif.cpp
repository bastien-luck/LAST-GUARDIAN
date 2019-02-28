#ifndef weapon_blaster_explosif_cpp
#define weapon_blaster_explosif_cpp

#include "weapon_blaster_explosif.h"

/**
 * @brief Weapon_blaster_explosif::Weapon_blaster_explosif constructeur de la classe Weapon_blaster_explosif
 * @param scene la scene où se déroule le jeu
 */

Weapon_blaster_explosif::Weapon_blaster_explosif( QGraphicsScene *scene ) : Armes( scene , 3 , 1 , 100 , 0 , 2 , 25 , 0 , 0 , 0 , 0  , 3 )
{
    /* stats :
     * id de l'arme : 3
     * nombre de balles tirée : 1
     * delais entre les tirs : 100 frames
     * angle maximum des balles tirées : 0
     * nombre de fois qu'est améliorable la cadence de tir : 2
     * amélioration par niveau de la cadence de tir en nombre de frames : -25
     * nombre de fois qu'est améliorable le nombre de balle tiré en même temps : 0
     * amélioration par niveau du nombre de balles tirés : 0
     * nombre de fois qu'est améliorable les dégat des munitions tirés : 0
     * amélioration par niveau des dégats : 0
     * balle tiré : projectile_explosif ( id : 3 )
    */
}

#endif // weapon_blaster_explosif_cpp
