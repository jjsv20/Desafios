TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ControlReservaciones.cpp \
        alojamiento.cpp \
        main.cpp \
        manejoreservas.cpp \
        reservacion.cpp \
        reservas.cpp \
        sesion.cpp \
        usuario.cpp

HEADERS += \
    alojamiento.h \
    manejoreservas.h \
    reservacion.h \
    reservas.h \
    sesion.h \
    usuario.h
