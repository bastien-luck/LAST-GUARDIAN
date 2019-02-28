#ifndef armes_cpp
#define armes_cpp

#include "armes.h"
#include "projectile_basique.h"
#include "projectile_lourd.h"
#include "projectile_corrosif.h"
#include "projectile_explosif.h"
#include "projectile_rapide.h"

/**
 * @brief Armes::Armes constructeur de la classe Armes
 * @param scene la scene où se déroule le jeu
 * @param id_arme l'id de l'arme pour permettre l'utilisation de switch/case impossible sur un QString
 * @param nb_bullet nombre de balles que tir l'arme
 * @param delais temps de rafraichissement de l'arme entre deux tirs
 * @param angle_max angle maximum qu'une balle tiré avec l'arme actuel peut prendre
 * @param lv_max_cad_tir nombre maximum d'amélioration de la cadence de tir par le joueur
 * @param scal_cad_tir valeur d'amélioration de la cadence de tir à chaque niveau d'amélioration
 * @param lv_max_nb_balle nombre maximum d'amélioration du nombre de balles tirées par le joueur
 * @param scal_nb_balle valeur d'amélioration du nombre de balles tirées à chaque niveau d'amélioration
 * @param lv_max_degat nombre maximum d'amélioration des dégats par le joueur
 * @param scal_degat valeur d'amélioration des dégats à chaque niveau d'amélioration
 * @param ammo l'id de la munition que l'arme utilise
 */

Armes::Armes( QGraphicsScene *scene , int id_arme , int nb_bullet , int delais , int angle_max , int lv_max_cad_tir , int scal_cad_tir , int lv_max_nb_balle , int scal_nb_balle , int lv_max_degat , int scal_degat , int ammo )
{
    this->scene = scene ;
    this->id_arme = id_arme ;
    this->nombre_projectile_tire = nb_bullet ;
    this->delais_entre_tir = delais ;
    this->delais_actuel = 0 ;
    this->angle_max_balles_tiree = angle_max ;
    this->level_max_cadence_de_tir = lv_max_cad_tir ;
    this->level_actuel_cadence_de_tir = 0 ;
    this->scaling_cadence_de_tir = scal_cad_tir ;
    this->level_max_nombre_de_balle_tire = lv_max_nb_balle ;
    this->level_actuel_nombre_de_balle_tire = 0 ;
    this->scaling_nombre_de_balle_tire = scal_nb_balle ;
    this->level_max_degat = lv_max_degat ;
    this->level_actuel_degat = 0 ;
    this->scaling_degat = scal_degat ;
    this->munition_tire = ammo ;
}

/**
 * @brief Armes::tire fait tirer un projectile par le joueur
 * @param pos_y position vertical actuelle du joueur
 * @param angle l'angle que prend la balles pour son déplacement
 * @return la balle qu'a tiré le joueur
 */

Projectiles *Armes::tire( qreal pos_y , int angle )
{
    this->delais_actuel = this->delais_entre_tir ;
    switch( this->munition_tire )
    {
    case 0 :
        return new Projectile_basique( this->scene , pos_y , angle , this->level_actuel_degat * this->scaling_degat ) ;
    case 1 :
        return new Projectile_corrosif( this->scene , pos_y , angle , this->level_actuel_degat * this->scaling_degat ) ;
    case 2 :
        return new Projectile_lourd( this->scene , pos_y , angle , this->level_actuel_degat * this->scaling_degat ) ;
    case 3 :
        return new Projectile_explosif( this->scene , pos_y , angle , this->level_actuel_degat * this->scaling_degat ) ;
    case 4 :
        return new Projectile_rapide( this->scene , pos_y , angle , this->level_actuel_degat * this->scaling_degat ) ;
    default :
        return nullptr ;
    }
}

/**
 * @brief Armes::tir_possible permet de vérifier si l'arme équipé a finie son refroidissement entre deux tirs
 * @param joueur_tire est-ce que le joueur demande manuellement le tir de la balle ?
 * @param tir_auto est-ce que le joueur a enclenché le tir automatique ?
 * @return true si le joueur peut tirer
 */

bool Armes::tir_possible( bool joueur_tire , bool tir_auto )
{
    if ( this->delais_actuel > 0 )
    {
        this->delais_actuel-- ;
        return false ;
    }
    else
    {
        if ( joueur_tire == true || tir_auto == true )
        {
            this->delais_actuel = this->delais_entre_tir ;
            return true ;
        }
        return false ; // si on met directemment return true, ça fait un tir auto : peut être intéressant :)
    }
}

/**
 * @brief Armes::get_id_arme getter de id_arme
 * @return l'id de l'arme
 */

int Armes::get_id_arme()
{
    return this->id_arme ;
}

/**
 * @brief Armes::get_nombre_projectiles_tire getter de nombre_projectile_tire
 * @return le nombre projectiles tiré
 */

int Armes::get_nombre_projectiles_tire()
{
    return this->nombre_projectile_tire ;
}

/**
 * @brief Armes::delais_changement_arme délais ocurrant au moment où l'on change d'arme
 */

void Armes::delais_changement_arme()
{
    this->delais_actuel = int (this->delais_entre_tir*0.5) ;
}

/**
 * @brief Armes::get_angle_max getter de angle_max_balles_tiree
 * @return l'angle maximal que peut prendre une balle tirée par l'arme
 */

int Armes::get_angle_max()
{
    return this->angle_max_balles_tiree ;
}

/**
 * @brief Armes::ameliore_arme permet d'améliorer les stats de l'arme
 * @param type_amelioration 0 : amélioration des dégats des projectiles, 1 : amélioration de la cadence de tir de l'arme, 2 : amélioration du nombre de balles tirées par l'arme
 */

void Armes::ameliore_arme( int type_amelioration )
{
    switch( type_amelioration )
    {
    case 0 :
        if ( this->level_actuel_degat < this->level_max_degat )
        {
            this->level_actuel_degat++ ;
        }
        break ;
    case 1 :
        if ( this->level_actuel_cadence_de_tir < this->level_max_cadence_de_tir )
        {
            this->level_actuel_cadence_de_tir++ ;
            this->delais_entre_tir -= this->scaling_cadence_de_tir ;
        }
        break ;
    case 2 :
        if ( this->level_actuel_nombre_de_balle_tire < this->level_max_nombre_de_balle_tire )
        {
            this->level_actuel_nombre_de_balle_tire++ ;
            this->nombre_projectile_tire += this->scaling_nombre_de_balle_tire ;
        }
        break ;
    }
}

/**
 * @brief Armes::get_level_actuel_degat getter de level_actuel_degat
 * @return le nombre d'amélioration de type dégat effectué sur l'arme
 */

int Armes::get_level_actuel_degat()
{
    return this->level_actuel_degat ;
}

/**
 * @brief Armes::get_level_max_degat getter de level_max_degat
 * @return le nombre de fois que peut être amélioré l'arme avec l'option dégat
 */

int Armes::get_level_max_degat()
{
    return this->level_max_degat ;
}

/**
 * @brief Armes::get_level_actuel_cadence_tir getter de level_actuel_cadence_de_tir
 * @return le nombre d'amélioration de type cadence de tir effectué sur l'arme
 */

int Armes::get_level_actuel_cadence_tir()
{
    return this->level_actuel_cadence_de_tir ;
}

/**
 * @brief Armes::get_level_max_cadence_tir getter de level_max_cadence_de_tir
 * @return le nombre de fois que peut être amélioré l'arme avec l'option cadence de tir
 */

int Armes::get_level_max_cadence_tir()
{
    return this->level_max_cadence_de_tir ;
}

/**
 * @brief Armes::get_level_actuel_nombre_balle_tire getter de level_actuel_nombre_de_balle_tire
 * @return le nombre d'amélioration de type nombre de balles tirées effectué sur l'arme
 */

int Armes::get_level_actuel_nombre_balle_tire()
{
    return this->level_actuel_nombre_de_balle_tire ;
}

/**
 * @brief Armes::get_level_max_nombre_balle_tire getter de level_max_nombre_de_balle_tire
 * @return le nombre de fois que peut être amélioré l'arme avec l'option nombre de balles tirées
 */

int Armes::get_level_max_nombre_balle_tire()
{
    return this->level_max_nombre_de_balle_tire ;
}

#endif // armes_cpp
