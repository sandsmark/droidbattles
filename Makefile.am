####### kdevelop will overwrite this part!!! (begin)##########
dist-hook:
	-perl am_edit

SUBDIRS = battlebots 

EXTRA_DIST = battlebots.kdevprj AUTHORS COPYING ChangeLog INSTALL README TODO NEWS battlebots.lsm tracker.basm 

install-data-local:
	$(mkinstalldirs) /usr/local/battlebots/bots/
	$(INSTALL_DATA) tracker.basm /usr/local/battlebots/bots/tracker.basm

uninstall-local:
	-rm -f /usr/local/battlebots/bots/tracker.basm

####### kdevelop will overwrite this part!!! (end)############
# not a GNU package. You can remove this line, if 
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 

