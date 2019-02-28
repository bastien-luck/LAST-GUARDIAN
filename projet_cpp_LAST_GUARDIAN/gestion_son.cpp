#ifndef gestion_son_cpp
#define gestion_son_cpp

#include "gestion_son.h"

/**
 * @brief Gestion_son::Gestion_son construteur de la classe Gestion_son
 */

Gestion_son::Gestion_son()
{
    this->num_musique_en_cours = 0 ;
    this->player = new QMediaPlayer() ;
    this->playlist = new QMediaPlaylist( this->player ) ;
    this->playlist->addMedia( QUrl( "qrc:/musiques/musiques_jeu/musique_start_screen.wav" ) ) ;
    this->playlist->addMedia( QUrl( "qrc:/musiques/musiques_jeu/musique_combat.wav" ) ) ;
    this->playlist->addMedia( QUrl( "qrc:/musiques/musiques_jeu/musique_upgrade.wav" ) ) ;
    this->player->setPlaylist( playlist ) ;
    this->player->setVolume( 100 ) ; // il semblerait que lors de la première utilisation de la classe QMediaPlayer volume = 0 ? le 100 représente un pourcentage du volume actuel de l'ordinateur
    this->playlist->setCurrentIndex( this->num_musique_en_cours ) ; // permet de changer de musique selon l'endroit où l'on se trouve
    this->player->play() ;
}

/**
 * @brief Gestion_son::change_musique permet de changer de musique en jeu
 * @param num_musique numéro de la musique dans la playlist
 */

void Gestion_son::change_musique( int num_musique )
{
    if ( this->num_musique_en_cours != num_musique )
    {
        this->player->setPosition( 0 ) ;
        this->num_musique_en_cours = num_musique ;
        this->playlist->setCurrentIndex( this->num_musique_en_cours ) ;
    }
}

/**
 * @brief Gestion_son::loop_musique permet de jouer en boucle une musique (de façon plus ou moins bien, dépend de la piste audio et nécessite un étalonnage manuel car utiliser l'attribut LOOP de QMediaPlaylist fait de mauvaise boucle)
 */

void Gestion_son::loop_musique()
{
    switch ( this->num_musique_en_cours )
    {
        case 0 :
            if ( this->player->position() > 23940 ) // la musique est chargé pour quelques ms donc il ne faut pas attendre la dernière position si l'on veut une boucle parfaite !!! (50 ms semble être la bonne valeur)
            {
                this->player->setPosition( 0 ) ;
                this->player->play() ;
            }
            break ;
        case 1 :
            if ( this->player->position() > 11245 )
            {
                this->player->setPosition( 0 ) ;
                this->player->play() ;
            }
            break ;
        case 2 :
            if ( this->player->position() > 39940 )
            {
                this->player->setPosition( 0 ) ;
                this->player->play() ;
            }
            break ;
        default :
            break ;
    }
}

/**
 * @brief Gestion_son::mute_music permet de supprimerer le son de la musique (sans arréter la musique)
 * @param mute true si on a choisi d'arréter la musique
 */

void Gestion_son::mute_music( bool mute )
{
    this->player->setMuted( mute ) ;
}

#endif // gestion_son_cpp
