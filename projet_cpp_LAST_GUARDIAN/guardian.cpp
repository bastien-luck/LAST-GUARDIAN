#ifndef guardian_cpp
#define guardian_cpp

#include "guardian.h"
#include "weapon_blaster_basique.h"
#include "weapon_blaster_corrosif.h"
#include "weapon_blaster_sniper.h"
#include "weapon_blaster_explosif.h"
#include "weapon_blaster_minigun.h"
#include "frame.h"

/**
 * @brief Guardian::Guardian constructeur de la classe Guardian
 * @param scene la scene où se déroule le jeu
 */

Guardian::Guardian( QGraphicsScene *scene )
{
    this->scene = scene ;
    this->hauteur_sprite_guardian = 77 ;
    this->largeur_sprite_guardian = 45 ;
    this->vitesse = 5 ;
    this->armes_possede = new QVector<Armes*>() ;
    this->armes_possede->append( new Weapon_blaster_basique( this->scene ) ) ;
    this->arme_equipe = this->armes_possede->at(0) ;
    this->sprite_guardian = "guardian_test" ; // faire des sprites d'armes qui se placent bien de base (faire du vide)
    this->setPos( 20 , (Frame::hauteur_spawn_max - Frame::hauteur_spawn_min - this->hauteur_sprite_guardian) * 0.5 + Frame::hauteur_spawn_min ) ; // centre le joueur au milieu de la zone de jeu

    // draw the image
    this->setPixmap(QPixmap( ":/images/images_jeu/" + this->sprite_guardian + ".png" ).scaled( this->largeur_sprite_guardian , this->hauteur_sprite_guardian , Qt::KeepAspectRatio ) ) ;
    this->scene->addItem( this ) ;
}

/**
 * @brief Guardian::get_arme_equipe getter de arme_equipe
 * @return l'arme que le joueur utilise
 */

Armes *Guardian::get_arme_equipe()
{
    return this->arme_equipe ;
}

/**
 * @brief Guardian::get_hauteur_sprite_guardian getter de hauteur_sprite_guardian
 * @return la hauteur de l'image du joueur
 */

int Guardian::get_hauteur_sprite_guardian()
{
    return this->hauteur_sprite_guardian ;
}

/**
 * @brief Guardian::move_up permet au joueur de se déplacer vers le haut
 */

void Guardian::move_up()
{
    if ( this->y() > Frame::hauteur_spawn_min - this->hauteur_sprite_guardian + 20 )
    {
        this->setPos( this->x() , this->y() - this->vitesse ) ;
    }
}

/**
 * @brief Guardian::move_down permet au joueur de se déplacer vers le bas
 */

void Guardian::move_down()
{
    this->setPos( this->x() , this->y() + this->vitesse ) ;
}

/**
 * @brief Guardian::fabrique_arme permet au joueur d'avoir de nouvelle arme
 * @param id_new_arme id de l'arme à créer
 */

void Guardian::fabrique_arme( int id_new_arme )
{
    for ( QVector<Armes*>::iterator armes_dans_sac = this->armes_possede->begin() ; armes_dans_sac != this->armes_possede->end() ; ++armes_dans_sac )
    {
        if ( (*armes_dans_sac)->get_id_arme() == id_new_arme )
        {
            return ; // évite d'avoir plusieurs fois la même arme
        }
    }
    switch( id_new_arme )
    {
        case 1 :
            this->armes_possede->append( new Weapon_blaster_corrosif( this->scene ) ) ;
            break ;
        case 2 :
            this->armes_possede->append( new Weapon_blaster_sniper( this->scene ) ) ;
            break ;
        case 3 :
            this->armes_possede->append( new Weapon_blaster_explosif( this->scene ) ) ;
            break ;
        case 4 :
            this->armes_possede->append( new Weapon_blaster_minigun( this->scene ) ) ;
            break ;
        default :
            break ;
    }
}

/**
 * @brief Guardian::change_arme_equipe permet au joueur de changer son arme actuellement équipé
 * @param id_arme_choisie l'id de l'arme que le joueur veut utiliser
 */

void Guardian::change_arme_equipe( int id_arme_choisie )
{
    for ( QVector<Armes*>::iterator armes_dans_sac = this->armes_possede->begin() ; armes_dans_sac != this->armes_possede->end() ; ++armes_dans_sac )
    {
        if ( (*armes_dans_sac)->get_id_arme() == id_arme_choisie )
        {
            this->arme_equipe = this->armes_possede->at( id_arme_choisie ) ;
            this->arme_equipe->delais_changement_arme() ;
        }
    }
}

/**
 * @brief Guardian::get_nb_armes_possede getter de armes_possede->size()
 * @return le nombre d'arme que le joueur possède
 */

int Guardian::get_nb_armes_possede()
{
    return this->armes_possede->size() ;
}

#endif // guardian_cpp
