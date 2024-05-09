QT       += core gui positioning quick widgets qml
QT       += sql
QT += network



#PDF
QT += widgets printsupport

LIBS += -L"C:/Qt/Qt5.9.9/Tools/mingw530_32/opt/bin" -lssleay32 -llibeay32

QT += location positioning quickcontrols2
TEMPLATE = app

QT += qml network quick positioning location
CONFIG += qtquickcompiler
QT += quickcontrols2
QT += quickwidgets

CONFIG += qxt
# Workaround for QTBUG-38735
QT_FOR_CONFIG += location-private
qtConfig(geoservices_mapboxgl): QT += sql opengl
qtConfig(geoservices_osm): QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    association.cpp \
    connection.cpp \
    guest.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    association.h \
    connection.h \
    guest.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
