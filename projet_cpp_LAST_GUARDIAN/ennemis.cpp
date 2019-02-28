#ifndef ennemis_cpp
#define ennemis_cpp

#include "ennemis.h"
#include "frame.h"

/**
 * @brief Ennemis::Ennemis
 * @param scene la scene où se déroule le jeu
 * @param largeur largeur de l'image de l'ennemi
 * @param hauteur hauteur de l'image de l'ennemi
 * @param largeur_hitbox largeur de la hitbox de l'image de l'ennemi
 * @param hauteur_hitbox hauteur de la hitbox de l'image de l'ennemi
 * @param decalage_hitbox_x largeur de l'image avant d'atteindre la hitbox réelle de l'ennemi
 * @param decalage_hitbox_y hauteur de l'image avant d'atteindre la hitbox réelle de l'ennemi
 * @param pv_tot nombre de pv de l'ennemi
 * @param delais nombre de frame à attendre avant le spawn du prochain ennemi
 * @param degat dégat que fait l'ennemi à chaque attaque
 * @param speed vitesse de mouvement de l'ennemi
 * @param range distance d'attaque de l'ennemi
 * @param type_ennemi boss ou mob pour savoir dans quel dossier chercher les images du sprite correspondant
 * @param nom nom de l'ennemi pour savoir dans quel dossier chercher ses sprites
 * @param nb_img_move nombre d'image de l'animation complete de déplacement de l'ennemi
 * @param nb_img_attack nombre d'image de l'animation complete d'attaque de l'ennemi
 * @param nb_img_die nombre d'image de l'animation complete de mort de l'ennemi
 * @param num_img_dmg numero de l'image où l'ennemi inflige des dégat à la base
 * @param delais_sprite nombre de frame entre deux changement d'image
 * @param summon_pos_x position horizontal forcée quand l'ennemi est une invocation
 * @param summon_pos_y position vertical forcée quand l'ennemi est une invocation
 */

Ennemis::Ennemis( QGraphicsScene *scene , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , int pv_tot , int delais , int degat , qreal speed , int range , QString type_ennemi , QString nom , int nb_img_move , int nb_img_attack , int nb_img_die , int num_img_dmg , int delais_sprite , int summon_pos_x , int summon_pos_y )
{
    this->scene = scene ;
    this->largeur_sprite_ennemi = largeur ;
    this->hauteur_sprite_ennemi = hauteur ;
    this->largeur_hitbox_ennemi = largeur_hitbox ;
    this->hauteur_hitbox_ennemi = hauteur_hitbox ;
    this->declage_x_hitbox_et_sprite_ennemi = decalage_hitbox_x ;
    this->declage_y_hitbox_et_sprite_ennemi = decalage_hitbox_y ;
    this->point_de_vie_actuel = pv_tot ;
    this->point_de_vie_total = pv_tot ;
    this->temps_stop_spawn = delais ;
    this->degat_attaque = degat ;
    this->vitesse_x = speed ;
    this->portee_attaque = range ;
    this->type_ennemi = type_ennemi ;
    this->sprite_ennemi = nom ;
    this->nb_images_mouvement = nb_img_move ;
    this->nb_images_attaque = nb_img_attack ;
    this->nb_images_mort = nb_img_die ;
    this->num_image_actuelle = 0 ;
    this->num_image_damage_on_attack_sprite = num_img_dmg ;
    this->delais_change_sprite = delais_sprite ;
    this->delais_change_sprite_restant = delais_sprite ;
    this->etat_actuel = 0 ;
    this->is_poisoned = 0 ;
    this->delais_poison = 60 ;
    this->delais_poison_actuel = this->delais_poison ;
    int pos_z_selon_pos_y = 0 ; // manipulation permettant de toujours mettre le mob plus bas en dessous d'un mob plus haut... sinon adieu la perspective (déjà qu'elle n'est pas énorme... x) )
    if ( this->type_ennemi == "mob" )
    {
        if ( summon_pos_x == 0 )
        {
            pos_z_selon_pos_y = (qrand() % ( Frame::hauteur_spawn_max - Frame::hauteur_spawn_min - 29 )) + Frame::hauteur_spawn_min - this->hauteur_sprite_ennemi + 20 ;
            this->setPos( Frame::largeur_ecran , pos_z_selon_pos_y ) ;
            this->setZValue( pos_z_selon_pos_y + this->hauteur_sprite_ennemi ) ; // peut faire bizarre si un ennemi vole haut du bas de son sprite mais il faut quand même que le sprite soit visible au bon endroit lorsqu'il est au sol donc bon...
        }
        else
        {
            this->setPos( summon_pos_x - this->declage_x_hitbox_et_sprite_ennemi - (this->largeur_hitbox_ennemi * 0.5) , summon_pos_y - this->hauteur_sprite_ennemi ) ;
            this->setZValue( summon_pos_y ) ;
        }
    }
    else
    {
        pos_z_selon_pos_y = int( Frame::hauteur_spawn_min + (Frame::hauteur_spawn_max-Frame::hauteur_spawn_min + this->hauteur_hitbox_ennemi)*0.5 - this->hauteur_sprite_ennemi ) ;
        this->setPos( Frame::largeur_ecran , pos_z_selon_pos_y ) ;
        this->setZValue( pos_z_selon_pos_y + this->hauteur_sprite_ennemi ) ;
    }
    this->affiche_pv = new Barre_de_vie( this->scene , this->x()+this->declage_x_hitbox_et_sprite_ennemi , this->y()+this->declage_y_hitbox_et_sprite_ennemi+this->hauteur_hitbox_ennemi , this->largeur_hitbox_ennemi ) ;

    // draw the image on a special state
    this->setPixmap( QPixmap( ":/images/images_jeu/" + this->type_ennemi + "/" + this->sprite_ennemi + "/" + this->sprite_ennemi + "_move_" + QString::number(this->num_image_actuelle) + ".png" ).scaled( this->largeur_sprite_ennemi , this->hauteur_sprite_ennemi , Qt::KeepAspectRatio ) ) ;
    this->scene->addItem( this ) ;
}

/**
 * @brief Ennemis::mort permet de savoir si l'ennemi est mort
 * @return true si l'ennemi n'a plus de pv
 */

bool Ennemis::mort()
{
    return this->point_de_vie_actuel <= 0 ;
}

/**
 * @brief Ennemis::get_hp getter de affiche_pv
 * @return la barre de vie commune qu'a tous les ennemis
 */

Barre_de_vie *Ennemis::get_hp()
{
    return this->affiche_pv ;
}

/**
 * @brief Ennemis::move_ennemi permet à l'ennemi d'avancer et de jouer son animation de mouvement
 */

void Ennemis::move_ennemi()
{
    this->setPos( this->x() - this->vitesse_x , this->y() ) ;
    this->affiche_pv->move_hp( this->vitesse_x ) ;
    if ( this->delais_change_sprite_restant > 0 )
    {
        this->delais_change_sprite_restant-- ;
    }
    else
    {
        this->delais_change_sprite_restant = this->delais_change_sprite ;
        if ( this->num_image_actuelle < this->nb_images_mouvement-1 )
        {
            this->num_image_actuelle++ ;
        }
        else
        {
            this->num_image_actuelle = 0 ;
        }
        this->setPixmap(QPixmap( ":/images/images_jeu/" + this->type_ennemi + "/" + this->sprite_ennemi + "/" + this->sprite_ennemi + "_move_" + QString::number(this->num_image_actuelle) + ".png" ).scaled( this->largeur_sprite_ennemi , this->hauteur_sprite_ennemi , Qt::KeepAspectRatio )) ;
    }
}

/**
 * @brief Ennemis::attack_ennemi permet à l'ennemi d'infliger des dégats en plus de jouer son animation d'attaque
 * @param batiment base du joueur
 */

void Ennemis::attack_ennemi( Base *batiment )
{
    if ( this->etat_actuel == 0 )
    {
        this->num_image_actuelle = 0 ;
        this->etat_actuel = 1 ;
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
        this->setPixmap(QPixmap( ":/images/images_jeu/" + this->type_ennemi + "/" + this->sprite_ennemi + "/" + this->sprite_ennemi + "_attack_" + QString::number(this->num_image_actuelle) + ".png" ).scaled( this->largeur_sprite_ennemi , this->hauteur_sprite_ennemi , Qt::KeepAspectRatio )) ;
    }
}

/**
 * @brief Ennemis::die_ennemi permet de supprimer le visuel des barres de vies des ennemis lorsqu'ils meurent ainsi que de jouer leur animation de mort
 */

void Ennemis::die_ennemi()
{
    if ( this->etat_actuel == 0 || this->etat_actuel == 1 ) // un mob peut mourrir en mouvement ou lorsqu'il attaque
    {
        this->num_image_actuelle = 0 ;
        this->etat_actuel = 2 ;
        this->scene->removeItem( this->affiche_pv->get_barre_supp() ) ; // c'est plus réaliste/logique de supprimer la barre de vie lorsque l'ennemi joue son animation de mort
        this->scene->removeItem( this->affiche_pv->get_barre_actuel() ) ;
        if ( this->type_ennemi == "boss" )
        {
            this->scene->removeItem( this->get_hp_boss()->get_barre_supp() ) ;
            this->scene->removeItem( this->get_hp_boss()->get_barre_actuel() ) ;
        }
        this->delais_change_sprite_restant = this->delais_change_sprite ;
    }
    if ( this->delais_change_sprite_restant > 0 )
    {
        this->delais_change_sprite_restant-- ;
    }
    else
    {
        this->delais_change_sprite_restant = this->delais_change_sprite ;
        if ( this->num_image_actuelle < this->nb_images_mort-1 )
        {
            this->num_image_actuelle++ ;
        }
        else
        {
            this->etat_actuel = 3 ;
        }
        this->setPixmap( QPixmap( ":/images/images_jeu/" + this->type_ennemi + "/" + this->sprite_ennemi + "/" + this->sprite_ennemi + "_die_" + QString::number(this->num_image_actuelle) + ".png" ).scaled( this->largeur_sprite_ennemi , this->hauteur_sprite_ennemi , Qt::KeepAspectRatio ) ) ;
    }
}

/**
 * @brief Ennemis::get_hauteur_ennemi getter de hauteur_sprite_ennemi
 * @return la hauteur de l'image de l'ennemi
 */

int Ennemis::get_hauteur_ennemi()
{
    return this->hauteur_sprite_ennemi ;
}

/**
 * @brief Ennemis::get_largeur_ennemi getter de largeur_sprite_ennemi
 * @return la largeur de l'image de l'ennemi
 */

int Ennemis::get_largeur_ennemi()
{
    return this->largeur_sprite_ennemi ;
}

/**
 * @brief Ennemis::get_hauteur_hitbox_ennemi getter de hauteur_hitbox_ennemi
 * @return la hauteur de la hitbox de l'image de l'ennemi
 */

int Ennemis::get_hauteur_hitbox_ennemi()
{
    return this->hauteur_hitbox_ennemi ;
}

/**
 * @brief Ennemis::get_largeur_hitbox_ennemi getter de largeur_hitbox_ennemi
 * @return la largeur de la hitbox de l'image de l'ennemi
 */

int Ennemis::get_largeur_hitbox_ennemi()
{
    return this->largeur_hitbox_ennemi ;
}

/**
 * @brief Ennemis::get_decalage_x_hitbox_et_sprites_ennemi getter de declage_x_hitbox_et_sprite_ennemi
 * @return la largeur de l'image avant d'atteindre la hitbox réelle de l'ennemi
 */

int Ennemis::get_decalage_x_hitbox_et_sprites_ennemi()
{
    return this->declage_x_hitbox_et_sprite_ennemi ;
}

/**
 * @brief Ennemis::get_decalage_y_hitbox_et_sprites_ennemi getter de declage_y_hitbox_et_sprite_ennemi
 * @return la hauteur de l'image avant d'atteindre la hitbox réelle de l'ennemi
 */

int Ennemis::get_decalage_y_hitbox_et_sprites_ennemi()
{
    return this->declage_y_hitbox_et_sprite_ennemi ;
}

/**
 * @brief Ennemis::get_damaged permet de gérer la perte de pv de l'ennemi et de modifier l'affichage de sa/ses barres de vies en conséquence
 * @param degat_recu pv perdu par l'ennemi
 */

void Ennemis::get_damaged( int degat_recu )
{
    this->point_de_vie_actuel = this->point_de_vie_actuel - degat_recu ;
    this->affiche_pv->perte_pv( 1 - ((qreal(this->point_de_vie_total) - qreal(this->point_de_vie_actuel))/qreal(this->point_de_vie_total)) , this->is_poisoned > 0 ) ;
    if ( this->type_ennemi == "boss" )
    {
        this->get_hp_boss()->perte_pv( 1 - fmod( this->get_nb_phase_boss()*(qreal(this->point_de_vie_total) - qreal(this->point_de_vie_actuel))/qreal(this->point_de_vie_total) , 1 ) , this->is_poisoned > 0 , this->point_de_vie_actuel*this->get_nb_phase_boss() >= this->point_de_vie_total ) ;
    }
}

/**
 * @brief Ennemis::get_damaged_by_poison permet de gérer les dot de type poison
 */

void Ennemis::get_damaged_by_poison()
{
    if ( this->is_poisoned > 0 )
    {
        if ( this->delais_poison_actuel == 0 )
        {
            this->get_damaged( this->is_poisoned ) ;
            this->delais_poison_actuel = this->delais_poison ;
        }
        else
        {
            this->delais_poison_actuel-- ;
        }
    }
}

/**
 * @brief Ennemis::get_hit permet d'appliquer à l'ennemi les dommages associé au projectile avec lequel il est rentré en contact
 * @param ammo_hit le projectile qui a touché l'ennemi
 */

void Ennemis::get_hit( Projectiles *ammo_hit )
{
    if ( ammo_hit->get_degat_poison() > this->is_poisoned ) // si un jour il existe des armes avec différents niveau de poison...
    {
        this->is_poisoned = ammo_hit->get_degat_poison() ;
    }
    this->get_damaged( ammo_hit->get_degat() ) ;
}

/**
 * @brief Ennemis::pv_restant getter de point_de_vie_actuel
 * @return le nombre de pv qu'il reste à l'ennemi
 */

int Ennemis::pv_restant()
{
    return this->point_de_vie_actuel ;
}

/**
 * @brief Ennemis::get_delais_spawn getter de temps_stop_spawn
 * @return le nombre de frame où aucun ennemi ne peut spawn après celui ci (dépend de la résistance de l'ennemi)
 */

int Ennemis::get_delais_spawn()
{
    return this->temps_stop_spawn ;
}

/**
 * @brief Ennemis::a_delete permet de vérifier si un ennemi a fini de jouer son animation de mort ainsi que celles de ses invocations (s'il en invoque)
 * @return true si l'ennemi a fini son animation de mort et que toutes ses invocations sont supprimés
 */

bool Ennemis::a_delete()
{
    if ( this->sprite_ennemi == "summoner" )
    {
        if ( this->get_invocation()->size() > 0 )
        {
            return false ; // on vérifie que les mobs invoqués sont bien delete avant de delete l'invocateur
        }
    }
    return this->etat_actuel == 3 ;
}

/**
 * @brief Ennemis::get_type getter de type_ennemi
 * @return boss ou mob pour savoir dans quel dossier chercher ses sprites
 */

QString Ennemis::get_type()
{
    return this->type_ennemi ;
}

/**
 * @brief Ennemis::get_hp_boss permet de ne pas définir cette fonction dans les sous classes qui n'en ont pas besoin
 * @return un pointeur null
 */

Barre_de_vie *Ennemis::get_hp_boss() // la définition d'une méthode virtuelle laisse la priorité aux overrides mais évite de redéfinir la méthode dans les sous classes qui n'en ont pas besoin
{
    return nullptr ;
}

/**
 * @brief Ennemis::get_nb_phase_boss permet de ne pas définir cette fonction dans les sous classes qui n'en ont pas besoin
 * @return la même valeur que si un boss était à sa dernière phase
 */

int Ennemis::get_nb_phase_boss()
{
    return 1 ;
}

/**
 * @brief Ennemis::get_range getter de portee_attaque
 * @return la portée d'attaque de l'ennemi
 */

int Ennemis::get_range()
{
    return this->portee_attaque ;
}

/**
 * @brief Ennemis::do_action permet d'éguiller vers l'action que doit faire l'ennemi selon la situation
 * @param batiment base du joueur
 */

void Ennemis::do_action( Base *batiment )
{
    if ( this->mort() == true )
    {
        this->die_ennemi() ;
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
 * @brief Ennemis::get_name getter de sprite_ennemi
 * @return le nom de l'ennemi pour savoir dans quel dossier chercher ses sprites
 */

QString Ennemis::get_name()
{
    return this->sprite_ennemi ;
}

/**
 * @brief Ennemis::get_invocation permet de ne pas définir cette fonction dans les sous classes qui n'en ont pas besoin
 * @return un pointeur null
 */

QVector<Ennemis*> *Ennemis::get_invocation()
{
    return nullptr ;
}

/**
 * @brief Ennemis::instant_death permet de tuer manuellement n'importe quel ennemi
 */

void Ennemis::instant_death()
{
    this->point_de_vie_actuel = 0 ;
}

#endif // ennemis_cpp
