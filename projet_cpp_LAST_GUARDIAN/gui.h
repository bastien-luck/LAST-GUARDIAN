#ifndef Gui_h
#define Gui_h

#include <iostream>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "armes.h"

using namespace std ;

/**
 * @brief The Gui class define every visible thing that don't move in the game
 */
class Gui
{
    // variables
private :
    QGraphicsScene * scene ;
    QVector<QGraphicsTextItem *> *texte ;
    QVector<QGraphicsPixmapItem *> *image ;
    QVector<int> type_bouton ; // sert pour savoir de quel bouton on parle (nécessaire pour les modifications des pixmap vu que certains boutons n'ont pas de texte)
    // 0 : ce n'est pas un bouton (oui oui haha) , 1 : boutons écran start et pause non cliqué ,
    // 2 : boutons écran start et pause cliqué , 3 : bouton musique on , 4 : bouton musique off ,
    // 5 : check mark non coché , 6 : check mark coché , 7 : flèche droite , 8 : flèche gauche ,
    // 9 : bouton plus
public :
    bool music_muted = false ;
    int volume_musique = 100 ;

    // méthodes
public :
    void add_texte( qreal pos_x , qreal pos_y , int nb_car , QColor couleur , QString texte_affiche , int taille_police , bool centre = false , bool gras = false ) ;
    void add_image( qreal pos_x , qreal pos_y , int largeur , int hauteur , QString nom_image , int type_image , bool centre = false ) ;
    void affiche_loose() ;
    void affiche_win() ;
    void affiche_start() ;
    void affiche_pause() ;
    void affiche_jeu() ;
    void affiche_option( bool tir_auto_on ) ;
    void affiche_upgrade( Armes *arme_a_upgrader , int nb_armes_debloquer , bool reset_affichage = false ) ;
    void affiche_credit() ;
    void remove_item_from_scene( int indice_debut_supression_image = 0 , int indice_debut_supression_texte = 0 ) ;
    void add_button( qreal pos_x , qreal pos_y , int largeur , int hauteur , QString nom_image , QString texte_du_bouton = "" ) ;
    int is_clicked( qreal curseur_x , qreal curseur_y , bool action = false ) ;
    void change_image_bouton( int num_bouton ) ;
    int get_nb_image() ;
    int get_nb_texte() ;

    // constructeurs / destructeurs
public:
    Gui( QGraphicsScene * scene ) ;
    ~Gui(){}
};

#endif // Gui_h
