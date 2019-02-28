#ifndef ennemis_h
#define ennemis_h

#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "barre_de_vie.h"
#include "base.h"
#include "projectiles.h"

using namespace std ;

/**
 * @brief The Ennemis class define the behavior of all the monster
 */
class Ennemis : virtual public QObject , virtual public QGraphicsPixmapItem
{
    Q_OBJECT
    // variables
protected :
    QGraphicsScene *scene ;
    int largeur_sprite_ennemi ;
    int hauteur_sprite_ennemi ;
    int largeur_hitbox_ennemi ; // utile lorsque le sprite part un peu dans tous les sens
    int hauteur_hitbox_ennemi ;
    int declage_x_hitbox_et_sprite_ennemi ;
    int declage_y_hitbox_et_sprite_ennemi ;
    int point_de_vie_actuel ;
    int point_de_vie_total ;
    int temps_stop_spawn ; // temps minimum avant le spawn d'un nouvel ennemi ( != delais dans niveau )
    int degat_attaque ;
    qreal vitesse_x ;
    int portee_attaque ;
    QString type_ennemi ;
    QString sprite_ennemi ;
    int nb_images_mouvement ;
    int nb_images_attaque ;
    int nb_images_mort ;
    int num_image_actuelle ;
    int num_image_damage_on_attack_sprite ;
    int delais_change_sprite ; // le nombre de frame où on ne change pas le sprite de l'ennemi
    int delais_change_sprite_restant ;
    int etat_actuel ; // move = 0 , attack = 1 , die = 2 , à delete = 3 (permet de ne reset qu'une seule fois num_image_actuelle)
    Barre_de_vie *affiche_pv ;
    int is_poisoned ; // 0 : pas empoisonné, 1+ : dégat du poison par thick
    int delais_poison ;
    int delais_poison_actuel ;

    // vitesse_y sera dans un héritage !

    // méthodes
public :
    bool mort() ;
    Barre_de_vie *get_hp() ;
    void move_ennemi() ;
    virtual void attack_ennemi( Base *batiment ) ;
    virtual void die_ennemi() ;
    int get_hauteur_ennemi() ;
    int get_largeur_ennemi() ;
    int get_hauteur_hitbox_ennemi() ;
    int get_largeur_hitbox_ennemi() ;
    int get_decalage_x_hitbox_et_sprites_ennemi() ;
    int get_decalage_y_hitbox_et_sprites_ennemi() ;
    void get_damaged( int degat_recu ) ;
    void get_damaged_by_poison() ;
    void get_hit ( Projectiles *ammo_hit ) ;
    int pv_restant() ;
    int get_delais_spawn() ;
    bool a_delete() ;
    QString get_type() ;
    virtual Barre_de_vie *get_hp_boss() ;
    virtual int get_nb_phase_boss() ;
    int get_range() ;
    virtual void do_action( Base *batiment ) ;
    QString get_name() ; // me sauve un peu pour le summoning en action spéciale
    virtual QVector<Ennemis*> *get_invocation() ;
    void instant_death() ;

    // constructeurs / destructeurs
public:
    Ennemis( QGraphicsScene *scene , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , int pv_tot , int delais , int degat , qreal speed , int range , QString type_ennemi , QString nom , int nb_img_move , int nb_img_attack , int nb_img_die , int num_img_dmg , int delais_sprite , int summon_pos_x = 0 , int summon_pos_y = 0 ) ;
    ~Ennemis()
    {
        this->scene->removeItem( this ) ;
        delete this->affiche_pv ;
    }
} ;

#endif // ennemis_h
