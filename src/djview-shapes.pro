# #####################################################################
# Automatically generated by qmake (2.01a) czw. sie 27 19:06:01 2009
# #####################################################################
TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
QT += network

RESOURCES = resources.qrc

TRANSLATIONS = i18n/pl.ts

win32:LIBS = /home/michal/programming/build/djvulibre-windows/libdjvulibre.dll.a
unix:LIBS = -ldjvulibre

!win32 {
HGID = $$system(hg id -n)
DEFINES += HAVE_CONFIG_H HGID=\\\"$$HGID\\\"

versiontarget.target = version.o
versiontarget.depends = FORCE
PRE_TARGETDEPS += version.o
QMAKE_EXTRA_TARGETS += versiontarget
}

# Input
HEADERS += recentfiles.h \
	 mainwindow.h \
	 qdjvuwidget.h \
	 qdjvuhttp.h \
	 qdjvu.h \
	 messagedialog.h \
	 version.h \
	 shapeswidget.h \
	 shapeextractor.h \
    shape.h \
    shapelist.h \
    shapemodel.h \
    blit.h \
    shapedocument.h

SOURCES += recentfiles.cpp \
	 mainwindow.cpp \
	 qdjvuwidget.cpp \
	 qdjvuhttp.cpp \
	 qdjvu.cpp \
	 messagedialog.cpp \
	 version.cpp \
	 main.cpp \
	 shapeswidget.cpp \
	 shapeextractor.cpp \
    shape.cpp \
    shapelist.cpp \
    shapemodel.cpp \
    blit.cpp \
    shapedocument.cpp
FORMS = mainwindow.ui

RESOURCES += \
	 resources.qrc
