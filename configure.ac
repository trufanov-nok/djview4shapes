# -*-Shell-script-*-
#
# DjVuLibre DjView
# Copyright (c) 2006-  Leon Bottou
#
# This software is subject to, and may be distributed under,
# the GNU General Public License, either version 2 of the license 
# or (at your option) any later version.
# The license should have accompanied the software or 
# you may obtain a copy of the license from the 
# Free Software Foundation at http://www.fsf.org .
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# ----------------------------------------
# Initialization
# ----------------------------------------

AC_PREREQ([2.67])
AC_INIT([djviewi4poliqarp],[4.7])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(README)
AC_CONFIG_HEADER(config.h:config/config.h.in)
AC_PREFIX_DEFAULT(/usr/local)
AC_CANONICAL_HOST

# Additional libraries
AC_ARG_WITH(extra-includes,
            AS_HELP_STRING([--with-extra-includes=DIR],[Define an additional directory for include files]),
        [ if test -d "$withval" ; then
            CFLAGS="$CFLAGS -I$withval" 
            CXXFLAGS="$CXXFLAGS -I$withval" 
          else
            AC_MSG_ERROR([Cannot stat directory $withval])
          fi ] )

AC_ARG_WITH(extra-libraries,
            AS_HELP_STRING([--with-extra-libraries=DIR],[Define an additional directory for library files]),
        [ if test -d "$withval" ; then
           LDFLAGS="$LDFLAGS -L$withval"
          else
            AC_MSG_ERROR([Cannot stat directory $withval])
          fi ] )

# Always look into a "gnu" directory.
curwd=`pwd`
if test -d $curwd/gnu/include ; then
   CFLAGS="$CFLAGS -I$curwd/gnu/include"   
   CXXFLAGS="$CXXFLAGS -I$curwd/gnu/include"
fi
if test -d $curwd/gnu/lib ; then
   LDFLAGS="$LDFLAGS -L$curwd/gnu/lib"
fi

# Special cases
case "$host" in
  *-darwin* | *-macos10*)
     if test -d /opt/local ; then
       CFLAGS="$CFLAGS -I/opt/local/include"
       CXXFLAGS="$CXXFLAGS -I/opt/local/include"
       LDFLAGS="$LDFLAGS -L/opt/local/lib"
     elif test -d /sw ; then
       CFLAGS="$CFLAGS -I/sw/include"
       CXXFLAGS="$CXXFLAGS -I/sw/include"
       LDFLAGS="$LDFLAGS -L/sw/lib"
     fi
  ;;
esac



# ----------------------------------------
# Programs
# ----------------------------------------

# Does make set variable $(MAKE)
AC_PROG_MAKE_SET

# Programs
AC_PROG_LN_S
AC_PATH_PROG(RM, rm)
AC_PATH_PROG(TOUCH, touch)
AC_PATH_PROG(MKDIR, mkdir)
AC_PATH_PROG(RSVG, rsvg, false)
AC_PATH_PROG(CONVERT, convert, false)
AC_PROG_INSTALL

# Libtool & Compilers
AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)
AC_CXX_OPTIMIZE

# Only nsdejavu needs libtool.
# But some combinations of libtool and autoconf
# break when libtool is in a conditional path.
RM="$RM -f"
AC_DISABLE_STATIC
LT_INIT


# ----------------------------------------
# Header Files
# ----------------------------------------

AC_HEADER_STDC
AC_HEADER_DIRENT
AC_HEADER_TIME
AC_HEADER_SYS_WAIT     
AC_CHECK_HEADERS(unistd.h string.h strings.h)


# ----------------------------------------
# Functions
# ----------------------------------------

AC_FUNC_FORK
AC_CHECK_FUNCS(sigaction strerror waitpid wait3)


# ----------------------------------------
# Packages
# ----------------------------------------

AC_PROG_PKG_CONFIG([],[
  AC_MSG_ERROR([Cannot find required program pkg-config.])
])

AC_PROGS_QT4([],[
  AC_MSG_ERROR([Cannot find required Qt4 programs.])
])

AC_PATH_DDJVUAPI([],[
  AC_MSG_ERROR([Cannot find required package ddjvuapi.])
])

AC_PATH_TIFF([],[
  AC_MSG_WARN([Cannot find libtiff (required for tiff export).])
])



# ----------------------------------------
# nsdejavu
# ----------------------------------------

ac_nsdejavu=yes
AC_ARG_ENABLE(nsdejavu,
    AS_HELP_STRING([--disable-nsdejavu],[Do not compile the nsdejavu browser plugin.]),
    [ac_nsdejavu=$enableval])

if test "$ac_nsdejavu" != no ; then
    AC_PATH_X
    AC_PATH_XTRA
    if test "$no_x" = yes; then
        ac_nsdejavu = no
        AC_MSG_WARN([Disabling plugin compilation (missing X11 include files).])
    fi
    
    ac_xt=yes
    ac_glib=yes
    AC_PATH_GLIB([],[ac_glib=no])
    savedCFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS ${X_CFLAGS}"
    AC_CHECK_HEADER(X11/Shell.h, [], [ac_xt=no])
    AC_CHECK_HEADER(X11/IntrinsicP.h, [], [ac_xt=no])
    CFLAGS="$savedCFLAGS"
    if test "$ac_xt" != no ; then
        AC_DEFINE(HAVE_XT,1,[Define if you have xt include files.])
        if test "$ac_glib" = no ; then
            AC_MSG_WARN([GLib not found. Compiling plugin without XEmbed.])
        fi
    else
        AC_MSG_WARN([Xt not found. Compiling plugin with XEmbed only.])
        if test "$ac_glib" = no ; then
            AC_MSG_WARN([Disabling plugin compilation (need Xt and/or Glib2.)])
        fi
    fi
fi

if test "$ac_nsdejavu" != no ; then
    # prepare flags
    NSDEJAVU_CFLAGS=
    NSDEJAVU_LIBS=
    NSDEJAVU_CFLAGS=${X_CFLAGS}
    case "$host" in
        *-cygwin* | *-mingw*)
            NSDEJAVU_LIBS="`echo ${X_LIBS} | sed -e 's/-lXext/-lXt -lXext/'`"
            NSDEJAVU_LIBS="-no-undefined $NSDEJAVU_LIBS"
            ;;
    esac
    AC_SUBST(NSDEJAVU_CFLAGS)
    AC_SUBST(NSDEJAVU_LIBS)
    # nsdejavu install
    if test -z "$INSTALL_SHLIB" ; then
        INSTALL_SHLIB="${INSTALL_DATA}"
        case "$host" in
            *-cygwin* | *-mingw*)
                INSTALL_SHLIB="cp"
                ;;
        esac
    fi
    AC_SUBST(INSTALL_SHLIB)
    NSDEJAVU_YES=''
    NSDEJAVU_NO='#'
else
    NSDEJAVU_YES='#'
    NSDEJAVU_NO=''
fi
AC_SUBST(NSDEJAVU_YES)
AC_SUBST(NSDEJAVU_NO)


# ----------------------------------------
# npdjvu
# ----------------------------------------

ac_npdjvu=no
AC_ARG_ENABLE(npdjvu,
    AS_HELP_STRING([--enable-npdjvu],[Compile the npdjvu browser plugin.]),
    [ac_npdjvu=$enableval])

if test "$ac_npdjvu" != no ; then
    NPDJVU_YES=''
    NPDJVU_NO='#'
else
    NPDJVU_YES='#'
    NPDJVU_NO=''
fi
AC_SUBST(NPDJVU_YES)
AC_SUBST(NPDJVU_NO)


# ----------------------------------------
# Desktop files
# ----------------------------------------

ac_desktopfiles=yes
AC_ARG_ENABLE(desktopfiles,
    AS_HELP_STRING([--disable-desktopfiles],[Do not install scripts to register icons and menus.]),
    [ac_desktopfiles=$enableval])

# Check for xdg tools
AC_PATH_PROG(XDG_MIME, xdg-mime)
AC_PATH_PROG(XDG_ICON_RESOURCE, xdg-icon-resource)
AC_PATH_PROG(XDG_DESKTOP_MENU, xdg-desktop-menu)
if test -x ${XDG_MIME} && \
   test -x ${XDG_ICON_RESOURCE} && \
   test -x ${XDG_DESKTOP_MENU}
then 
  true
elif test "$ac_desktopfiles" = yes ; then
  ac_desktopfiles=no
  AC_MSG_WARN([Cannot find the Xdg Portland tools.
--------------------------------------------------------
*** The scripts to register icons and menus 
*** ${datadir}/djvu/osi/desktop/register-djvu-mimetype, and
*** ${datadir}/djvu/djview3/desktop/register-djview3-menu
*** will not be installed.
--------------------------------------------------------])
fi

if test ${ac_desktopfiles} != no ; then
  DESKTOP_YES=''
  DESKTOP_NO='#'
else
  DESKTOP_YES='#'
  DESKTOP_NO=''
fi
AC_SUBST(DESKTOP_YES)
AC_SUBST(DESKTOP_NO)



# ----------------------------------------
# Paths
# ----------------------------------------

# Define installation paths and version string
AC_DEFINE_INSTALL_PATHS
AC_DEFINE_VERSION([DJVIEW_VERSION], [${PACKAGE_VERSION}])
AC_DEFINE_UNQUOTED([DJVIEW_VERSION_STR], ["${PACKAGE_VERSION}"], [string])


# ----------------------------------------
# Run qmake
# ----------------------------------------

# autoconf
QARG="CONFIG+=autoconf"
AUTO_LIBS="$DDJVUAPI_LIBS $TIFF_LIBS $LIBS"
AUTO_FLAGS="-I.. $DDJVUAPI_CFLAGS $TIFF_CFLAGS"
#    note: AUTO_FLAGS does not contain $OPTS
#          because qmake determines itself
#          its optimization flags...

# out-of-tree?
if test -d src && test -r src/qdjvu.cpp ; then : ; else
  test -d src || mkdir src
  test -d npdjvu || mkdir npdjvu
  for n in $srcdir/src/*.pro $srcdir/src/*.ts ; do
      m=`basename $n`
      test -r $n && ( cmp -s $n src/$m || cp $n src/$m )
  done
  for n in $srcdir/npdjvu/*.pro ; do
      m=`basename $n`
      test -r $n && ( cmp -s $n npdjvu/$m || cp $n npdjvu/$m )
  done
fi
nsrcdir="$srcdir"
case "$srcdir" in .*) nsrcdir="../$srcdir" ;; esac
AUTO_FLAGS="-I$nsrcdir/src $AUTO_FLAGS"

# debug
if test "$ac_debug" = yes ; then
  QARG="$QARG CONFIG+=debug"
else
  QARG="$QARG CONFIG+=release"
fi

# qmake arguments
QARG="$QARG QMAKE_UIC="'"'"$UIC"'"'
QARG="$QARG QMAKE_MOC="'"'"$MOC"'"'
QARG="$QARG QMAKE_RCC="'"'"$RCC"'"'
QARG="$QARG LIBS+="'"'"$AUTO_LIBS"'"'
QARG="$QARG QMAKE_LFLAGS+="'"'"$LDFLAGS"'"'
QARG="$QARG QMAKE_CFLAGS+="'"'"$CFLAGS $AUTO_FLAGS"'"'
QARG="$QARG QMAKE_CXXFLAGS+="'"'"$CXXFLAGS $AUTO_FLAGS"'"'

# qmake environment variables
if test -n "$QMAKESPEC" ; then
    QARG="-spec "'"'"$QMAKESPEC"'"'" $QARG"
fi

# run
AC_CONFIG_COMMANDS([qmake_src], [
    echo "config.status: running $QMAKE_COMMAND1."
    ( cd src ; eval "$QMAKE_COMMAND1" )
],[
    read QMAKE_COMMAND1 <<QMAKE_COMMAND_EOF
$QMAKE $QARG VPATH="$nsrcdir/src"
QMAKE_COMMAND_EOF
] )

if test "$ac_npdjvu" != "no" ; then
AC_CONFIG_COMMANDS([qmake_npdjvu], [
    echo "config.status (npdjvu) running $QMAKE_COMMAND2."
    ( cd npdjvu ; eval "$QMAKE_COMMAND2" )
],[
    read QMAKE_COMMAND2 <<QMAKE_COMMAND_EOF
$QMAKE $QARG VPATH="$nsrcdir/src $nsrcdir/npdjvu"
QMAKE_COMMAND_EOF
] )
fi


# ----------------------------------------
# Outputs
# ----------------------------------------

AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(nsdejavu/Makefile)
AC_CONFIG_FILES(desktopfiles/Makefile)
AC_OUTPUT

# ----------------------------------------
# Fin
# ----------------------------------------

echo ""
echo "Configuration is done."
echo "Compile with command:"
echo "    $ make"
echo "Then install the binaries in $prefix with command:"
echo "    # make install"
