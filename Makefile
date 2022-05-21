# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz rm config.h

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	test -e /usr/share/xsessions/dwm.desktop || cp -v dwm.desktop /usr/share/xsessions/
	# test -d ${$HOME}/.dwm || mkdir ${HOME}/.dwm
	# test -e ${HOME}/.dwm/autostart.sh || cp -v autostart.sh ${HOME}/.dwm/
	# test -O ${HOME}/.dwm/autostart.sh || echo "WARN: ~/.dwm/autostart.sh is not owned by the current user!"
	# test -x ${HOME}/.dwm/autostart.sh || echo "WARN: ~/.dwm/autostart.sh is not executable by the current user!"

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

setup:
	echo "setting up for first time use"

	test -d ${$HOMEBIN} || mkdir -p ${HOMEBIN}
	cp -rv scripts/* ${HOMEBIN}/
	chmod 700 ${HOMEBIN}/*.sh
	chmod 700 ${HOMEBIN}/extract
	test -d ${CONFIGDIR} || mkdir ${CONFIGDIR}
	test -e ${CONFIGDIR}/autostart.sh || cp -v autostart.sh ${CONFIGDIR}
	test -O ${CONFIGDIR}/autostart.sh || echo "WARN: ~/.dwm/autostart.sh is not owned by the current user!"
	test -x ${CONFIGDIR}/autostart.sh || echo "WARN: ~/.dwm/autostart.sh is not executable by the current user!"
	echo "Done"
	echo "WARN: Remember to make the scripts in ~/bin executable, and owned by the current user"

.PHONY: all options clean dist install uninstall setup
