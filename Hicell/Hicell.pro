#-------------------------------------------------
#
# Project created by QtCreator 2019-04-17T12:39:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hicell
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        alertainventario.cpp \
        cambiar.cpp \
        clave.cpp \
        crearusuario.cpp \
        dialog.cpp \
        egreso.cpp \
        eliminar.cpp \
        formapago.cpp \
        ingresos.cpp \
        inventario.cpp \
        main.cpp \
        agregar.cpp \
        modificar.cpp \
        venta.cpp

HEADERS += \
        agregar.h \
        alertainventario.h \
        cambiar.h \
        clave.h \
        crearusuario.h \
        dialog.h \
        egreso.h \
        eliminar.h \
        formapago.h \
        ingresos.h \
        inventario.h \
        modificar.h \
        venta.h

FORMS += \
        agregar.ui \
        alertainventario.ui \
        cambiar.ui \
        clave.ui \
        crearusuario.ui \
        dialog.ui \
        egreso.ui \
        eliminar.ui \
        formapago.ui \
        ingresos.ui \
        inventario.ui \
        modificar.ui \
        venta.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

RC_FILE = recourse.rc

