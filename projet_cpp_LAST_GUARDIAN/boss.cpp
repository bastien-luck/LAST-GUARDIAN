#ifndef boss_cpp
#define boss_cpp

#include "boss.h"

/**
 * @brief Boss::Boss constructeur de la classe Boss
 * @param scene la scene où se déroule le jeu
 * @param largeur largeur de l'image du boss
 * @param hauteur hauteur de l'image du boss
 * @param largeur_hitbox largeur de la hitbox de l'image du boss
 * @param hauteur_hitbox hauteur de la hitbox de l'image du boss
 * @param decalage_hitbox_x largeur de l'image avant d'atteindre la hitbox réelle du boss
 * @param decalage_hitbox_y hauteur de l'image avant d'atteindre la hitbox réelle du boss
 * @param nb_phase nombre de phase du boss
 * @param pv_tot nombre de pv du boss
 * @param delais nombre de frame à attendre avant le spawn du prochain ennemi
 * @param degat dégat que fait le boss à chaque attaque
 * @param speed vitesse de mouvement du boss
 * @param range distance d'attaque du boss
 * @param nom nom du boss pour savoir dans quel dossier chercher ses sprites
 * @param nb_img_move nombre d'image de l'animation complete de déplacement du boss
 * @param nb_img_attack nombre d'image de l'animation complete d'attaque du boss
 * @param nb_img_die nombre d'image de l'animation complete de mort du boss
 * @param num_img_dmg numero de l'image où le boss inflige des dégat à la base
 * @param delais_sprite nombre de frame entre deux changement d'image
 */

Boss::Boss( QGraphicsScene *scene , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , int nb_phase , int pv_tot , int delais , int degat , qreal speed , int range , QString nom , int nb_img_move , int nb_img_attack , int nb_img_die , int num_img_dmg , int delais_sprite ) : Ennemis( scene , largeur , hauteur , largeur_hitbox , hauteur_hitbox , decalage_hitbox_x , decalage_hitbox_y , pv_tot , delais , degat , speed , range , "boss" , nom , nb_img_move , nb_img_attack , nb_img_die , num_img_dmg , delais_sprite )
{
    this->nombre_de_phase_total = nb_phase ;
    this->numero_phase_actuelle = 0 ;
    this->barre_haut_screen = new Barre_de_vie( this->scene ) ;
}

/**
 * @brief Boss::get_hp_boss getter de barre_haut_screen
 * @return la barre de vie toujours visible du boss
 */

Barre_de_vie *Boss::get_hp_boss()
{
    return this->barre_haut_screen ;
}

/**
 * @brief Boss::get_nb_phase_boss getter de nombre_de_phase_total
 * @return le nombre de phase du boss
 */

int Boss::get_nb_phase_boss()
{
    return this->nombre_de_phase_total ;
}

#endif // boss_cpp
