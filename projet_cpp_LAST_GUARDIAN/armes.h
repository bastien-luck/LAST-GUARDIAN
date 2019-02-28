#ifndef armes_h
#define armes_h

#include <iostream>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "projectiles.h"

using namespace std ;

/**
 * @brief The Armes class define all the weapon available in game with all their caracteristics
 */
class Armes
{
    //variables
private :
    QGraphicsScene *scene ;
    int id_arme ; // permet de savoir de quel arme on parle sans faire une comparaison avec les noms
    int nombre_projectile_tire ;
    int delais_entre_tir ; // nombre de frame entre deux tirs
    int delais_actuel ;
    int angle_max_balles_tiree ;
    int level_actuel_degat ;
    int level_max_degat ;
    int scaling_degat ;
    int level_actuel_cadence_de_tir ;
    int level_max_cadence_de_tir ;
    int scaling_cadence_de_tir ;
    int level_actuel_nombre_de_balle_tire ;
    int level_max_nombre_de_balle_tire ;
    int scaling_nombre_de_balle_tire ;
    int munition_tire ;

    // méthodes
public :
    Projectiles *tire( qreal pos_y , int angle = 0 ) ;
    bool tir_possible( bool joueur_tire , bool tir_auto ) ;
    int get_id_arme() ;
    int get_nombre_projectiles_tire() ;
    void delais_changement_arme() ;
    int get_angle_max() ;
    void ameliore_arme( int type_amelioration ) ; // 0 : dégat , 1 : cadence de tir , 2 : nombre de balle
    int get_level_actuel_degat() ;
    int get_level_max_degat() ;
    int get_level_actuel_cadence_tir() ;
    int get_level_max_cadence_tir() ;
    int get_level_actuel_nombre_balle_tire() ;
    int get_level_max_nombre_balle_tire() ;

    // constructeurs / destructeurs
public:
    Armes( QGraphicsScene *scene , int id_arme , int nb_bullet , int delais , int angle_max , int lv_max_cad_tir , int scal_cad_tir , int lv_max_nb_balle , int scal_nb_balle , int lv_max_degat , int scal_degat , int ammo ) ;
    ~Armes(){}
} ;

#endif // armes_h
