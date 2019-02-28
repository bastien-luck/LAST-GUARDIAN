#ifndef gui_cpp
#define gui_cpp

#include "gui.h"
#include "frame.h"

/**
 * @brief Gui::Gui constructeur de la classe Gui
 * @param scene la scene où se déroule le jeu
 */

Gui::Gui( QGraphicsScene *scene )
{
    this->scene = scene ;
    this->image = new QVector<QGraphicsPixmapItem *>() ;
    this->texte = new QVector<QGraphicsTextItem *>() ;
    this->type_bouton = {} ;
}

/**
 * @brief Gui::add_texte permet d'afficher du texte sur l'écran
 * @param pos_x position horizontal du texte
 * @param pos_y position vertical du texte
 * @param nb_car nombre de caractère de la chaine avant de revenir à la ligne
 * @param couleur couleur des caractères
 * @param texte_affiche mots à écrire
 * @param taille_police taille des caractères
 * @param centre est-ce pos_x et pos_y définisse la position du centre du texte ?
 * @param gras est-ce que le texte doit être écrit en gras ?
 */

void Gui::add_texte( qreal pos_x , qreal pos_y , int nb_car , QColor couleur , QString texte_affiche , int taille_police , bool centre , bool gras )
{
    QGraphicsTextItem *texte = new QGraphicsTextItem() ;
    texte->setTextWidth( nb_car ) ; // -1 pour ne pas revenir à la ligne
    texte->setDefaultTextColor( couleur ) ;
    texte->setFont( QFont( "times" , taille_police ) ) ;
    texte->font().setBold( gras ) ; // marche pas
    texte->setPlainText( texte_affiche ) ;
    if ( centre == true )
    {
        texte->setPos( pos_x - texte->boundingRect().width() * 0.5 , pos_y - texte->boundingRect().height() * 0.5 ) ;
    }
    else
    {
        texte->setPos( pos_x , pos_y ) ;
    }
    texte->setZValue( Frame::hauteur_spawn_max ) ;
    this->texte->append( texte ) ;
    this->scene->addItem( this->texte->last() ) ;
}

/**
 * @brief Gui::add_image permet d'affiche des images immobile sur l'écran
 * @param pos_x position horizontal de l'image
 * @param pos_y position vertical de l'image
 * @param largeur largeur de l'image
 * @param hauteur hauteur de l'image
 * @param nom_image nom de l'image pour savoir dans quel dossier chercher ses sprites
 * @param type_image permet de lier plusieurs séquences d'images lors d'un évennement de type input
 * @param centre est-ce pos_x et pos_y définisse la position du centre du texte ?
 */

void Gui::add_image( qreal pos_x , qreal pos_y , int largeur , int hauteur , QString nom_image , int type_image , bool centre )
{
    QGraphicsPixmapItem *image = new QGraphicsPixmapItem() ;
    image->setPixmap( QPixmap( ":/images/images_jeu/" + nom_image + ".png" ).scaled( largeur , hauteur ) ) ;
    if ( centre == true )
    {
        image->setPos( pos_x - largeur * 0.5 , pos_y - hauteur * 0.5 ) ;
    }
    else
    {
        image->setPos( pos_x , pos_y ) ;
    }
    image->setZValue( Frame::hauteur_spawn_max ) ;
    this->image->append( image ) ;
    this->type_bouton.append( type_image ) ;
    this->scene->addItem( this->image->last() ) ;
}

/**
 * @brief Gui::affiche_loose images et textes immobile visible sur l'écran de défaite
 */

void Gui::affiche_loose()
{
    this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran , "fond_noir" , 0 ) ;
    this->add_texte( Frame::largeur_ecran * 0.5 , Frame::hauteur_ecran * 0.5 , -1 , Qt::red , "YOU LOOSE" , 64 , true , true ) ;
}

/**
 * @brief Gui::affiche_win images et textes immobile visible sur l'écran de victoire
 */

void Gui::affiche_win()
{
    this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran , "fond_noir" , 0 ) ;
    this->add_texte( Frame::largeur_ecran * 0.5 , Frame::hauteur_ecran * 0.5 , -1 , Qt::yellow , "YOU WIN" , 64 , true , true ) ;
}

/**
 * @brief Gui::affiche_start images et textes immobile visible sur l'écran de départ
 */

void Gui::affiche_start()
{
    this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran , "background_start" , 0 ) ;

    this->add_texte( 30 , 0 , -1 , Qt::blue , "LAST GUARDIAN" , 128 , false , true ) ;

    int largeur_bouton = 231 ;
    int hauteur_bouton = 69 ;
    this->add_button( int (Frame::largeur_ecran * 0.3) , int (Frame::hauteur_ecran * 0.65) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Jouer" ) ;
    this->add_button( int (Frame::largeur_ecran * 0.3) , int (Frame::hauteur_ecran * 0.80) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Crédits" ) ;
    this->add_button( int (Frame::largeur_ecran * 0.7 - largeur_bouton ) , int (Frame::hauteur_ecran * 0.65) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Options" ) ;
    this->add_button( int (Frame::largeur_ecran * 0.7 - largeur_bouton ) , int (Frame::hauteur_ecran * 0.80) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Quitter" ) ;
}

/**
 * @brief Gui::affiche_pause images et textes immobile visible sur le menu pause
 */

void Gui::affiche_pause()
{
    int largeur_panel = 285 ;
    int hauteur_panel = 492 ;
    this->add_image( Frame::largeur_ecran * 0.5 , Frame::hauteur_spawn_max * 0.5 , largeur_panel , hauteur_panel , "gui/background_gui_pause" , 0 , true ) ;

    int largeur_bouton = 231 ;
    int hauteur_bouton = 69 ;
    this->add_button( int ((Frame::largeur_ecran - largeur_bouton) * 0.5) , int (Frame::hauteur_spawn_max * 0.2) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Continuer" ) ;
    this->add_button( int ((Frame::largeur_ecran - largeur_bouton) * 0.5) , int (Frame::hauteur_spawn_max * 0.36) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Options" ) ; // au moins pour le volume sonore
    this->add_button( int ((Frame::largeur_ecran - largeur_bouton) * 0.5) , int (Frame::hauteur_spawn_max * 0.52) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Menu Principal" ) ; // voir à quoi le lier
    this->add_button( int ((Frame::largeur_ecran - largeur_bouton) * 0.5) , int (Frame::hauteur_spawn_max * 0.68) , largeur_bouton , hauteur_bouton , "button_not_clicked_pause" , "Quitter" ) ;
}

/**
 * @brief Gui::affiche_jeu images et textes immobile visible sur l'écran de combat
 */

void Gui::affiche_jeu()
{
    int hauteur_background_gui_play = 120 ;

    this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran - hauteur_background_gui_play , "background_jeu" , 0 ) ;
    this->image->last()->setZValue( 0 ) ; // cas spécial qui ne doit pas être devant
    this->add_image( 0 , Frame::hauteur_ecran - hauteur_background_gui_play , Frame::largeur_ecran , hauteur_background_gui_play , "gui/background_gui_play" , 0 ) ;
    this->add_texte( 50 , Frame::hauteur_spawn_max + 20 , 700 , Qt::black , "Pour débloquer toutes les armes, faire un clique gauche. Pour ensuite changer l'arme équipée, utiliser & é \" ' (" , 20 ) ;
}

/**
 * @brief Gui::affiche_option images et textes immobile visible sur le menu option
 * @param tir_auto_on permet de savoir si le joueur a activé le mode tir automatique pour modifier l'affichage du bouton
 */

void Gui::affiche_option( bool tir_auto_on )
{
    this->add_image( Frame::largeur_ecran * 0.5 , Frame::hauteur_ecran * 0.5 , int (Frame::largeur_ecran * 0.5) , int (Frame::hauteur_ecran * 0.5) , "gui/panels/small panel 2" , 0 , true ) ;
    this->add_image( Frame::largeur_ecran * 0.3 , Frame::hauteur_ecran * 0.4 , 21*2 , 21*2 , "gui/music_on_button" , 3 ) ;
    this->add_image( Frame::largeur_ecran * 0.3 , Frame::hauteur_ecran * 0.5 , 18*2 , 18*2 , "gui/check_mark_passive" , 5 ) ;
    this->add_texte( Frame::largeur_ecran * 0.33 , Frame::hauteur_ecran * 0.5 , -1 , Qt::black , "Tir automatique ( en jeu : T )" , 20 ) ;
    if ( this->music_muted == true )
    {
        this->change_image_bouton( this->image->size() - 2 ) ;
    }
    if ( tir_auto_on == true )
    {
        this->change_image_bouton( this->image->size() - 1 ) ;
    }
}

/**
 * @brief Gui::affiche_upgrade images et textes immobile visible sur l'écran d'upgrade
 * @param arme_a_upgrader armes équipé par le joueur
 * @param nb_armes_debloquer nombre d'arme que le joueur possède
 * @param reset_affichage est-ce que un input a eut lieu ?
 */

void Gui::affiche_upgrade( Armes *arme_a_upgrader , int nb_armes_debloquer , bool reset_affichage )
{
    int taille_bouton = 42 ; // 21*2
    if ( reset_affichage == false )
    {
        this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran , "background_upgrade" , 0 ) ;
        this->add_image( 75 , 450 , taille_bouton , taille_bouton , "gui/fleche_gauche" , 8 ) ;
        this->add_image( 280 , 450 , taille_bouton , taille_bouton , "gui/fleche_droite" , 7 ) ;
    }
    this->add_texte( 200 , 470 , -1 , Qt::black , QString::number(arme_a_upgrader->get_id_arme()+1) + "/" + QString::number(nb_armes_debloquer) , 20 , true , true ) ;
    QString nom_arme ;
    switch( arme_a_upgrader->get_id_arme() ) // j'aurais dû utiliser le boundingrect des image pour limiter les problèmes de non compatibilité mais cela entrainé la nécéssité de créer une balle donc...
    {
    case 0 :
        this->add_image( 200 , 300 , 24*5 , 22*5 , "projectiles/projectile_basique" , 0 , true ) ;
        nom_arme = "blaster basique" ;
        break ;
    case 1 :
        this->add_image( 200 , 300 , 18*5 , 18*5 , "projectiles/projectile_corrosif" , 0 , true ) ;
        nom_arme = "blaster corrosif" ;
        break ;
    case 2 :
        this->add_image( 200 , 300 , 112*2 , 72*2 , "projectiles/projectile_lourd" , 0 , true ) ;
        nom_arme = "blaster sniper" ;
        break ;
    case 3 :
        this->add_image( 200 , 300 , 97*2 , 68*2 , "projectiles/projectile_explosif" , 0 , true ) ;
        nom_arme = "blaster explosif" ;
        break ;
    case 4 :
        this->add_image( 200 , 300 , 9*5 , 9*5 , "projectiles/projectile_rapide" , 0 , true ) ;
        nom_arme = "blaster minigun" ;
        break ;
    }
    this->add_texte( 200 , 200 , -1 , Qt::black , nom_arme , 20 , true , true ) ;

    if ( arme_a_upgrader->get_level_actuel_degat() < arme_a_upgrader->get_level_max_degat() ) // pas très joli mais j'ai fait la disparition du bouton plus rapidement car je n'ai pas le temps de trouver comment gérer le fait que le numéro de l'image change pour le choix de l'upgrade
    {
        this->add_image( 500 , 200 , taille_bouton , taille_bouton , "gui/bouton_plus" , 9 ) ;
    }
    else
    {
        this->add_image( 500 , 200 , 0 , 0 , "gui/bouton_plus" , 9 ) ;
    }
    this->add_texte( 550 , 200 , -1 , Qt::black , "Amélioration de la puissance de l'arme : " + QString::number(arme_a_upgrader->get_level_actuel_degat()) + "/" + QString::number(arme_a_upgrader->get_level_max_degat()) , 20 , false , true ) ;
    if ( arme_a_upgrader->get_level_actuel_cadence_tir() < arme_a_upgrader->get_level_max_cadence_tir() )
    {
        this->add_image( 500 , 300 , taille_bouton , taille_bouton , "gui/bouton_plus" , 9 ) ;
    }
    else
    {
        this->add_image( 500 , 200 , 0 , 0 , "gui/bouton_plus" , 9 ) ;
    }
    this->add_texte( 550 , 300 , -1 , Qt::black , "Amélioration de la cadence de tire de l'arme : " + QString::number(arme_a_upgrader->get_level_actuel_cadence_tir()) + "/" + QString::number(arme_a_upgrader->get_level_max_cadence_tir()) , 20 , false , true ) ;
    if ( arme_a_upgrader->get_level_actuel_nombre_balle_tire() < arme_a_upgrader->get_level_max_nombre_balle_tire() )
    {
        this->add_image( 500 , 400 , taille_bouton , taille_bouton , "gui/bouton_plus" , 9 ) ;
    }
    else
    {
        this->add_image( 500 , 200 , 0 , 0 , "gui/bouton_plus" , 9 ) ;
    }
    this->add_texte( 550 , 400 , -1 , Qt::black , "Amélioration du nombre de balles tirées de l'arme : " + QString::number(arme_a_upgrader->get_level_actuel_nombre_balle_tire()) + "/" + QString::number(arme_a_upgrader->get_level_max_nombre_balle_tire()) , 20 , false , true ) ;
}

/**
 * @brief Gui::affiche_credit images et textes immobile visible sur l'écran de crédit
 */

void Gui::affiche_credit()
{
    this->add_image( 0 , 0 , Frame::largeur_ecran , Frame::hauteur_ecran , "fond_noir" , 0 ) ;
    this->add_texte( 30 , 10 , -1 , Qt::white , "Développeur :" , 20 ) ;
    this->add_texte( 30 , 50 , -1 , Qt::white , "LUCK Bastien" , 12 ) ;
    this->add_texte( 30 , 110 , -1 , Qt::white , "Musiques :" , 20 ) ;
    this->add_texte( 30 , 150 , -1 , Qt::white , "écran de combat : https://nyxgames.itch.io/space-blaster" , 12 ) ;
    this->add_texte( 30 , 180 , -1 , Qt::white , "autres : https://finalgatestudios.itch.io/music-pack-1" , 12 ) ;
    this->add_texte( 30 , 240 , -1 , Qt::white , "Graphiques :" , 20 ) ;
    this->add_texte( 30 , 280 , -1 , Qt::white , "background départ : non retrouvé" , 12 ) ;
    this->add_texte( 30 , 310 , -1 , Qt::white , "background combat : http://spritedatabase.net/file/8069/Desert" , 12 ) ;
    this->add_texte( 30 , 340 , -1 , Qt::white , "boutons et mini fenêtres : https://plastic-vibes.itch.io/pocket-gui-for-pixel-mobile-games" , 12 ) ;
    this->add_texte( 30 , 370 , -1 , Qt::white , "curseur ( modifié ) : https://kicked-in-teeth.itch.io/point" , 12 ) ;
    this->add_texte( 30 , 400 , -1 , Qt::white , "slime : https://rvros.itch.io/pixel-art-animated-slime" , 12 ) ;
    this->add_texte( 30 , 430 , -1 , Qt::white , "champignon : https://lhteam.itch.io/tiny-mushroom" , 12 ) ;
    this->add_texte( 30 , 460 , -1 , Qt::white , "squelette : https://jesse-m.itch.io/skeleton-pack" , 12 ) ;
    this->add_texte( 30 , 490 , -1 , Qt::white , "boss summoner : https://lionheart963.itch.io/the-summoner" , 12 ) ;
    this->add_texte( 30 , 520 , -1 , Qt::white , "joueur ( animation non utilisée ) : non retrouvé" , 12 ) ;
    this->add_texte( 30 , 550 , -1 , Qt::white , "munitions : https://nyxgames.itch.io/space-blaster" , 12 ) ;
    this->add_texte( 30 , 580 , -1 , Qt::white , "explosions : https://skywardriver.itch.io/free-pixel-animations-christmas-pack" , 12 ) ;

}

/**
 * @brief Gui::remove_item_from_scene permet de supprimer les images non utile à un écran
 * @param indice_debut_supression_image permet de ne supprimer que les images en sur-affichage (le menu option ne supprime pas le menu pause qui ne supprime pas l'écran start ni l'écran de combat)
 * @param indice_debut_supression_texte permet de ne supprimer que les textes en sur-affichage
 */

void Gui::remove_item_from_scene( int indice_debut_supression_image , int indice_debut_supression_texte )
{
    while ( this->image->size() > indice_debut_supression_image )
    {
        this->scene->removeItem( this->image->last() ) ;
        delete this->image->takeLast() ;
        this->type_bouton.removeLast() ;
    }
    while ( this->texte->size() > indice_debut_supression_texte )
    {
        this->scene->removeItem( this->texte->last() ) ;
        delete this->texte->takeLast() ;
    }
}

/**
 * @brief Gui::add_button permet d'ajouter une image de type bouton cliquable
 * @param pos_x position horizontal de l'image
 * @param pos_y position vertical de l'image
 * @param largeur largeur de l'image
 * @param hauteur hauteur de l'image
 * @param nom_image nom de l'image pour savoir dans quel dossier chercher ses sprites
 * @param texte_du_bouton texte à mettre sur le bouton
 */

void Gui::add_button( qreal pos_x , qreal pos_y , int largeur , int hauteur , QString nom_image , QString texte_du_bouton )
{
    this->add_image( pos_x , pos_y , largeur , hauteur , "gui/" + nom_image , 1 ) ;

    if ( texte_du_bouton != "" )
    {
        this->add_texte( pos_x + largeur * 0.5 , pos_y + hauteur * 0.5 , -1 , Qt::black , texte_du_bouton , 20 , true , true ) ;
    }
}

/**
 * @brief Gui::is_clicked permet de savoir quel bouton a été cliqué dessus par le joueur
 * @param curseur_x position horizontal du curseur de la souris
 * @param curseur_y position vertical du curseur de la souris
 * @param action est-ce que le joueur relache son clic sur l'image ?
 * @return le numéro de la position de l'image dans le vecteur image
 */

int Gui::is_clicked( qreal curseur_x , qreal curseur_y , bool action )
{
    int num_bouton = -1 ; // je ne voulais utiliser que des itérateurs mais j'ai besoin de regarder deux tableau donc...
    curseur_x -= 6 ; // je ne sais pas si c'est la valeur du curseur ou de l'image qui est décalé mais le -6 est nécessaire
    curseur_y -= 6 ;
    for ( int i = 0 ; i < this->image->size() ; i++ )
    {
        if ( this->image->at(i)->x() <= curseur_x && curseur_x <= this->image->at(i)->x() + this->image->at(i)->boundingRect().width()
             && this->image->at(i)->y() <= curseur_y && curseur_y <= this->image->at(i)->y() + this->image->at(i)->boundingRect().height() )
        {
            switch( this->type_bouton.at( i ) )
            {
                case 1 :
                    if ( action == false ) // évite de rendre actif le bouton alors qu'on n'effectue pas le fait de presser le clique gauche sur le bouton
                    {
                        this->change_image_bouton( i ) ;
                    }
                    break ;
                case 2 :
                case 3 :
                case 4 :
                case 5 :
                case 6 :
                    if ( action == true )
                    {
                        this->change_image_bouton( i ) ;
                        num_bouton = i ;
                    }
                    break ;
                case 7 :
                case 8 :
                case 9 :
                    if ( action == true ) // je n'ai pas de sprite pour l'appui de certains boutons
                    {
                        num_bouton = i ;
                    }
                    break ;
                default :
                    break ;
            }
        }
        else // reset l'image à son état initial si on ne clique pas dessus
        {
            switch( this->type_bouton.at( i ) )
            {
                case 2 :
                    this->change_image_bouton( i ) ;
                    break ;
                default :
                    break ;
            }

        }
    }

    return num_bouton ;
}

/**
 * @brief Gui::change_image_bouton permet de changer l'image du bouton selon son état actuel
 * @param num_bouton position du bouton dans les tableaux
 */

void Gui::change_image_bouton( int num_bouton )
{
    switch( this->type_bouton.at( num_bouton ) )
    {
        case 1 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/button_clicked_pause.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 2 ;
            break ;
        case 2 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/button_not_clicked_pause.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 1 ;
            break ;
        case 3 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/music_off_button.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 4 ;
            break ;
        case 4 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/music_on_button.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 3 ;
            break ;
        case 5 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/check_mark_active.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 6 ;
            break ;
        case 6 :
            this->image->at( num_bouton )->setPixmap( QPixmap( ":/images/images_jeu/gui/check_mark_passive.png" ).scaled( int (this->image->at( num_bouton )->boundingRect().width()) , int (this->image->at( num_bouton )->boundingRect().height()) ) ) ;
            this->type_bouton[ num_bouton ] = 5 ;
            break ;
        default :
            break ;
    }
}

/**
 * @brief Gui::get_nb_image getter de image->size()
 * @return le nombre d'images immobile visible à l'écran
 */

int Gui::get_nb_image()
{
    return this->image->size() ;
}

/**
 * @brief Gui::get_nb_texte getter de texte->size()
 * @return le nombre de texte immobile visible à l'écran
 */

int Gui::get_nb_texte()
{
    return this->texte->size() ;
}

#endif // gui_cpp
