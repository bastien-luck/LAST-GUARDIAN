#ifndef frame_cpp
#define frame_cpp

#include <QCoreApplication>
#include "windows.h"
#include "frame.h"
#include "guardian.h"
#include "gestion_input.h"
#include <QSoundEffect>

/**
 * @brief Frame::Frame "constructeur" de la classe Frame
 * cette classe s'occupe de toutes les actions que le jeu fait en gérant les conséquences associés à chaque situation
 */

Frame::Frame()
{
    qsrand( uint (QTime::currentTime().msec()) ); // fait au début pour ne plus s'en inquiéter :)
    this->endroit_actuel = 1 ;
    this->items_deja_present = false ;
    this->pause = false ;
    this->option = false ;
    this->niveau_actuel = nullptr ;
    this->tir_automatique = false ;
    this->arme_upgrade_show = 0 ;

    // credit to the youtuber Abdullah Aghazadah for the default setup of the frame
    // create a scene
    this->scene = new QGraphicsScene();

    // create an item to put into the scene
    this->keylistener = new Gestion_input() ;
    this->projectiles_presents = new QVector<Projectiles*>() ;
    this->interface_graphique = new Gui( scene ) ;
    this->explosions_presentes = new QVector<Explosion*>() ;

    // make keylistener focusable
    this->keylistener->setFlag(QGraphicsItem::ItemIsFocusable);
    this->keylistener->setFocus();

    // add a view to visualize the scene
    this->view = new QGraphicsView( this->scene );

    // undecorate the window
    this->view->setWindowFlags(Qt::CustomizeWindowHint); // supprime la possibilité d'utiliser la croix qui crash l'appli ni le resize
    this->view->setFixedSize( this->largeur_ecran+2 , this->hauteur_ecran+2 ) ; // sans le +2, il est posible de scroller la fenêtre de quelque pixel, bizarre
    this->scene->setSceneRect( 0 , 0 , this->largeur_ecran , this->hauteur_ecran ) ; // évite que la scene s'agrandisse toute seule (peut-être pas le cas car je ne passe pas pas a.exec() ?)
    this->view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ; // permet de faire spawn les ennemis juste en dehors de la fenêtre pour
    this->view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff ) ; // faire un effet de non téléportation sans avoir de scrollbar visible

    // add the item to the scene
    this->scene->addItem( this->keylistener ) ;

    // make the view visible
    this->view->show();

    // change the cursor looking
    this->view->setCursor( QCursor( QPixmap( ":/images/images_jeu/curseur/default_cursor.png" ).scaled( 30 , 30 ) , 0 , 0 ) ) ; // sans le double 0, le vrai curseur est au milieu du nouveau curseur

    // création musique ambiante
    this->jukebox = new Gestion_son() ; // ne prend pas encore en compte les effets sonores

    /*QSoundEffect * effect = new QSoundEffect(this);
    effect->setSource( QUrl( "qrc:/musiques/musiques_jeu/musique_combat.wav" ) );
    effect->play() ;*/ // à utiliser pour les effets sonores

    this->joueur = nullptr ; // permet de ne créer qu'un joueur lorsque l'on lance le jeu

    while ( this->endroit_actuel != 0 )
    {
        this->dieTime = QTime::currentTime().addMSecs(17); // 17 pour 60 fps ( 16*60=960 et 17*60=1020 donc 17 est plus proche de 1 seconde que 16 )
        switch( this->endroit_actuel )
        {
            case 1 :
                this->jukebox->change_musique( 0 ) ;
                this->start_screen() ;
                break ;
            case 2 :
                this->jukebox->change_musique( 1 ) ;
                this->play() ;
                break ;
            case 3 :
                this->jukebox->change_musique( 2 ) ;
                this->winning_screen() ;
                break ;
            case 4 :
                this->jukebox->change_musique( 2 ) ;
                this->loosing_screen() ;
                break ;
            case 5 :
                this->jukebox->change_musique( 2 ) ;
                this->upgrade_screen() ;
                break ;
            case 6 :
                this->jukebox->change_musique( 2 ) ;
                this->credit_screen() ;
                break ;
        }

        this->jukebox->loop_musique() ;

        while ( QTime::currentTime() < this->dieTime ) // credit to stackoverflow => méthode pour un framerate qui ne bloque pas le GUI (très puissant car marche parfaitement même avec 1 de différence entre currentTime et dieTime)
        {
            QCoreApplication::processEvents( QEventLoop::AllEvents , 100 ) ;
        }
    }
}

/**
 * @brief Frame::change_endroit_actuel permet de gérer les suppressions d'objets en masse nécessaire lors des changement d'écran
 * @param endroit_suivant la valeur du prochain écran de jeu
 */

void Frame::change_endroit_actuel( int endroit_suivant )
{
    if ( this->endroit_actuel == 2 )
    {
        this->scene->removeItem( this->joueur ) ;
        for ( QVector<Ennemis*>::iterator ennemi_restant = this->niveau_actuel->get_spawn_ennemi()->begin() ; ennemi_restant != this->niveau_actuel->get_spawn_ennemi()->end() ; ++ennemi_restant )
        {
            delete (*ennemi_restant) ;
            (*ennemi_restant) = nullptr ;
            ennemi_restant = this->niveau_actuel->get_spawn_ennemi()->erase( ennemi_restant ) ;
            --ennemi_restant ;
        }
        for ( QVector<Projectiles*>::iterator bullet_deleted = this->projectiles_presents->begin() ; bullet_deleted != this->projectiles_presents->end() ; ++bullet_deleted )
        {
            delete (*bullet_deleted) ; // si les balles ne sont pas supprimé, lors du reset du niveau il est possible de tuer un ennemi avant de commencer à tirer ^^'
            (*bullet_deleted) = nullptr ;
            this->projectiles_presents->erase( bullet_deleted ) ;
            --bullet_deleted ;
        }
        for ( QVector<Explosion*>::iterator explosion_advance = this->explosions_presentes->begin() ; explosion_advance != this->explosions_presentes->end() ; ++explosion_advance )
        {
            delete (*explosion_advance) ;
            (*explosion_advance) = nullptr ;
            explosion_advance = this->explosions_presentes->erase( explosion_advance ) ;
            --explosion_advance ;
        }
        delete this->niveau_actuel ;
        this->niveau_actuel = nullptr ;
        if ( endroit_suivant != 5 )
        {
            delete this->joueur ;
            this->joueur = nullptr ;
        }
    }
    this->endroit_actuel = endroit_suivant ;
    this->items_deja_present = false ;
    this->interface_graphique->remove_item_from_scene() ;
}

/**
 * @brief Frame::start_screen écran de début du jeu
 */

void Frame::start_screen()
{
    if ( this->option == false )
    {
        if ( this->items_deja_present == false )
        {
            this->interface_graphique->affiche_start() ;
            this->items_deja_present = true ;
        }
        if ( this->keylistener->fin == true )
        {
            this->change_endroit_actuel( 0 ) ;
        }
        if ( this->keylistener->validation == true )
        {
            this->bunker = new Base( this->scene , 100 ) ;
            this->change_endroit_actuel( 2 ) ;
            this->numero_niveau_actuel = 1 ;
        }
        if ( this->keylistener->left_click_pressed == true )
        {
            this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() ) ;
        }
        if ( this->keylistener->left_click_released == true )
        {
            switch (this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() , true ) )
            {
            case 1 :
                this->bunker = new Base( this->scene , 100 ) ;
                this->change_endroit_actuel( 2 ) ; // jouer
                this->numero_niveau_actuel = 1 ;
                break ;
            case 2 :
                this->change_endroit_actuel( 6 ) ; // crédit
                break ;
            case 3 :
                this->items_deja_present = false ; // options
                this->option = true ;
                break ;
            case 4 :
                this->change_endroit_actuel( 0 ) ; // quitter
                break ;
            default :
                break ;
            }
            this->keylistener->left_click_released = false ;
        }
    }
    else
    {
        this->menu_option() ;
    }
}

/**
 * @brief Frame::play écran de combat du jeu (informations en bas de l'écran non implémenté)
 * s'occupe de tous ce qui se passe lorsque le joueur se bat férocement contre les vagues d'ennemis
 */

void Frame::play()
{
    if ( this->niveau_actuel == nullptr ) // reset/change the level
    {
        // create the level
        this->niveau_actuel = init_niveau( this->numero_niveau_actuel ) ;
        this->attente_prochain_spawn = this->niveau_actuel->get_delais_spawn() ;
        this->numero_ennemi_spawned = 0 ;
        this->nombre_ennemi_mort = 0 ;
    }
    if ( this->pause == false )
    {
        if ( this->items_deja_present == false )
        {
            this->items_deja_present = true ;

            this->interface_graphique->affiche_jeu() ; // à faire en premier sinon ça cache tout :)
            if ( this->joueur == nullptr )
            {
                this->joueur = new Guardian( this->scene ) ;
            }
            else
            {
                this->scene->addItem( this->joueur ) ;
            }
        }

        if ( this->keylistener->haut == true )
        {
            this->joueur->move_up() ;
        }
        if ( this->keylistener->bas == true && this->joueur->y() + this->joueur->get_hauteur_sprite_guardian() < this->hauteur_spawn_max - 3 ) // -3 car la hauteur du sprite du guardian n'est pas un multiple de 5...
        {
            this->joueur->move_down() ;
        }
        if ( this->keylistener->auto_fire == true )
        {
            this->tir_automatique = !this->tir_automatique ;
            this->keylistener->auto_fire = false ;
        }

        if ( this->keylistener->fin == true )
        {
            this->pause = true ;
            this->keylistener->fin = false ;
            this->items_deja_present = false ;
        }

        if ( this->joueur->get_arme_equipe()->get_id_arme() != this->keylistener->choix_arme )
        {
            this->joueur->change_arme_equipe( this->keylistener->choix_arme ) ;
        }

        if ( this->keylistener->left_click_released == true )
        {
            this->joueur->fabrique_arme( 1 ) ;
            this->joueur->fabrique_arme( 2 ) ;
            this->joueur->fabrique_arme( 3 ) ;
            this->joueur->fabrique_arme( 4 ) ;
            this->keylistener->left_click_released = false ;
        }

        // vérifie aussi si le joueur appuie sur espace ou si l'autofire est sur true avant de tirer tout en gérant le cooldown de l'arme
        if ( this->joueur->get_arme_equipe()->tir_possible( this->keylistener->tire_munition , this->tir_automatique ) == true )
        {
            if ( this->joueur->get_arme_equipe()->get_nombre_projectiles_tire() != 1 )
            {
                for ( int i = 0 ; i < this->joueur->get_arme_equipe()->get_nombre_projectiles_tire() ; i++ )
                {
                    int angle = i * ( 2 * this->joueur->get_arme_equipe()->get_angle_max() / (this->joueur->get_arme_equipe()->get_nombre_projectiles_tire()-1)) - this->joueur->get_arme_equipe()->get_angle_max() ;
                    this->projectiles_presents->append( this->joueur->get_arme_equipe()->tire( this->joueur->y() , angle ) ) ;
                }
            }
            else
            {
                if ( this->joueur->get_arme_equipe()->get_angle_max() !=  0 )
                {
                    this->projectiles_presents->append( this->joueur->get_arme_equipe()->tire( this->joueur->y() , (qrand() % (this->joueur->get_arme_equipe()->get_angle_max() * 2)) - this->joueur->get_arme_equipe()->get_angle_max() ) ) ;
                }
                else
                {
                    this->projectiles_presents->append( this->joueur->get_arme_equipe()->tire( this->joueur->y() ) ) ;
                }
            }
        }

        for ( QVector<Projectiles*>::iterator bullet_checked = this->projectiles_presents->begin() ; bullet_checked != this->projectiles_presents->end() ; ++bullet_checked )
        {
            (*bullet_checked)->move_projectile() ;
            if ( (*bullet_checked)->x() > scene->width() - (*bullet_checked)->get_largeur_balle() || (*bullet_checked)->y() > this->hauteur_spawn_max || (*bullet_checked)->y() + (*bullet_checked)->get_hauteur_balle() < 0 )
            { // delete la balles lorsqu'elle quitte la zone visible
                delete (*bullet_checked) ;
                (*bullet_checked) = nullptr ;
                this->projectiles_presents->erase( bullet_checked ) ;
                --bullet_checked ;
            }
        }

        // gestion du spawn d'ennemi
        if ( this->attente_prochain_spawn > 0 )
        {
            this->attente_prochain_spawn-- ;
        }
        else if ( this->numero_ennemi_spawned < this->niveau_actuel->get_spawn_order()->size() )
        {
            this->niveau_actuel->get_spawn_ennemi()->append( spawn_ennemi( this->scene , this->niveau_actuel->get_spawn_order()->at(this->numero_ennemi_spawned) ) ) ;
            this->attente_prochain_spawn = this->niveau_actuel->get_delais_spawn() + this->niveau_actuel->get_spawn_ennemi()->last()->get_delais_spawn() ;
            this->numero_ennemi_spawned++ ;
        }

        this->nombre_ennemi_mort += gestion_ennemis( this->bunker , this->niveau_actuel->get_spawn_ennemi() , this->projectiles_presents , this->explosions_presentes ) ;

        // vérifie les conditions de fin de niveau
        if ( this->bunker->detruite() == true )
        {
            this->change_endroit_actuel( 4 ) ;
        }
        else if ( this->nombre_ennemi_mort == this->niveau_actuel->get_spawn_order()->size() )
        {
            if ( this->numero_niveau_actuel < 4 )
            {
                this->bunker->reparation_totale() ;
                this->change_endroit_actuel( 5 ) ;
                this->numero_niveau_actuel++ ;
            }
            else
            {
                this->change_endroit_actuel( 3 ) ;
            }
        }

        for ( QVector<Explosion*>::iterator explosion_advance = this->explosions_presentes->begin() ; explosion_advance != this->explosions_presentes->end() ; ++explosion_advance )
        { // faire un QVector peut sembler bizarre vu que je ne dépasse pas les 1 explosions simultanées actuellement mais il était prévu d'avoir des touelles et des actions spéciales donc bon...
            if ( (*explosion_advance)->explosion_en_cours() == false ) // vaut false quand l'explosion est finie
            {
                delete (*explosion_advance) ;
                (*explosion_advance) = nullptr ;
                explosion_advance = this->explosions_presentes->erase( explosion_advance ) ;
                --explosion_advance ;
            }
        }
    }
    else
    {
        if ( this->option == false )
        {
            if ( this->items_deja_present == false )
            {
                this->items_deja_present = true ;
                this->interface_graphique->affiche_pause() ;
            }

            if ( this->keylistener->left_click_pressed == true )
            {
                this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() ) ;
            }
            if ( this->keylistener->left_click_released == true )
            {
                this->pause = false ;
                this->keylistener->left_click_released = false ;
                switch (this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() , true ) )
                {
                case 3 :
                    this->interface_graphique->remove_item_from_scene( 2 , 1 ) ;
                    break ;
                case 4 :
                    this->option = true ;
                    this->items_deja_present = false ;
                    this->pause = true ;
                    break ;
                case 5 :
                    this->interface_graphique->remove_item_from_scene() ;
                    this->change_endroit_actuel( 1 ) ;
                    delete this->niveau_actuel ;
                    this->niveau_actuel = nullptr ;
                    break ;
                case 6 :
                    this->interface_graphique->remove_item_from_scene() ;
                    this->change_endroit_actuel( 0 ) ;
                    break ;
                default :
                    this->pause = true ;
                    break ;
                }
            }

            if ( this->keylistener->fin == true )
            {
                this->keylistener->fin = false ;
                this->pause = false ;
                this->interface_graphique->remove_item_from_scene( 2 , 1 ) ;
            }
        }
        else
        {
            this->menu_option() ;
        }
    }
}

/**
 * @brief Frame::loosing_screen écran de défaite du jeu
 * annonce la difficile nouvelle au joueur qu'il doit tout recommencer :)
 */

void Frame::loosing_screen()
{
    if ( this->items_deja_present == false )
    {
        this->interface_graphique->affiche_loose() ;
        this->items_deja_present = true ;
    }

    if ( this->keylistener->fin == true || this->keylistener->validation == true )
    {
        this->keylistener->fin = false ;
        this->keylistener->validation = false ;
        this->change_endroit_actuel( 6 ) ;
    }
}

/**
 * @brief Frame::winning_screen écran de victoire du jeu
 * annonce au joueur qu'il peut enfin laisser de côté le jeu car il l'a fini :)
 */

void Frame::winning_screen()
{
    if ( this->items_deja_present == false )
    {
        this->interface_graphique->affiche_win() ;
        this->items_deja_present = true ;
    }

    if ( this->keylistener->fin == true || this->keylistener->validation == true )
    {
        this->keylistener->fin = false ;
        this->keylistener->validation = false ;
        this->change_endroit_actuel( 6 ) ;
    }
}

/**
 * @brief Frame::menu_option menu option du jeu (plusieurs choses n'ont pas été implémenté donc c'est normal que des if soient vide^^')
 */

void Frame::menu_option()
{
    if ( this->items_deja_present == false )
    {
        this->nb_image_dans_scene_sans_le_menu_option = this->interface_graphique->get_nb_image() ;
        this->nb_texte_dans_scene_sans_le_menu_option = this->interface_graphique->get_nb_texte() ;
        this->interface_graphique->affiche_option( this->tir_automatique ) ;
        this->items_deja_present = true ;
    }

    if ( this->keylistener->fin == true )
    {
        this->keylistener->fin = false ;
        this->interface_graphique->remove_item_from_scene( this->nb_image_dans_scene_sans_le_menu_option , this->nb_texte_dans_scene_sans_le_menu_option ) ;
        this->option = false ;
    }

    if ( this->keylistener->validation == true )
    {

    }

    if ( this->keylistener->left_click_pressed == true )
    {

    }

    if ( this->keylistener->left_click_released == true )
    {
        this->keylistener->left_click_released = false ;
        int clicked_button = this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() , true ) ;
        if ( this->nb_image_dans_scene_sans_le_menu_option + 1 == clicked_button )
        { // switch impossible même en utilisant une variable locale const...
            this->interface_graphique->music_muted = !this->interface_graphique->music_muted ;
            this->jukebox->mute_music( this->interface_graphique->music_muted ) ;
        }
        if ( this->nb_image_dans_scene_sans_le_menu_option + 2 == clicked_button )
        {
            this->tir_automatique = !this->tir_automatique ;
        }
    }
}

/**
 * @brief Frame::upgrade_screen écran d'upgrade du jeu (informations en bas de l'écran, conditions d'upgrade/débloquage des armes non implémenté)
 * permet au joueur d'améliorer ses armes
 */

void Frame::upgrade_screen()
{
    if ( this->items_deja_present == false )
    {
        this->items_deja_present = true ;
        this->interface_graphique->affiche_upgrade( this->joueur->get_arme_equipe() , this->joueur->get_nb_armes_possede() ) ;
        this->arme_upgrade_show = this->joueur->get_arme_equipe()->get_id_arme() ;
    }

    if ( this->keylistener->left_click_released == true )
    {
        this->keylistener->left_click_released = false ;
        int clicked_button = this->interface_graphique->is_clicked( this->view->cursor().pos().x() , this->view->cursor().pos().y() , true ) ;
        switch ( clicked_button )
        {
        case 1 :
            this->arme_upgrade_show-- ;
            if ( this->arme_upgrade_show < 0 )
            {
                this->arme_upgrade_show = this->joueur->get_nb_armes_possede() - 1 ;
            }
            this->keylistener->choix_arme = this->arme_upgrade_show ;
            this->joueur->change_arme_equipe( this->arme_upgrade_show ) ;
            break ;
        case 2 :
            this->arme_upgrade_show++ ;
            if ( this->arme_upgrade_show >= this->joueur->get_nb_armes_possede() )
            {
                this->arme_upgrade_show = 0 ;
            }
            this->keylistener->choix_arme = this->arme_upgrade_show ;
            this->joueur->change_arme_equipe( this->arme_upgrade_show ) ;
            break ;
        case 4 :
            this->joueur->get_arme_equipe()->ameliore_arme( 0 ) ;
            break ;
        case 5 :
            this->joueur->get_arme_equipe()->ameliore_arme( 1 ) ;
            break ;
        case 6 :
            this->joueur->get_arme_equipe()->ameliore_arme( 2 ) ;
            break ;
        default :
            break ;
        }
        this->interface_graphique->remove_item_from_scene( 3 ) ;
        this->interface_graphique->affiche_upgrade( this->joueur->get_arme_equipe() , this->joueur->get_nb_armes_possede() , true ) ;
    }

    if ( this->arme_upgrade_show != this->keylistener->choix_arme ) // permet de changer l'arme visualisée comme en jeu
    {
        if ( this->keylistener->choix_arme < this->joueur->get_nb_armes_possede() )
        {
            this->arme_upgrade_show = this->keylistener->choix_arme ;
            this->joueur->change_arme_equipe( this->arme_upgrade_show ) ;
            this->interface_graphique->remove_item_from_scene( 3 ) ;
            this->interface_graphique->affiche_upgrade( this->joueur->get_arme_equipe() , this->joueur->get_nb_armes_possede() , true ) ;
        }
        else
        {
            this->keylistener->choix_arme = this->arme_upgrade_show ; // limite le nombre de calcul
        }
    }

    if ( this->keylistener->fin == true || this->keylistener->validation == true )
    {
        this->keylistener->fin = false ;
        this->keylistener->validation = false ;
        this->change_endroit_actuel( 2 ) ;
    }
}

/**
 * @brief Frame::credit_screen écran de crédit du jeu
 * permet d'informer le joueur sur le contenu du jeu (n'ayant que prit des choses et non eut de communication avec les divers artiste j'ai mit le liens des images et non le noms des artistes... ils n'ont personnellement joué aucun rôle dans la conception du jeu après tout)
 */

void Frame::credit_screen()
{
    if ( this->items_deja_present == false )
    {
        this->items_deja_present = true ;
        this->interface_graphique->affiche_credit() ;
    }

    if ( this->keylistener->fin == true || this->keylistener->validation == true )
    {
        this->keylistener->fin = false ;
        this->keylistener->validation = false ;
        this->change_endroit_actuel( 1 ) ;
    }

    if ( this->keylistener->give_me_a_B == true && this->keylistener->give_me_a_U == true && this->keylistener->give_me_a_G == true )
    {
        try // même dans un try/catch, si le programme bug tout est stoppé donc bon ce n'est pas autant pratique qu'en java car il faut faire un chemin qui marche et dire au programme d'avertir le programmeur qu'il y a un bug... autant faire le même if avec un cout/qDebug sans le try catch car ça revient au même et est plus simple à faire...
        {
            if ( this->numero_niveau_actuel == 0 ) // le joueur doit lancer le programme puis aller dans crédit directement pour que cela soit possible
            {
                int n = 2 ;
                throw n ;
            }
        }
        catch( int )
        {
            cout << "give me a B-U-G !!! (ou pas en fait)" << endl ;
        }
    }
}

#endif // frame_cpp
