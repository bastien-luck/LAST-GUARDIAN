#-------------------------------------------------
#
# Project created by QtCreator 2018-10-19T11:59:56
#
#-------------------------------------------------

QT       += \
    core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet_cpp_LAST_GUARDIAN
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 \
	resources_big

SOURCES += \
        main.cpp \
    armes.cpp \
    base.cpp \
    boss.cpp \
    ennemis.cpp \
    fonction_globale.cpp \
    guardian.cpp \
    niveau.cpp \
    projectiles.cpp \
    gestion_input.cpp \
    frame.cpp \
    barre_de_vie.cpp \
    mob_slime.cpp \
    mob_skeleton.cpp \
    weapon_blaster_basique.cpp \
    weapon_blaster_sniper.cpp \
    projectile_lourd.cpp \
    projectile_basique.cpp \
    weapon_blaster_corrosif.cpp \
    projectile_corrosif.cpp \
    gui.cpp \
    weapon_blaster_minigun.cpp \
    projectile_rapide.cpp \
    weapon_blaster_explosif.cpp \
    projectile_explosif.cpp \
    gestion_son.cpp \
    mob_mushroom.cpp \
    boss_summoner.cpp \
    explosion.cpp

HEADERS += \
    armes.h \
    base.h \
    boss.h \
    ennemis.h \
    fonction_globale.h \
    guardian.h \
    niveau.h \
    projectiles.h \
    gestion_input.h \
    frame.h \
    barre_de_vie.h \
    mob_slime.h \
    mob_skeleton.h \
    weapon_blaster_basique.h \
    weapon_blaster_sniper.h \
    projectile_lourd.h \
    projectile_basique.h \
    weapon_blaster_corrosif.h \
    projectile_corrosif.h \
    gui.h \
    weapon_blaster_minigun.h \
    projectile_rapide.h \
    weapon_blaster_explosif.h \
    projectile_explosif.h \
    gestion_son.h \
    mob_mushroom.h \
    boss_summoner.h \
    explosion.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
