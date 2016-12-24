# avg_price
# See LICENSE file for copyright and license details.

include config.mk

SRC = avg_price.c functions.c
OBJ = ${SRC:.c=.o}
VPATH = .:c_generic:modules

all: options avg_price

options:
	@echo avg_price build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

avg_price: ${OBJ}
	@echo CC -o $@ ${OBJ} ${LDFLAGS}
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning...
	@rm -fv avg_price ${OBJ} avg_price-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p avg_price-${VERSION}
	@cp -R LICENSE.txt Makefile README.adoc config.def.h config.mk \
		avg_price.1 avg_price.h ${SRC} avg_price-${VERSION}
	@tar -cf avg_price-${VERSION}.tar avg_price-${VERSION}
	@gzip avg_price-${VERSION}.tar
	@rm -rf avg_price-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f avg_price ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/avg_price
	@echo installing gnuplot scripts to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${SHARE}/avg_price
	@cp -rfv gnuplot ${DESTDIR}${SHARE}/avg_price/gnuplot
	@chmod 644 ${DESTDIR}${SHARE}/avg_price/gnuplot/*
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < avg_price.1 > ${DESTDIR}${MANPREFIX}/man1/avg_price.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/avg_price.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/avg_price
	@echo removing data in /usr/local/share from ${DESTDIR}${SHARE}/avg_price
	@rm -rf ${DESTDIR}${SHARE}/avg_price
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/avg_price.1

.PHONY: all options clean dist install uninstall
