#include <QApplication>
#include <iostream>
#include "frame.h"

using namespace std ;

/**
 * @brief qMain le main du jeu
 * @param argc null ici
 * @param argv null ici
 * @return 0
 */

int main( int argc , char *argv[] )
{
    QApplication a(argc, argv) ;

    Frame *jeu = new Frame() ;

    delete jeu ;

    a.exit() ;

    return 0/*a.exec()*/; // ne permet pas de faire un timer framerate pratique donc son effet est simulé dans la frame
}
