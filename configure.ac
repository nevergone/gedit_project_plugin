dnl a megjegyzeseket a "dnl" utan lehet irni

dnl itt kell megadni a konyvtarat, ahol a program forrasa talalhato
AC_INIT(src)
dnl az autoconf -os valtozokat ezen a fileneven fogja eltarolni
AM_CONFIG_HEADER(config.h)
dnl itt alap CFLAG -eket lehet beallitani a forditashoz a gcc -nek
CFLAGS="-pipe -Wall"
dnl a csomag neve, erdemes kitolteni, bekerul a config.h -ba
PACKAGE_NAME=project_plugin
PACKAGE=$PACKAGE_NAME
dnl es a csomag verzioja, ez is bekerul
PACKAGE_VERSION=0.1

dnl itt inicializaljuk az automake -t
AM_INIT_AUTOMAKE($PACKAGE_NAME,$PACKAGE_VERSION)
dnl itt az jon, amiket mindenkeppen ellenorizni fog a configure
dnl ezek az alap glibc headereket ellenorzi, valamint az intltool -t
AC_PROG_CC
AC_LANG_C
AC_STDC_HEADERS
AC_PROG_INSTALL
AC_PROG_INTLTOOL
AC_PROG_LIBTOOL

dnl ha --enable-debug opcio volt atadva a configure -nek, akkor tobbek kozt
dnl olyan binarist forditunk, mely tartalmazza a szukseges adatokat
AC_ARG_ENABLE(debug, [  --enable-debug	Enable debug-friendly compile], debug=yes)
AC_MSG_CHECKING(for GDB DEBUG request)
if test x$debug = xyes; then
	dnl ha debug-modban megy a forditas
	AC_MSG_RESULT(yes)
	dnl beallitunk debug-specifikus forditasi flag -eket, ha az --enable-debug
	dnl kapcsolo lett hasznalva
	CFLAGS="$CFLAGS -DDEBUG -Wall -W -O0 -fno-omit-frame-pointer -ggdb -g3"
	GDB_FLAGS=$CFLAGS
	GDB_DEBUG=yes
	DEBUG=yes
	dnl ez azt jelenti, hogy a config.h -ba vegyen fel egy ilyen sort:
	dnl #define DEBUG yes
	AC_DEFINE_UNQUOTED(DEBUG, "$GDB_DEBUG", [Build debug code ?])
else
	dnl a forditashoz nem hasznalunk debug-modot
	AC_MSG_RESULT(no)
	dnl csak optimalizacios flag -eket hasznalunk a forditashoz
	CFLAGS="$CFLAGS -O2 -ffast-math -fomit-frame-pointer -s"
	GDB_DEBUG=no
fi

dnl ellenorizzuk a forditashoz szukseges fuggvenykonyvtarak megletet
dnl a kovetkezo sor ennek felelne meg:
dnl `pkg-config --cflags --libs gtk+-2.0` `pkg-config --cflags --libs gthread-2.0`
PKG_CHECK_MODULES(DEPS, [
                  glib-2.0 >= 2.4.0
                  gtk+-2.0 >= 2.4.0
                  gtksourceview-1.0 >= 1.1.0
                  libgnomeui-2.0 >= 2.8.0
                  libglade-2.0 >= 2.4.0
                  libgnomeprintui-2.2 >= 2.8.0
                  gedit-2.20 >= 2.20.0
                  ])

dnl kiexportalja a PKG_CHECK_MODULES kimenetet a cflags -ba es a libs -be
dnl ezaltal hozzafuzodik majd a Makefile -hez
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

dnl Gettext hozzaadasa, az "-" -t itt is cserelni kell "_" -re
GETTEXT_PACKAGE=project_plugin
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Gettext Package name])
ALL_LINGUAS="hu"
AM_GLIB_GNU_GETTEXT
AM_PO_SUBDIRS
if test "x$prefix" = "xNONE"; then
  prefix=$ac_default_prefix
  PROJECT_PLUGIN_LOCALEDIR=$ac_default_prefix/share/locale
else
  PROJECT_PLUGIN_LOCALEDIR=$prefix/share/locale
fi
dnl ha "-" jel van a csomag neveben, azt le kell cserelni "_" jelre
AC_DEFINE_UNQUOTED(PROJECT_PLUGIN_LOCALEDIR, "$PROJECT_PLUGIN_LOCALEDIR", [Localedir for language files])

dnl Makefile keszitese :)
AC_OUTPUT([
Makefile
po/Makefile.in
src/Makefile
])

dnl munka vegen par valtozo megjelenitese, es egy kis segitseg a forditashoz :)
echo "Program prefix:       $prefix"
echo "Program localedir:    $PROJECT_PLUGIN_LOCALEDIR"
echo ""
echo "GDB Debug binary:     $GDB_DEBUG"
if test x$debug = xyes; then
  echo "Debug FLAGS:          $GDB_FLAGS"
fi
echo ""
echo "Now configure ready. Type make to compile the program."
