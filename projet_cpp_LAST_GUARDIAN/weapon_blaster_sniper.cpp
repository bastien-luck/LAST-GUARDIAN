#ifndef weapon_blaster_sniper_cpp
#define weapon_blaster_sniper_cpp

#include "weapon_blaster_sniper.h"

/**
 * @brief Weapon_blaster_sniper::Weapon_blaster_sniper constructeur de la classe Weapon_blaster_sniper
 * @param scene la scene où se déroule le jeu
 */

Weapon_blaster_sniper::Weapon_blaster_sniper( QGraphicsScene *scene ) : Armes( scene , 2 , 1 , 100 , 0 , 0 , 0 , 0 , 0 , 3 , 10  , 2 )
{
    /* stats :
     * id de l'arme : 2
     * nombre de balles tirée : 1
     * delais entre les tirs : 100 frames
     * angle maximum des balles tirées : 0
     * nombre de fois qu'est améliorable la cadence de tir : 0
     * amélioration par niveau de la cadence de tir en nombre de frames : 0
     * nombre de fois qu'est améliorable le nombre de balle tiré en même temps : 0
     * amélioration par niveau du nombre de balles tirés : 0
     * nombre de fois qu'est améliorable les dégat des munitions tirés : 3
     * amélioration par niveau des dégats : 10
     * balle tiré : projectile_lourd ( id : 2 )
    */
}

#endif // weapon_blaster_sniper_cpp
