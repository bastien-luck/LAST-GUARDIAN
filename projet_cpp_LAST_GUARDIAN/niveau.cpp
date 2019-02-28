#ifndef niveau_cpp
#define niveau_cpp

#include "niveau.h"

/**
 * @brief Niveau::Niveau constructeur de la classe Niveau
 * @param level numéro du niveau actuel
 */

Niveau::Niveau( int level )
{
    this->numero_niveau = level ;
    this->delais_spawn = 25-level*5 ; // level commence à 1
    this->spawn_ennemi = new QVector<Ennemis*>() ;
    this->spawn_order = new QVector<int>() ;
}

/**
 * @brief Niveau::get_spawn_ennemi getter de spawn_ennemi
 * @return le vecteur qui contient les ennemis présent du niveau
 */

QVector<Ennemis*> *Niveau::get_spawn_ennemi()
{
    return this->spawn_ennemi ;
}

/**
 * @brief Niveau::get_delais_spawn getter de delais_spawn
 * @return le nombre de frame à attendre avant de prendre en compte le prochain ennemi à spawn (plus on avance dans le jeu, plus cette valeur est basse car le joueur est plus puissant)
 */

int Niveau::get_delais_spawn()
{
    return this->delais_spawn ;
}

/**
 * @brief Niveau::get_spawn_order getter de spawn_order
 * @return le vecteur qui contient l'ordre du spawn d'ennemi pour ne pas avoir à créer tous les ennemis lors du lancement du niveau
 */

QVector<int> *Niveau::get_spawn_order()
{
    return this->spawn_order ;
}

#endif // niveau_cpp
