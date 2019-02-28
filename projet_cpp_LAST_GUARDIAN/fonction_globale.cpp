#ifndef fonction_globale_cpp
#define fonction_globale_cpp

#include <iostream>
#include "fonction_globale.h"
#include "frame.h"
#include "mob_slime.h"
#include "mob_skeleton.h"
#include "mob_mushroom.h"
#include "boss_summoner.h"

using namespace std ;

// ces fonctions ne s'appellent pas à partir d'un objet
/*
exemple : (exemple d'appel : init_niveau(10) ; )
*/

/**
 * @brief init_niveau genre de sous constructeur de la classe Niveau... oui ce n'est pas malin x)
 * @param num_lv numéro du niveau actuel
 * @return le niveau rempli de la liste des ennemis à spawn
 */

Niveau *init_niveau( int num_lv )
{
    Niveau *ennemis_du_niveau = new Niveau( num_lv ) ;
    int random_ennemi ;
    switch( num_lv )
    {
    case 1 :
        for ( int i = 0 ; i < 10  ; i++ )
        {
            ennemis_du_niveau->get_spawn_order()->append( 0 ) ;
        }
        return ennemis_du_niveau ;
    case 2 :
        for ( int i = 0 ; i < 20  ; i++ )
        {
            random_ennemi = qrand() % 2 ;
            ennemis_du_niveau->get_spawn_order()->append( random_ennemi ) ;
        }
        return ennemis_du_niveau ;
    case 3 :
        for ( int i = 0 ; i < 30  ; i++ )
        {
            random_ennemi = qrand() % 3 ;
            ennemis_du_niveau->get_spawn_order()->append( random_ennemi ) ;
        }
        return ennemis_du_niveau ;
    case 4 :
        for ( int i = 0 ; i < 40  ; i++ )
        {
            random_ennemi = qrand() % 3 ;
            ennemis_du_niveau->get_spawn_order()->append( random_ennemi ) ;
        }
        ennemis_du_niveau->get_spawn_order()->append( 3 ) ;
        return ennemis_du_niveau ;
    default :
        return nullptr ;
    }
}

/**
 * @brief spawn_ennemi permet d'ajouter un ennemi dans le jeu
 * @param scene la scene où se déroule le jeu
 * @param id_ennemi id du type de l'ennemi
 * @return l'ennemi fraichement créé
 */

Ennemis *spawn_ennemi( QGraphicsScene *scene , int id_ennemi )
{
    switch( id_ennemi )
    {
    case 0 :
        return new Mob_slime( scene ) ;
    case 1 :
        return new Mob_mushroom( scene ) ;
    case 2 :
        return new Mob_skeleton( scene ) ;
    case 3 :
        return new Boss_summoner( scene ) ;
    default :
        return nullptr ;
    }
}

/**
 * @brief collision_ennemi_contre_munition permet de savoir si un projectile a touché un ennemi
 * @param mob l'ennemi à vérifier
 * @param ammo le projectile à vérifier
 * @return true si les deux se touchent
 */

bool collision_ennemi_contre_munition( Ennemis *mob , Projectiles *ammo )
{ // c'était plus simple avec l'hitbox ronde mais ça faisait bizarre dans certains cas (mob ou balle allongé)
    int ligne_gauche_mob_x = int ( mob->x() + mob->get_decalage_x_hitbox_et_sprites_ennemi() ) ;
    int ligne_droit_mob_x = int ( ligne_gauche_mob_x + mob->get_largeur_hitbox_ennemi() ) ;
    int ligne_haut_mob_y = int ( mob->y() + mob->get_decalage_y_hitbox_et_sprites_ennemi() ) ;
    int ligne_bas_mob_y = int ( ligne_haut_mob_y + mob->get_hauteur_hitbox_ennemi() ) ;
    int ligne_gauche_ammo_x = int ( ammo->x() + ammo->get_decalage_x_hitbox_et_sprites_balle() ) ;
    int ligne_droit_ammo_x = int ( ligne_gauche_ammo_x + ammo->get_largeur_hitbox_balle() ) ;
    int ligne_haut_ammo_y = int ( ammo->y() + ammo->get_decalage_y_hitbox_et_sprites_balle() ) ;
    int ligne_bas_ammo_y = int ( ligne_haut_ammo_y + ammo->get_hauteur_hitbox_balle() ) ;
    return collision_entre_deux_objets( ligne_gauche_mob_x , ligne_droit_mob_x , ligne_haut_mob_y , ligne_bas_mob_y , ligne_gauche_ammo_x , ligne_droit_ammo_x , ligne_haut_ammo_y , ligne_bas_ammo_y ) ;
}

/**
 * @brief collision_ennemi_contre_explosion permet de savoir si une explosion a touché un ennemi
 * @param mob l'ennemi à vérifier
 * @param explosive l'explosion à vérifier
 * @return true si les deux se touchent
 */

bool collision_ennemi_contre_explosion( Ennemis *mob , Explosion *explosive )
{
    int ligne_gauche_mob_x = int ( mob->x() + mob->get_decalage_x_hitbox_et_sprites_ennemi() ) ;
    int ligne_droit_mob_x = int ( ligne_gauche_mob_x + mob->get_largeur_hitbox_ennemi() ) ;
    int ligne_haut_mob_y = int ( mob->y() + mob->get_decalage_y_hitbox_et_sprites_ennemi() ) ;
    int ligne_bas_mob_y = int ( ligne_haut_mob_y + mob->get_hauteur_hitbox_ennemi() ) ;
    int ligne_gauche_explosive_x = int ( explosive->x() + explosive->get_decalage_x_hitbox_et_sprites_bombe() ) ;
    int ligne_droit_explosive_x = int ( ligne_gauche_explosive_x + explosive->get_largeur_hitbox_bombe() ) ;
    int ligne_haut_explosive_y = int ( explosive->y() + explosive->get_decalage_y_hitbox_et_sprites_bombe() ) ;
    int ligne_bas_explosive_y = int ( ligne_haut_explosive_y + explosive->get_hauteur_hitbox_bombe() ) ;
    return collision_entre_deux_objets( ligne_gauche_mob_x , ligne_droit_mob_x , ligne_haut_mob_y , ligne_bas_mob_y , ligne_gauche_explosive_x , ligne_droit_explosive_x , ligne_haut_explosive_y , ligne_bas_explosive_y ) ;
}

/**
 * @brief collision_entre_deux_objets vérifie qu'un objet numéro 1 a une de ses parties à l'intérieur d'un obet numéro 2
 * @param ligne_gauche_objet_1_x ligne vertical délimitant la position x minimum de la hitbox de l'objet 1
 * @param ligne_droite_objet_1_x ligne vertical délimitant la position x maximum de la hitbox de l'objet 1
 * @param ligne_haut_objet_1_y ligne vertical délimitant la position y minimum de la hitbox de l'objet 1
 * @param ligne_bas_objet_1_y ligne vertical délimitant la position y maximum de la hitbox de l'objet 1
 * @param ligne_gauche_objet_2_x ligne vertical délimitant la position x minimum de la hitbox de l'objet 2
 * @param ligne_droite_objet_2_x ligne vertical délimitant la position x maximum de la hitbox de l'objet 2
 * @param ligne_haut_objet_2_y ligne vertical délimitant la position y minimum de la hitbox de l'objet 2
 * @param ligne_bas_objet_2_y ligne vertical délimitant la position y maximum de la hitbox de l'objet 2
 * @return true si les deux se touchent
 */

bool collision_entre_deux_objets( int ligne_gauche_objet_1_x , int ligne_droite_objet_1_x , int ligne_haut_objet_1_y , int ligne_bas_objet_1_y , int ligne_gauche_objet_2_x , int ligne_droite_objet_2_x , int ligne_haut_objet_2_y , int ligne_bas_objet_2_y )
{ //picote beaucoup car il faut vérifier que l'objet le plus petit est à l'intérieur de l'objet le plus grand (une même catégorie d'objet pouvant être soit l'un soit l'autre par rapport à certains cas, il n'est pas possible d'adapter le test pour ces comparaisons)
    if ( (( (ligne_gauche_objet_1_x < ligne_gauche_objet_2_x && ligne_gauche_objet_2_x < ligne_droite_objet_1_x) ||  (ligne_gauche_objet_1_x < ligne_droite_objet_2_x && ligne_droite_objet_2_x < ligne_droite_objet_1_x) )
         && ( (ligne_haut_objet_1_y < ligne_haut_objet_2_y && ligne_haut_objet_2_y < ligne_bas_objet_1_y) || (ligne_haut_objet_1_y < ligne_bas_objet_2_y && ligne_bas_objet_2_y < ligne_bas_objet_1_y) ))
         || (( (ligne_gauche_objet_2_x < ligne_gauche_objet_1_x && ligne_gauche_objet_1_x < ligne_droite_objet_2_x) ||  (ligne_gauche_objet_2_x < ligne_droite_objet_1_x && ligne_droite_objet_1_x < ligne_droite_objet_2_x) )
         && ( (ligne_haut_objet_2_y < ligne_haut_objet_1_y && ligne_haut_objet_1_y < ligne_bas_objet_2_y) || (ligne_haut_objet_2_y < ligne_bas_objet_1_y && ligne_bas_objet_1_y < ligne_bas_objet_2_y) )) )
    {
        return true ;
    }
    else
    {
        return false ;
    }
}

/**
 * @brief gestion_ennemis permet de gérer tout ce qui est lié aux ennemis : actions, delete, invocation, collision avec des projectiles
 * @param batiment base du joueur
 * @param ennemis_spawned vecteur contenant les ennemis du niveau ou les invocation d'un ennemi
 * @param bullet_fired vecteur contenant les projectiles visible sur l'écran qui sont tirés par le joueur
 * @param explosion_en_cours vecteur contenant les explosions qui sont en cours d'exécution
 * @return le nombre d'ennemi mort lors de cette frame
 */

int gestion_ennemis( Base *batiment , QVector<Ennemis*> *ennemis_spawned , QVector<Projectiles*> *bullet_fired , QVector<Explosion*> *explosion_en_cours )
{
    int ennemi_en_moins = 0 ;
    for ( int i = 0 ; i < ennemis_spawned->size() ; i++ )
    {
        ennemis_spawned->at(i)->do_action( batiment ) ;

        if ( ennemis_spawned->at(i)->get_name() == "summoner" ) // éviter les summoner qui invoque des summoner et la pile de récursivité ne devrait pas devenir folle
        {
            gestion_ennemis( batiment , ennemis_spawned->at(i)->get_invocation() , bullet_fired , explosion_en_cours ) ;
        }

        if ( ennemis_spawned->at(i)->mort() == true )
        {
            if ( ennemis_spawned->at(i)->a_delete() == true ) // delete l'ennemi dès que son animation de mort est finie
            {
                delete ennemis_spawned->takeAt(i) ;
                i-- ;
                ennemi_en_moins++ ;
            }
        }
        else // permmet de tirer à travers les animations de mort
        {
            for ( QVector<Projectiles*>::iterator bullet_checked = bullet_fired->begin() ; bullet_checked != bullet_fired->end() ; ++bullet_checked )
            {
                if ( collision_ennemi_contre_munition( ennemis_spawned->at(i) , (*bullet_checked) ) )
                {
                    if ( (*bullet_checked)->get_aoe() > 0 )
                    {
                        explosion_en_cours->append( (*bullet_checked)->explose() ) ; // créer l'explosion pour qu'elle soit jouée lors des frames suivantes
                        for ( QVector<Ennemis*>::iterator ennemi_hit_by_explosion = ennemis_spawned->begin() ; ennemi_hit_by_explosion != ennemis_spawned->end() ; ++ennemi_hit_by_explosion )
                        { // pas optimisé certes mais temps que l'écran n'explose pas de partout avec plein d'ennemis présents, cela devrait ne pas trop géner
                            if ( collision_ennemi_contre_explosion( (*ennemi_hit_by_explosion) , explosion_en_cours->last() ) )
                            {
                                (*ennemi_hit_by_explosion)->get_hit( (*bullet_checked) ) ;
                            }
                        }
                    }
                    else
                    {
                        ennemis_spawned->at(i)->get_hit( (*bullet_checked) ) ;
                    }
                    if ( (*bullet_checked)->transperce() == false )
                    {
                        delete (*bullet_checked) ;
                        (*bullet_checked) = nullptr ;
                        bullet_checked = bullet_fired->erase( bullet_checked ) ;
                        --bullet_checked ;
                    }
                }
            }
            ennemis_spawned->at(i)->get_damaged_by_poison() ; // si l'ennemi n'est pas empoisonné, alors cette ligne ne fait rien
        }
    }
    return ennemi_en_moins ;
}

#endif //fonction_globale_cpp
