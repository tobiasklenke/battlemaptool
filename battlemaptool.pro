QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlemap.cpp \
    battlemapscene.cpp \
    battlemapsquare.cpp \
    dialog_newbattlemap.cpp \
    main.cpp \
    mainwindow.cpp \
    screencalc.cpp

HEADERS += \
    battlemap.h \
    battlemapscene.h \
    battlemapsquare.h \
    defines.h \
    dialog_newbattlemap.h \
    mainwindow.h \
    screencalc.h

FORMS += \
    dialog_newbattlemap.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    images.qrc
