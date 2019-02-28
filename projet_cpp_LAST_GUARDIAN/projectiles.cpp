#ifndef projectiles_cpp
#define projectiles_cpp

#include "projectiles.h"

/**
 * @brief Projectiles::Projectiles constructeur de la classe Projectiles
 * @param scene la scene où se déroule le jeu
 * @param y position vertical de la balle
 * @param id_balle id de la balle
 * @param dmg dégat de la balle
 * @param largeur largeur de l'image de la balle
 * @param hauteur hauteur de l'image de la balle
 * @param largeur_hitbox largeur de la hitbox de l'image de la balle
 * @param hauteur_hitbox hauteur de la hitbox de l'image de la balle
 * @param decalage_hitbox_x largeur de l'image avant d'atteindre la hitbox réelle de la balle
 * @param decalage_hitbox_y hauteur de l'image avant d'atteindre la hitbox réelle de la balle
 * @param nom_image nom de la balle pour savoir dans quel dossier chercher son sprite
 * @param speed vitesse de mouvement de la balle
 * @param angle_balle l'angle de déplacement de la balle
 * @param pierce est-ce que la balle traverse les ennemis (non implémenté)
 * @param dot dégat sur le temps de la balle
 * @param aoe zone d'effet d'explosion de la balle
 * @param amelioration_degat dégats supplémentaire de la balle dus à une amélioration de l'arme associé
 */

Projectiles::Projectiles( QGraphicsScene *scene , qreal y , int id_balle , int dmg , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , QString nom_image , qreal speed , int angle_balle , bool pierce , int dot ,  qreal aoe , int amelioration_degat )
{
    this->scene = scene ;
    this->id_balle = id_balle ;
    this->degat = dmg + amelioration_degat ;
    this->largeur_sprite_projectile = largeur ;
    this->hauteur_sprite_projectile = hauteur ;
    this->largeur_hitbox_projectile = largeur_hitbox ;
    this->hauteur_hitbox_projectile = hauteur_hitbox ;
    this->declage_x_hitbox_et_sprite_projectile = decalage_hitbox_x ;
    this->declage_y_hitbox_et_sprite_projectile = decalage_hitbox_y ;
    this->penetration = pierce ;
    this->setPos( 45 , y + 37 - hauteur * 0.5 ) ;
    this->vitesse = speed ;
    this->angle = angle_balle ;
    this->dot = dot ;
    this->rayon_explosion = aoe ;
    this->sprite_projectile = nom_image ;

    // draw the image
    this->setPixmap( QPixmap( ":/images/images_jeu/projectiles/" + this->sprite_projectile + ".png" ).scaled( this->largeur_sprite_projectile , this->hauteur_sprite_projectile ) ) ;
    this->scene->addItem( this ) ;
}

/**
 * @brief Projectiles::move_projectile permet de déplacer la balle dans sa direction de déplacement
 */

void Projectiles::move_projectile()
{
    this->setPos( this->x() + qCos(qDegreesToRadians(this->angle)) * this->vitesse , this->y() - qSin(qDegreesToRadians(this->angle)) * this->vitesse ) ;
}

/**
 * @brief Projectiles::get_hauteur_balle getter de hauteur_sprite_projectile
 * @return la hauteur de l'image de la balle
 */

int Projectiles::get_hauteur_balle()
{
    return this->hauteur_sprite_projectile ;
}

/**
 * @brief Projectiles::get_largeur_balle getter de largeur_sprite_projectile
 * @return la largeur de l'image de la balle
 */

int Projectiles::get_largeur_balle()
{
    return this->largeur_sprite_projectile ;
}

/**
 * @brief Projectiles::get_hauteur_hitbox_balle getter de hauteur_hitbox_projectile
 * @return la hauteur de la hitbox de la balle
 */

int Projectiles::get_hauteur_hitbox_balle()
{
    return this->hauteur_hitbox_projectile ;
}

/**
 * @brief Projectiles::get_largeur_hitbox_balle getter de largeur_hitbox_projectile
 * @return la largeur de la hitbox de la balle
 */

int Projectiles::get_largeur_hitbox_balle()
{
    return this->largeur_hitbox_projectile ;
}

/**
 * @brief Projectiles::get_decalage_x_hitbox_et_sprites_balle getter de declage_x_hitbox_et_sprite_projectile
 * @return la largeur de l'image avant d'atteindre la hitbox réelle de la balle
 */

int Projectiles::get_decalage_x_hitbox_et_sprites_balle()
{
    return this->declage_x_hitbox_et_sprite_projectile ;
}

/**
 * @brief Projectiles::get_decalage_y_hitbox_et_sprites_balle getter de declage_y_hitbox_et_sprite_projectile
 * @return la hauteur de l'image avant d'atteindre la hitbox réelle de la balle
 */

int Projectiles::get_decalage_y_hitbox_et_sprites_balle()
{
    return this->declage_y_hitbox_et_sprite_projectile ;
}

/**
 * @brief Projectiles::get_degat getter de degat
 * @return les dégat de la balle
 */

int Projectiles::get_degat()
{
    return this->degat ;
}

/**
 * @brief Projectiles::get_degat_poison getter de dot
 * @return les dégats sur le temps de la balle
 */

int Projectiles::get_degat_poison()
{
    return this->dot ;
}

/**
 * @brief Projectiles::transperce getter de penetration
 * @return true si la balle transperce les ennemis
 */

bool Projectiles::transperce()
{
    return this->penetration ;
}

/**
 * @brief Projectiles::get_aoe getter de rayon_explosion
 * @return le rayon d'explosion de la balle
 */

qreal Projectiles::get_aoe()
{
    return this->rayon_explosion ;
}

/**
 * @brief Projectiles::explose permet de faire exploser la balle
 * @return l'explosion de la balle
 */

Explosion *Projectiles::explose()
{
    return new Explosion( this->scene , this->x() + this->declage_x_hitbox_et_sprite_projectile + this->largeur_hitbox_projectile * 0.5 , this->y() + this->declage_y_hitbox_et_sprite_projectile + this->hauteur_hitbox_projectile * 0.5 , 200 , 200 , 166 , 166 , 17 , 17 , "explosion_projectile_explosif_" , 32 ) ;
}

#endif // projectiles_cpp
