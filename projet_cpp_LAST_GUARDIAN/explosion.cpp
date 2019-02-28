#ifndef explosion_cpp
#define explosion_cpp

#include "explosion.h"

/**
 * @brief Explosion::Explosion constructeur de la classe Explosion
 * @param scene la scene où se déroule le jeu
 * @param x position horizontal du milieu de l'image de l'explosion
 * @param y position vertical du milieu de l'image de l'explosion
 * @param largeur largeur de l'image de l'explosion
 * @param hauteur hauteur de l'image de l'explosion
 * @param largeur_hitbox largeur de la hitbox de l'image de l'explosion
 * @param hauteur_hitbox hauteur de la hitbox de l'image de l'explosion
 * @param decalage_hitbox_x largeur de l'image avant d'atteindre la hitbox réelle de l'explosion
 * @param decalage_hitbox_y hauteur de l'image avant d'atteindre la hitbox réelle de l'explosion
 * @param nom_image nom de l'explosion pour savoir dans quel dossier chercher ses sprites
 * @param nombre_sprite_explosion nombre d'image de l'animation complète de l'explosion
 */

Explosion::Explosion( QGraphicsScene *scene , qreal x , qreal y , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , QString nom_image , int nombre_sprite_explosion )
{
    this->scene = scene ;
    this->largeur_sprite_explosion = largeur ;
    this->hauteur_sprite_explosion = hauteur ;
    this->largeur_hitbox_explosion = largeur_hitbox ;
    this->hauteur_hitbox_explosion = hauteur_hitbox ;
    this->declage_x_hitbox_et_sprite_explosion = decalage_hitbox_x ;
    this->declage_y_hitbox_et_sprite_explosion = decalage_hitbox_y ;
    this->sprite_explosion = nom_image ;
    this->nombre_sprite = nombre_sprite_explosion ;
    this->numero_sprite_actuel = 0 ;
    this->setPos( x - this->largeur_sprite_explosion * 0.5 , y - this->hauteur_sprite_explosion * 0.5 ) ;
    this->setZValue( 3 ) ;
    this->setPixmap( QPixmap( ":/images/images_jeu/explosions/" + this->sprite_explosion + QString::number(this->numero_sprite_actuel) + ".png" ).scaled( this->largeur_sprite_explosion , this->hauteur_sprite_explosion , Qt::KeepAspectRatio ) ) ;
    this->scene->addItem( this ) ;
}

/**
 * @brief Explosion::explosion_en_cours permet de jouer l'animation de l'explosion et de savoir si celle ci est finie
 * @return true si l'animation de l'explosion n'est pas finie
 */

bool Explosion::explosion_en_cours()
{
    if ( this->numero_sprite_actuel < this->nombre_sprite )
    {
        this->numero_sprite_actuel++ ;
        this->setPixmap( QPixmap( ":/images/images_jeu/explosions/" + this->sprite_explosion + QString::number(this->numero_sprite_actuel) + ".png" ).scaled( this->largeur_sprite_explosion , this->hauteur_sprite_explosion , Qt::KeepAspectRatio ) ) ;
        return true ;
    }
    else
    {
        return false ;
    }
}

/**
 * @brief Explosion::get_largeur_hitbox_bombe getter de largeur_hitbox_explosion
 * @return la largeur de la hitbox de l'image de l'explosion
 */

int Explosion::get_largeur_hitbox_bombe()
{
    return this->largeur_hitbox_explosion ;
}

/**
 * @brief Explosion::get_hauteur_hitbox_bombe getter de hauteur_hitbox_explosion
 * @return la hauteur de la hitbox de l'image de l'explosion
 */

int Explosion::get_hauteur_hitbox_bombe()
{
    return this->hauteur_hitbox_explosion ;
}

/**
 * @brief Explosion::get_decalage_x_hitbox_et_sprites_bombe getter de declage_x_hitbox_et_sprite_explosion
 * @return la largeur de l'image avant d'atteindre la hitbox réelle de l'explosion
 */

int Explosion::get_decalage_x_hitbox_et_sprites_bombe()
{
    return this->declage_x_hitbox_et_sprite_explosion ;
}

/**
 * @brief Explosion::get_decalage_y_hitbox_et_sprites_bombe getter de declage_y_hitbox_et_sprite_explosion
 * @return la hauteur de l'image avant d'atteindre la hitbox réelle de l'explosion
 */

int Explosion::get_decalage_y_hitbox_et_sprites_bombe()
{
    return this->declage_y_hitbox_et_sprite_explosion ;
}

#endif // explosion_cpp
