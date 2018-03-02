####### kdevelop will overwrite this part!!! (begin)##########

SUBDIRS = droidbattles 

EXTRA_DIST = droidbattles.kdevprj admin AUTHORS COPYING ChangeLog INSTALL README TODO droidbattles.lsm 

install-data-local:
	$(mkinstalldirs) /usr/local/droidbattles/doc/
	$(INSTALL_DATA) $(srcdir)/AUTHORS /usr/local/droidbattles/doc/AUTHORS
	$(mkinstalldirs) /usr/local/droidbattles/
	$(INSTALL_DATA) $(srcdir)/COPYING /usr/local/droidbattles/COPYING
	$(mkinstalldirs) /usr/local/droidbattles/doc/
	$(INSTALL_DATA) $(srcdir)/ChangeLog /usr/local/droidbattles/doc/ChangeLog
	$(mkinstalldirs) /usr/local/droidbattles/doc/
	$(INSTALL_DATA) $(srcdir)/INSTALL /usr/local/droidbattles/doc/INSTALL
	$(mkinstalldirs) /usr/local/droidbattles/
	$(INSTALL_DATA) $(srcdir)/README /usr/local/droidbattles/README

uninstall-local:
	-rm -f /usr/local/droidbattles/doc/AUTHORS
	-rm -f /usr/local/droidbattles/COPYING
	-rm -f /usr/local/droidbattles/doc/ChangeLog
	-rm -f /usr/local/droidbattles/doc/INSTALL
	-rm -f /usr/local/droidbattles/README

####### kdevelop will overwrite this part!!! (end)############
# not a GNU package. You can remove this line, if 
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 

#$(top_srcdir)/configure.in: configure.in.in $(top_srcdir)/subdirs
#	cd $(top_srcdir) && $(MAKE) -f admin/Makefile.common configure.in ;

$(top_srcdir)/subdirs:
	cd $(top_srcdir) && $(MAKE) -f admin/Makefile.common subdirs

$(top_srcdir)/acinclude.m4: $(top_srcdir)/admin/acinclude.m4.in $(top_srcdir)/admin/libtool.m4.in
	@cd $(top_srcdir) && cat admin/acinclude.m4.in admin/libtool.m4.in > acinclude.m4

MAINTAINERCLEANFILES = subdirs configure.in acinclude.m4 configure.files 

package-messages:
	$(MAKE) -f admin/Makefile.common package-messages
	$(MAKE) -C po merge

dist-hook:
	cd $(top_distdir) && perl admin/am_edit -padmin
	cd $(top_distdir) && $(MAKE) -f admin/Makefile.common subdirs
