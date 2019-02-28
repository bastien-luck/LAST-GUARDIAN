#ifndef gestion_son_h
#define gestion_son_h

#include <iostream>
#include <QMediaPlayer>
#include <QMediaPlaylist>

using namespace std ;

/**
 * @brief The Gestion_son class manage the sound of the game
 */
class Gestion_son
{
    // variables
private :
    int num_musique_en_cours ;
    QMediaPlayer *player ;
    QMediaPlaylist *playlist ;

    // méthodes
public :
    void change_musique( int num_musique ) ;
    void loop_musique() ;
    void mute_music( bool mute ) ;

    // constructeurs / destructeurs
public :
    Gestion_son() ;
    ~Gestion_son(){}
} ;

#endif // gestion_son_h
