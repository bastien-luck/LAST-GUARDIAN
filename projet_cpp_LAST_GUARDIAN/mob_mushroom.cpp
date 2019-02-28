#ifndef mob_mushroom_cpp
#define mob_mushroom_cpp

#include "mob_mushroom.h"

/**
 * @brief Mob_mushroom::Mob_mushroom constructeur de la classe Mob_mushroom
 * @param scene la scene où se déroule le jeu
 * @param summon_pos_x position horizontal forcée quand l'ennemi est une invocation
 * @param summon_pos_y position vertical forcée quand l'ennemi est une invocation
 */

Mob_mushroom::Mob_mushroom( QGraphicsScene *scene , int summon_pos_x , int summon_pos_y ) : Ennemis( scene , 90 , 90 , 60 , 60 , 15 , 30 , 10 , 5 , 5 , 1 , 10 , "mob" , "mushroom" , 11 , 6 , 9 , 4 , 12 , summon_pos_x , summon_pos_y )
{
    /* stats :
     * largeur : 30*3 = 90
     * hauteur : 30*3 = 90
     * largeur hitbox moyenne : 20*3 = 60
     * hauteur hitbox moyenne : 20*3 = 60
     * décalage de l'animation avec la taille du sprite en x : 5*3 = 15
     * décalage de l'animation avec la taille du sprite en y : 10*3 = 30
     * pv : 10
     * delais : 5
     * degat : 5
     * vitesse : 1
     * portée d'attaque : 10
     * nom du monstre : mushroom
     * nombre d'image pour l'animation du mouvement : 11
     * nombre d'image pour l'animation d'attaque : 6
     * nombre d'image pour l'animation de mort : 9
     * numero de l'image où l'attaque a lieu : 4
     * nombre de frames pour changer l'image courante : 12
    */
    // sert juste à initialiser des valeurs fixes
}

#endif // mob_mushroom_cpp
