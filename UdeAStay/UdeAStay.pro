TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ControlReservaciones.cpp \
        alojamiento.cpp \
        main.cpp \
        reservacion.cpp \
        sesion.cpp \
        usuario.cpp

HEADERS += \
    alojamiento.h \
    reservacion.h \
    sesion.h \
    usuario.h
