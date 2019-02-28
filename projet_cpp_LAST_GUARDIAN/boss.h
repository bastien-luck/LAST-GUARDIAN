#ifndef boss_h
#define boss_h

#include "ennemis.h"

/**
 * @brief The Boss class define the special behavior of boss kind Ennemis
 */
class Boss : public Ennemis
{
    Q_OBJECT
    // variables
protected :
    int nombre_de_phase_total ;
    int numero_phase_actuelle ;
    Barre_de_vie *barre_haut_screen ;

    // méthodes
public :
    Barre_de_vie *get_hp_boss() ;
    int get_nb_phase_boss() ;

    // constructeurs / destructeurs
public :
    Boss( QGraphicsScene *scene , int largeur , int hauteur , int largeur_hitbox , int hauteur_hitbox , int decalage_hitbox_x , int decalage_hitbox_y , int nb_phase , int pv_tot , int delais , int degat , qreal speed , int range , QString nom , int nb_img_move , int nb_img_attack , int nb_img_die , int num_img_dmg , int delais_sprite ) ;
    ~Boss()
    {
        delete this->barre_haut_screen->get_barre_supp() ;
        delete this->barre_haut_screen->get_barre_actuel() ;
    }
} ;

#endif // boss_h
