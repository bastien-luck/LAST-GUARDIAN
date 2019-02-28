#ifndef mob_slime_cpp
#define mob_slime_cpp

#include "mob_slime.h"

/**
 * @brief Mob_slime::Mob_slime constructeur de la classe mob_slime
 * @param scene la scene où se déroule le jeu
 * @param summon_pos_x position horizontal forcée quand l'ennemi est une invocation
 * @param summon_pos_y position vertical forcée quand l'ennemi est une invocation
 */

Mob_slime::Mob_slime( QGraphicsScene *scene , int summon_pos_x  , int summon_pos_y ) : Ennemis( scene , 93 , 60 , 72 , 36 , 15 , 24 , 5 , 5 , 3 , 2 , 10 , "mob" , "slime" , 4 , 5 , 4 , 2 , 6 , summon_pos_x , summon_pos_y )
{
    /* stats :
     * largeur : 31*3 = 93
     * hauteur : 20*3 = 60
     * largeur hitbox moyenne : 21*3 = 63
     * hauteur hitbox moyenne : 12*3 = 36
     * décalage de l'animation avec la taille du sprite en x : 5*3 = 15
     * décalage de l'animation avec la taille du sprite en y : 8*3 = 24
     * pv : 5
     * delais : 5
     * degat : 3
     * vitesse : 2
     * portée d'attaque : 10
     * nom du monstre : slime
     * nombre d'image pour l'animation du mouvement : 4
     * nombre d'image pour l'animation d'attaque : 5
     * nombre d'image pour l'animation de mort : 4
     * numero de l'image où l'attaque a lieu : 2
     * nombre de frames pour changer l'image courante : 6
    */
    // sert juste à initialiser des valeurs fixes
}

#endif // mob_slime_cpp
