#ifndef mob_skeleton_cpp
#define mob_skeleton_cpp

#include "mob_skeleton.h"

/**
 * @brief Mob_skeleton::Mob_skeleton constructeur de la classe Mob_skeleton
 * @param scene la scene où se déroule le jeu
 * @param summon_pos_x position horizontal forcée quand l'ennemi est une invocation
 * @param summon_pos_y position vertical forcée quand l'ennemi est une invocation
 */

Mob_skeleton::Mob_skeleton( QGraphicsScene *scene , int summon_pos_x  , int summon_pos_y ) : Ennemis( scene , 150 , 111 , 45 , 75 , 75 , 36 , 25 , 20 , 10 , 0.65 , 25 , "mob" , "skeleton" , 13 , 18 , 15 , 7 , 6 , summon_pos_x , summon_pos_y )
{
    /* stats :
     * largeur : 50*3 = 150
     * hauteur : 37*3 = 111
     * largeur hitbox moyenne : 15*3 = 45
     * hauteur hitbox moyenne : 25*3 = 75
     * décalage de l'animation avec la taille du sprite en x : 25*3 = 75
     * décalage de l'animation avec la taille du sprite en y : 12*3 = 36
     * pv : 25
     * delais : 20
     * degat : 10
     * vitesse : 0.65
     * portée d'attaque : 25
     * nom du monstre : skeleton
     * nombre d'image pour l'animation du mouvement : 13
     * nombre d'image pour l'animation d'attaque : 18
     * nombre d'image pour l'animation de mort : 15
     * numero de l'image où l'attaque a lieu : 7
     * nombre de frames pour changer l'image courante : 6
    */
    // sert juste à initialiser des valeurs fixes
}

#endif // mob_skeleton_cpp
