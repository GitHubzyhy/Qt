CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qwbateryplugin)
TEMPLATE    = lib

HEADERS     = qwbateryplugin.h
SOURCES     = qwbateryplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qwbatery.pri)
