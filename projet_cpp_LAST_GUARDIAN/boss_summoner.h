#ifndef boss_sumoner_h
#define boss_sumoner_h

#include "boss.h"

/**
 * @brief The Boss_summoner class define how act the boss called "the summoner"
 */
class Boss_summoner : public Boss
{
    Q_OBJECT
    // variables
private :
    QVector<Ennemis*> *mob_spawned ; // j'aurais pu mettre les mobs invoqué dans le vecteur de niveau, mais cela rendait la gestion de cette action spéciale compliqué et en plus, l'avantage de cette utilisation de vecteur ici me permet de tuer les mobs invoqué quand le boss meurt et donc d'avoir un résultat plus intérressant donc pourquoi faire compliqué quand faire simple est mieux ? :)
    int num_image_action_speciale_actuel ; // ces variables étaient dans Ennemis mais n'ayant pas le temps de faire tous les ennemis, le summoner se retrouve à être le seul avec une action spéciale donc au final je les aient déplacé ici
    int nb_image_action_speciale ;
    int delais_action_speciale ; // une action spéciale étant spéciale, elle n'est pas censé ne pas avoir de cooldown
    int delais_action_speciale_actuel ;
    QVector<QGraphicsPixmapItem*> *portail_invocation ;
    int largeur_sprite_portail ;
    int hauteur_sprite_portail ;

    // méthodes
public :
    void attack_ennemi( Base *batiment ) ;
    void die_ennemi() ;
    void do_action( Base *batiment ) ;
    void summon_mob() ;
    QVector<Ennemis*> *get_invocation() ;
    void kill_all_summon_on_death() ;

    // constructeurs / destructeurs
public :
    Boss_summoner( QGraphicsScene *scene ) ;
    ~Boss_summoner() // force la suppression dans le cas du win/loose screen
    {
        for ( QVector<QGraphicsPixmapItem*>::iterator portail_restant = this->portail_invocation->begin() ; portail_restant != this->portail_invocation->end() ; ++portail_restant )
        {
            delete (*portail_restant) ;
            (*portail_restant) = nullptr ;
            portail_restant = this->portail_invocation->erase( portail_restant ) ;
            --portail_restant ;
        }
        for ( QVector<Ennemis*>::iterator invocation_restante = this->mob_spawned->begin() ; invocation_restante != this->mob_spawned->end() ; ++invocation_restante )
        {
            delete (*invocation_restante) ;
            (*invocation_restante) = nullptr ;
            invocation_restante = this->mob_spawned->erase( invocation_restante ) ;
            --invocation_restante ;
        }
    }
} ;

#endif // boss_sumoner_h
