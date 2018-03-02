####### kdevelop will overwrite this part!!! (begin)##########
dist-hook:
	-perl am_edit

SUBDIRS = droidbattles 

EXTRA_DIST = droidbattles.kdevprj AUTHORS COPYING ChangeLog INSTALL README TODO NEWS droidbattles.lsm 

install-data-local:
	$(mkinstalldirs) /usr/local/battlebots/doc/
	$(INSTALL_DATA) AUTHORS /usr/local/battlebots/doc/AUTHORS
	$(mkinstalldirs) /usr/local/battlebots/doc/
	$(INSTALL_DATA) COPYING /usr/local/battlebots/doc/COPYING
	$(mkinstalldirs) /usr/local/battlebots/doc/
	$(INSTALL_DATA) ChangeLog /usr/local/battlebots/doc/ChangeLog
	$(mkinstalldirs) /usr/local/droidbattles/
	$(INSTALL_DATA) INSTALL /usr/local/droidbattles/INSTALL
	$(mkinstalldirs) /usr/local/droidbattles/
	$(INSTALL_DATA) README /usr/local/droidbattles/README
	$(mkinstalldirs) /usr/local/battlebots/doc/
	$(INSTALL_DATA) TODO /usr/local/battlebots/doc/TODO

uninstall-local:
	-rm -f /usr/local/battlebots/doc/AUTHORS
	-rm -f /usr/local/battlebots/doc/COPYING
	-rm -f /usr/local/battlebots/doc/ChangeLog
	-rm -f /usr/local/droidbattles/INSTALL
	-rm -f /usr/local/droidbattles/README
	-rm -f /usr/local/battlebots/doc/TODO

####### kdevelop will overwrite this part!!! (end)############
# not a GNU package. You can remove this line, if 
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 

