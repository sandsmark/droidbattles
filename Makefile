
CC = g++
QINCLUDEDIR = /usr/lib/qt3/include/
QLIBDIR = /usr/lib/qt3/lib/
QMOC = /usr/lib/qt3/bin/moc
CPPFLAGS = -c -O2 -I$(QINCLUDEDIR)
LDFLAGS = -g -L$(QLIBDIR) -lqt

objects = armor.o battlearea.o beam.o beamer.o botinfo.o chaff.o chafflauncher.o chiller.o cloaker.o \
	communication.o confedit.o cpu.o createbot.o debugwindow.o devchoice.o device.o docbrowser.o \
	droidbattles.o engine.o explosion.o fuel.o installdir.o instruktion.o kothtournament.o \
	mine.o minelayer.o missile.o myqmultilineedit.o pixbutton.o pixmapholder.o plasma.o \
	quickconf.o radarmissile.o radarmissilelauncher.o ram.o repair.o robcpu.o robots.o rocket.o \
	rocketlauncher.o scandetect.o scanner.o screenobject.o shield.o startcup.o startdeathbatt.o \
	startsbatt.o startsurvbatt.o starttournament.o steering.o textmodebattlearea.o \
	textmodefilemanip.o timedev.o turret.o infobox.o

mocobjects = battlearea.moc.o botinfo.moc.o confedit.moc.o createbot.moc.o debugwindow.moc.o \
	devchoice.moc.o docbrowser.moc.o droidbattles.moc.o kothtournament.moc.o myqmultilineedit.moc.o \
	pixbutton.moc.o quickconf.moc.o startcup.moc.o startdeathbatt.moc.o startsbatt.moc.o \
	startsurvbatt.moc.o starttournament.moc.o screenobject.moc.o robots.moc.o

droidbattles: $(objects) $(mocobjects) main.o
	$(CC) $(LDFLAGS) $(objects) $(mocobjects) main.o -o droidbattles

$(objects): %.o: %.cpp %.h
	$(CC) $(CPPFLAGS) $< -o $@

$(mocobjects): %.moc.o: %.h
	$(QMOC) $< -o $*.moc.cpp
	$(CC) $(CPPFLAGS) $*.moc.cpp -o $@

main.o: main.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o
	rm ./droidbattles

install:
	./installation
	
