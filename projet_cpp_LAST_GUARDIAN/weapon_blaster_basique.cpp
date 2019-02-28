#ifndef weapon_blaster_basique_cpp
#define weapon_blaster_basique_cpp

#include "weapon_blaster_basique.h"

/**
 * @brief Weapon_blaster_basique::Weapon_blaster_basique constructeur de la classe Weapon_blaster_basique
 * @param scene la scene où se déroule le jeu
 */

Weapon_blaster_basique::Weapon_blaster_basique( QGraphicsScene *scene ) : Armes( scene , 0 , 1 , 20 , 0 , 2 , -2 , 0 , 0 , 2 , 1  , 0 )
{
    /* stats :
     * id de l'arme : 0
     * nombre de balles tirée : 1
     * delais entre les tirs : 20 frames
     * angle maximum des balles tirées : 0
     * nombre de fois qu'est améliorable la cadence de tir : 2
     * amélioration par niveau de la cadence de tir en nombre de frames : -2
     * nombre de fois qu'est améliorable le nombre de balle tiré en même temps : 0
     * amélioration par niveau du nombre de balles tirés : 0
     * nombre de fois qu'est améliorable les dégat des munitions tirés : 2
     * amélioration par niveau des dégats : 1
     * balle tiré : projectile_basique ( id : 0 )
    */
}

#endif // weapon_blaster_basique_cpp
