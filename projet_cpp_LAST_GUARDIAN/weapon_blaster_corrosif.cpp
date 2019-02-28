#ifndef weapon_blaster_corrosif_cpp
#define weapon_blaster_corrosif_cpp

#include "weapon_blaster_corrosif.h"

/**
 * @brief Weapon_blaster_corrosif::Weapon_blaster_corrosif constructeur de la classe Weapon_blaster_corrosif
 * @param scene la scene où se déroule le jeu
 */

Weapon_blaster_corrosif::Weapon_blaster_corrosif( QGraphicsScene *scene ) : Armes( scene , 1 , 5 , 100 , 10 , 0 , 0 , 2 , 2 , 0 , 0  , 1 )
{
    /* stats :
     * id de l'arme : 1
     * nombre de balles tirée : 5
     * delais entre les tirs : 100 frames
     * angle maximum des balles tirées : 10
     * nombre de fois qu'est améliorable la cadence de tir : 0
     * amélioration par niveau de la cadence de tir en nombre de frames : 0
     * nombre de fois qu'est améliorable le nombre de balle tiré en même temps : 2
     * amélioration par niveau du nombre de balles tirés : 2
     * nombre de fois qu'est améliorable les dégat des munitions tirés : 0
     * amélioration par niveau des dégats : 0
     * balle tiré : projectile_corrosif ( id : 1 )
    */
}

#endif // weapon_blaster_corrosif_cpp
