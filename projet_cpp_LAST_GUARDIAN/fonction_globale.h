#ifndef fonction_globale_h
#define fonction_globale_h

#include <iostream>
#include <QVector>
#include "niveau.h"
#include "ennemis.h"
#include "projectiles.h"


// en soit, ces fonctions sont plus lié à des fonctions de Frame mais bon
/**
 * dans l'idée, ces fonctions sont censé être utilisable par plusieurs classes mais j'ai un peu raté mon coup et au final ce n'est pas le cas x)
 */
Niveau *init_niveau( int num_lv ) ;
Ennemis *spawn_ennemi( QGraphicsScene *scene , int id_ennemi ) ;
bool collision_ennemi_contre_munition( Ennemis *mob , Projectiles *ammo ) ;
bool collision_ennemi_contre_explosion( Ennemis *mob , Explosion *bombe ) ;
bool collision_entre_deux_objets( int ligne_gauche_objet_1_x , int ligne_droite_objet_1_x , int ligne_haut_objet_1_y , int ligne_bas_objet_1_y , int ligne_gauche_objet_2_x , int ligne_droite_objet_2_x , int ligne_haut_objet_2_y , int ligne_bas_objet_2_y ) ;
int gestion_ennemis( Base *batiment , QVector<Ennemis*> *ennemis_spawned , QVector<Projectiles*> *bullet_fired , QVector<Explosion*> *explosion_en_cours ) ;

#endif //fonction_globale_h
