QT += serialport
QT += network
QT       += core gui charts
QT       += sql
QT += widgets printsupport
QT += texttospeech
greaterThan(QT_MAJOR_VERSION, 4):

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
    arduino.cpp \
    article.cpp \
    artist.cpp \
    association.cpp \
    connection.cpp \
    controller.cpp \
    employee.cpp \
    evenement.cpp \
    guest.cpp \
    main.cpp \
    mainwindow.cpp \
    participer.cpp \
    qr.cpp \
    qrcode.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    article.h \
    artist.h \
    association.h \
    connection.h \
    controller.h \
    employee.h \
    evenement.h \
    guest.h \
    mainwindow.h \
    participer.h \
    qr.h \
    qrcode.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    images.qrc

DISTFILES += \
    audio.py \
    chat.py
