#ifndef barre_de_vie_cpp
#define barre_de_vie_cpp

#include "barre_de_vie.h"

/**
 * @brief Barre_de_vie::Barre_de_vie constructeur de la classe Barre_de_vie pour la barre de vie commune à tous les ennemis
 * @param scene la scene où se déroule le jeu
 * @param pos_x
 * @param pos_y
 * @param largeur_barre
 */

Barre_de_vie::Barre_de_vie( QGraphicsScene *scene , qreal pos_x , qreal pos_y , int largeur_barre )
{
    this->scene = scene ;
    this->largeur_barre_pv = largeur_barre ;
    this->hauteur_barre_pv = 4 ;
    this->barre_pv_supp = new QGraphicsPixmapItem() ;
    this->barre_pv_supp->setPos( pos_x , pos_y+5 ) ;
    this->barre_pv_supp->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_fixe.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
    this->barre_pv_supp->setZValue( 1 ) ;
    this->scene->addItem( this->barre_pv_supp ) ;
    this->barre_pv_actuel = new QGraphicsPixmapItem() ;
    this->barre_pv_actuel->setPos( pos_x , pos_y+5 ) ;
    this->barre_pv_actuel->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_en_cours.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
    this->barre_pv_actuel->setZValue( 1 ) ;
    this->scene->addItem( this->barre_pv_actuel ) ;
}

/**
 * @brief Barre_de_vie::Barre_de_vie constructeur de la classe Barre_de_vie pour la barre de vie toujours visible des boss du jeu
 * @param scene la scene où se déroule le jeu
 */

Barre_de_vie::Barre_de_vie( QGraphicsScene *scene )
{
    this->scene = scene ;
    this->largeur_barre_pv = 1200 ;
    this->hauteur_barre_pv = 30 ;
    this->barre_pv_supp = new QGraphicsPixmapItem() ;
    this->barre_pv_supp->setPos( 10 , 10 ) ;
    this->barre_pv_supp->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_supp.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
    this->barre_pv_supp->setZValue( 1 ) ;
    this->scene->addItem( this->barre_pv_supp ) ;
    this->barre_pv_actuel = new QGraphicsPixmapItem() ;
    this->barre_pv_actuel->setPos( 10 , 10 ) ;
    this->barre_pv_actuel->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_en_cours.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
    this->barre_pv_actuel->setZValue( 1 ) ;
    this->scene->addItem( this->barre_pv_actuel ) ;
}

/**
 * @brief Barre_de_vie::get_barre_supp getter de barre_pv_supp
 * @return la barre de vie non actuelle de l'ennemi
 */

QGraphicsPixmapItem *Barre_de_vie::get_barre_supp()
{
    return this->barre_pv_supp ;
}

/**
 * @brief Barre_de_vie::get_barre_actuel getter de barre_pv_actuel
 * @return la barre de vie courante de l'ennemi
 */

QGraphicsPixmapItem *Barre_de_vie::get_barre_actuel()
{
    return this->barre_pv_actuel ;
}

/**
 * @brief Barre_de_vie::perte_pv met à jour l'affichage des barres de vies des ennemis
 * @param pourcent_pv_restant le pourcent de pv qu'il reste à l'ennemi par rapport à son nombre total de pv
 * @param empoisonner est-ce que l'ennemi est actuellement empoisonné ?
 * @param more_hp_barre_to_display reste t'il d'autres phase au boss ? faux si non boss
 */

void Barre_de_vie::perte_pv( qreal pourcent_pv_restant , bool empoisonner , bool more_hp_barre_to_display )
{
    if ( empoisonner == false )
    {
        this->barre_pv_actuel->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_en_cours.png" ).scaled( int (this->largeur_barre_pv*pourcent_pv_restant) , this->hauteur_barre_pv ) ) ;
        if ( more_hp_barre_to_display == false )
        {
            this->barre_pv_supp->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_fixe.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
        }
    }
    else
    {
        this->barre_pv_actuel->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_en_cours_poison.png" ).scaled( int (this->largeur_barre_pv*pourcent_pv_restant) , this->hauteur_barre_pv ) ) ;
        if ( more_hp_barre_to_display == false )
        {
            this->barre_pv_supp->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_fixe.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
        }
        else
        {
            this->barre_pv_supp->setPixmap( QPixmap( ":/images/images_jeu/gui/barre_pv_supp_poison.png" ).scaled( this->largeur_barre_pv , this->hauteur_barre_pv ) ) ;
        }
    }
}

/**
 * @brief Barre_de_vie::move_hp déplace la barre de vie de l'ennemi lorsque celui ci avance
 * @param vitesse_mob la vitesse de déplacement de l'ennemi
 */

void Barre_de_vie::move_hp( qreal vitesse_mob )
{
    this->barre_pv_supp->setPos( this->barre_pv_supp->x() - vitesse_mob , this->barre_pv_supp->y() ) ;
    this->barre_pv_actuel->setPos( this->barre_pv_actuel->x() - vitesse_mob , this->barre_pv_actuel->y() ) ;
}

#endif // barre_de_vie_cpp
