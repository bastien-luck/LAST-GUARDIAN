#ifndef boss_summoner_cpp
#define boss_summoner_cpp

#include "boss_summoner.h"
#include "mob_mushroom.h"
#include "mob_skeleton.h"
#include "mob_slime.h"
#include "frame.h"

/**
 * @brief Boss_summoner::Boss_summoner constructeur de la classe Boss_summoner
 * @param scene la scene où se déroule le jeu
 */

Boss_summoner::Boss_summoner( QGraphicsScene *scene ) : Boss( scene , 240 , 240 , 45 , 132 , 93 , 54 , 5 , 500 , 0 , 0 , 1 , 700 , "summoner" , 12 , 14 , 12 , 0 , 6 )
{
    /* stats :
     * largeur : 80*3 = 240
     * hauteur : 80*3 = 240
     * largeur hitbox moyenne : 15*3 = 45
     * hauteur hitbox moyenne : 44*3 = 132
     * décalage de l'animation avec la taille du sprite en x : 31*3 = 93
     * décalage de l'animation avec la taille du sprite en y : 18*3 = 54
     * nombre de phase : 5
     * pv : 500
     * delais : 0 // le boss est le dernier mob du niveau donc bon...
     * degat : 0 // on verra plus tard si le summoner ne fait pas que summon des mobs
     * vitesse : 1
     * portée d'attaque : 700
     * nom du monstre : summoner
     * nombre d'image pour l'animation du mouvement : 12
     * nombre d'image pour l'animation d'attaque : 14
     * nombre d'image pour l'animation de mort : 12
     * numero de l'image où l'attaque a lieu : 0
     * nombre de frames pour changer l'image courante : 6
    */
    this->mob_spawned = new QVector<Ennemis*>() ;
    this->num_image_action_speciale_actuel = 0 ;
    this->nb_image_action_speciale = 10 ;
    this->delais_action_speciale = 13 ;
    this->delais_action_speciale_actuel = 7 ; // portail 3° sprite et apparition mob depuis le portail 7° sprite
    this->portail_invocation = new QVector<QGraphicsPixmapItem*>() ; // faire cette méthode évite de faire des delete / new à chaque invocation et donc réduit la charge processeur
    this->portail_invocation->append( new QGraphicsPixmapItem() ) ;
    this->largeur_sprite_portail = 60 ;
    this->hauteur_sprite_portail = 66 ;
}

/**
 * @brief Boss_summoner::attack_ennemi override de la fonction attack_ennemi de Ennemis qui implémente la partie invocation du boss
 * @param batiment base du joueur
 */

void Boss_summoner::attack_ennemi( Base *batiment )
{
    if ( this->etat_actuel == 0 )
    {
        this->num_image_actuelle = 0 ;
        this->etat_actuel++ ;
    }
    if ( this->delais_change_sprite_restant > 0 )
    {
        this->delais_change_sprite_restant-- ;
    }
    else
    {
        this->delais_change_sprite_restant = this->delais_change_sprite ;
        if ( this->num_image_actuelle < this->nb_images_attaque-1 )
        {
            if ( this->num_image_damage_on_attack_sprite == this->num_image_actuelle )
            {
                (*batiment) - this->degat_attaque ;
            }
            this->num_image_actuelle++ ;
        }
        else
        {
            this->num_image_actuelle = 0 ;
        }
        if ( this->delais_action_speciale_actuel == 0 )
        {
            this->summon_mob() ;
            this->delais_action_speciale_actuel = this->delais_action_speciale ;
        }
        else
        {
            this->delais_action_speciale_actuel-- ;
        }

        if ( 1 < this->num_image_actuelle && this->num_image_actuelle < 13 )
        {
            if ( this->num_image_actuelle == 2 )
            {
                int pos_z_selon_pos_y = 0 ;
                int check_phase_modifier = int (fmod( this->get_nb_phase_boss()*(qreal(this->point_de_vie_total) - qreal(this->point_de_vie_actuel))/qreal(this->point_de_vie_total) , this->get_nb_phase_boss() )) ;
                if ( this->numero_phase_actuelle != check_phase_modifier )
                {
                    for ( int i = 0 ; i < check_phase_modifier - this->numero_phase_actuelle ; i++ ) // permet de skip plusieurs barre de vie dans le cas où on fait très mal au boss lors de sa phase de mouvement
                    {
                        this->portail_invocation->append( new QGraphicsPixmapItem() ) ;
                    }
                    this->numero_phase_actuelle = check_phase_modifier ;
                }
                for ( QVector<QGraphicsPixmapItem*>::iterator portail_cast = this->portail_invocation->begin() ; portail_cast != this->portail_invocation->end() ; ++portail_cast )
                { // pas pratique de gérer la position des invocations selon la position du portail mais pas impossible au final
                    pos_z_selon_pos_y = (qrand() % ( Frame::hauteur_spawn_max - Frame::hauteur_spawn_min - 29 )) + Frame::hauteur_spawn_min - this->hauteur_sprite_portail + 20 ;
                    (*portail_cast)->setPos( (qrand() % int (Frame::largeur_ecran * 0.5) ) + 300 , pos_z_selon_pos_y ) ;
                    (*portail_cast)->setZValue( pos_z_selon_pos_y + this->hauteur_sprite_portail + 1 ) ; // + 1 car le portail doit rester devant le mob invoqué
                    this->scene->addItem( (*portail_cast) ) ;
                    (*portail_cast)->setVisible( true ) ;
                }
            }
            else if ( this->num_image_actuelle == 12 )
            {
                for ( QVector<QGraphicsPixmapItem*>::iterator portail_cast = this->portail_invocation->begin() ; portail_cast != this->portail_invocation->end() ; ++portail_cast )
                {
                    this->scene->removeItem( (*portail_cast) ) ;
                    (*portail_cast)->setVisible( false ) ;
                }
            }
            else
            {
                for ( QVector<QGraphicsPixmapItem*>::iterator portail_cast = this->portail_invocation->begin() ; portail_cast != this->portail_invocation->end() ; ++portail_cast )
                {
                    (*portail_cast)->setPixmap( QPixmap( ":/images/images_jeu/boss/summoner/summoner_portal_" + QString::number(this->num_image_actuelle - 2) + ".png" ).scaled( 60 , 69 , Qt::KeepAspectRatio ) ) ;
                }
            }
        }
        this->setPixmap( QPixmap( ":/images/images_jeu/" + this->type_ennemi + "/" + this->sprite_ennemi + "/" + this->sprite_ennemi + "_summon_" + QString::number(this->num_image_actuelle) + ".png" ).scaled( this->largeur_sprite_ennemi , this->hauteur_sprite_ennemi , Qt::KeepAspectRatio ) ) ;
    }
}

/**
 * @brief Boss_summoner::die_ennemi override de la fonction die_ennemis de Ennemis qui permet de supprimer les portails visible à la mort du boss
 */

void Boss_summoner::die_ennemi()
{
    this->Ennemis::die_ennemi() ; // au moins pour la mort, il n'est pas obligé de tout réécrire la méthode pour la modification à faire
    for ( QVector<QGraphicsPixmapItem*>::iterator portail_cast = this->portail_invocation->begin() ; portail_cast != this->portail_invocation->end() ; ++portail_cast )
    {
        if ( (*portail_cast)->isVisible() == true )
        {
            this->scene->removeItem( (*portail_cast) ) ;
            delete (*portail_cast) ;
            (*portail_cast) = nullptr ;
            this->portail_invocation->erase( portail_cast ) ;
            --portail_cast ;
        }
    }
}

/**
 * @brief Boss_summoner::do_action permet d'éguiller vers l'action que doit faire le boss summoner selon la situation (mal implémenté par manque de temps car tout est spécifique à cette classe sans en être une générique)
 * @param batiment base du joueur
 */

void Boss_summoner::do_action( Base *batiment )
{
    if ( this->mort() == true )
    {
        this->die_ennemi() ;
        this->kill_all_summon_on_death() ;
    }
    else if ( this->x() > batiment->x() + this->portee_attaque )
    {
        this->move_ennemi() ;
        if ( this->x() <= batiment->x() + this->portee_attaque )
        {
            this->delais_change_sprite_restant = this->delais_change_sprite ; // ne pas oublier de reset le compteur pour éviter que le premier sprite ne se fini trop rapidement
        }
    }
    else
    {
        this->attack_ennemi( batiment ) ;
    }
}

/**
 * @brief Boss_summoner::summon_mob permet au summoner d'invoquer des ennemis (aurait dû utiliser la fonction globale spawn_ennemi mais je n'ai pas fait les modifications nécessaire pour)
 */

void Boss_summoner::summon_mob() // j'étais parti sur une solution avec un type de spawn fixe mais vu qu'il fallait modifier plusieurs endroits si l'on voulait changer le nombre d'ennemi qui spawnait, j'ai modifié en random summon
{
    for ( QVector<QGraphicsPixmapItem*>::iterator portail_cast = this->portail_invocation->begin() ; portail_cast != this->portail_invocation->end() ; ++portail_cast )
    {
        switch( qrand() % 3 )
        {
        case 0 :
            this->mob_spawned->append( new Mob_slime( this->scene , int ((*portail_cast)->x() + (this->largeur_sprite_portail * 0.5)) , int ((*portail_cast)->y() + this->hauteur_sprite_portail) ) ) ;
            break ;
        case 1 :
            this->mob_spawned->append( new Mob_mushroom( this->scene , int ((*portail_cast)->x() + (this->largeur_sprite_portail * 0.5)) , int ((*portail_cast)->y() + this->hauteur_sprite_portail) ) ) ;
            break ;
        case 2 :
            this->mob_spawned->append( new Mob_skeleton( this->scene , int ((*portail_cast)->x() + (this->largeur_sprite_portail * 0.5)) , int ((*portail_cast)->y() + this->hauteur_sprite_portail) ) ) ;
            break ;
        default :
            break ;
        }
    }
}

/**
 * @brief Boss_summoner::get_invocation getter de mob_spawned
 * @return le vecteur contenant tous les ennemis qu'a invoqué le summoner
 */

QVector<Ennemis*> *Boss_summoner::get_invocation()
{
    return this->mob_spawned ;
}

/**
 * @brief Boss_summoner::kill_all_summon_on_death permet de faire mourir toutes les invocation lorsque le boss meurt
 */

void Boss_summoner::kill_all_summon_on_death()
{
    for ( QVector<Ennemis*>::iterator invocation = this->mob_spawned->begin() ; invocation != this->mob_spawned->end() ; ++invocation )
    {
        (*invocation)->instant_death() ;
    }
}

#endif // boss_sumoner_cpp
