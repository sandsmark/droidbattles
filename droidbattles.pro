TEMPLATE = app
TARGET = droidbattles
QT += widgets
CONFIG += c++11

#CONFIG += sanitizer sanitize_address sanitize_undefined

windows {
    CONFIG += static exceptions_off rtti_off stl_off
}

# Input
HEADERS += src/armor.h \
           src/battlearea.h \
           src/beam.h \
           src/beamer.h \
           src/botinfo.h \
           src/chaff.h \
           src/chafflauncher.h \
           src/chiller.h \
           src/cloaker.h \
           src/commonsymbols.h \
           src/communication.h \
           src/confedit.h \
           src/confstruct.h \
           src/cpu.h \
           src/createbot.h \
           src/debugcontents.h \
           src/debugwindow.h \
           src/devchoice.h \
           src/device.h \
           src/docbrowser.h \
           src/droidbattles.h \
           src/engine.h \
           src/explosion.h \
           src/fuel.h \
           src/infobox.h \
           src/instruktion.h \
           src/kothtournament.h \
           src/matchresult.h \
           src/mine.h \
           src/minelayer.h \
           src/missile.h \
           src/myqmultilineedit.h \
           src/pixbutton.h \
           src/pixmapholder.h \
           src/plasma.h \
           src/radarmissile.h \
           src/radarmissilelauncher.h \
           src/ram.h \
           src/repair.h \
           src/resource.h \
           src/robcpu.h \
           src/robots.h \
           src/rocket.h \
           src/rocketlauncher.h \
           src/scandetect.h \
           src/scanner.h \
           src/screenobject.h \
           src/shield.h \
           src/startcup.h \
           src/startdeathbatt.h \
           src/startsbatt.h \
           src/startsurvbatt.h \
           src/starttournament.h \
           src/steering.h \
           src/textmodebattlearea.h \
           src/textmodefilemanip.h \
           src/timedev.h \
           src/turret.h \
           src/battleconfig.h

SOURCES += src/armor.cpp \
           src/battlearea.cpp \
           src/beam.cpp \
           src/beamer.cpp \
           src/botinfo.cpp \
           src/chaff.cpp \
           src/chafflauncher.cpp \
           src/chiller.cpp \
           src/cloaker.cpp \
           src/communication.cpp \
           src/confedit.cpp \
           src/cpu.cpp \
           src/createbot.cpp \
           src/debugwindow.cpp \
           src/devchoice.cpp \
           src/device.cpp \
           src/docbrowser.cpp \
           src/droidbattles.cpp \
           src/engine.cpp \
           src/explosion.cpp \
           src/fuel.cpp \
           src/infobox.cpp \
           src/instruktion.cpp \
           src/kothtournament.cpp \
           src/main.cpp \
           src/mine.cpp \
           src/minelayer.cpp \
           src/missile.cpp \
           src/myqmultilineedit.cpp \
           src/pixbutton.cpp \
           src/pixmapholder.cpp \
           src/plasma.cpp \
           src/radarmissile.cpp \
           src/radarmissilelauncher.cpp \
           src/ram.cpp \
           src/repair.cpp \
           src/robcpu.cpp \
           src/robots.cpp \
           src/rocket.cpp \
           src/rocketlauncher.cpp \
           src/scandetect.cpp \
           src/scanner.cpp \
           src/screenobject.cpp \
           src/shield.cpp \
           src/startcup.cpp \
           src/startdeathbatt.cpp \
           src/startsbatt.cpp \
           src/startsurvbatt.cpp \
           src/starttournament.cpp \
           src/steering.cpp \
           src/textmodebattlearea.cpp \
           src/textmodefilemanip.cpp \
           src/timedev.cpp \
           src/turret.cpp \
           src/confstruct.cpp

RESOURCES += images.qrc \
    configs.qrc \
    doc.qrc
