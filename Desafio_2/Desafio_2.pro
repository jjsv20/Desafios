TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        alojamiento.cpp \
        anfitrion.cpp \
        huesped.cpp \
        main.cpp \
        reservacion.cpp \
        usuario.cpp

HEADERS += \
    alojamiento.h \
    anfitrion.h \
    huesped.h \
    reservacion.h \
    usuario.h

STATECHARTS +=
