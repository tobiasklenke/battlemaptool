QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlemap.cpp \
    battlemapscene.cpp \
    battlemapscenemasterscreen.cpp \
    battlemapsceneplayerscreen.cpp \
    battlemapscenesection.cpp \
    battlemapscenesquareselection.cpp \
    battlemapsquare.cpp \
    customgraphicspixmapitem.cpp \
    customgraphicsview.cpp \
    dialogsettings.cpp \
    main.cpp \
    mainwindow.cpp \
    masterscreenhandler.cpp \
    playerscreenhandler.cpp \
    screencalc.cpp \
    undocommanddeletecolumnleft.cpp \
    undocommanddeletecolumnright.cpp \
    undocommanddeleterowabove.cpp \
    undocommanddeleterowbelow.cpp \
    undocommandinsertcolumnleft.cpp \
    undocommandinsertcolumnright.cpp \
    undocommandinsertrowabove.cpp \
    undocommandinsertrowbelow.cpp \
    undocommandpaste.cpp \
    undocommandrotatebattlemapleft.cpp \
    undocommandrotatebattlemapright.cpp \
    wizardnewbattlemap.cpp

HEADERS += \
    battlemap.h \
    battlemapscene.h \
    battlemapscenemasterscreen.h \
    battlemapsceneplayerscreen.h \
    battlemapscenesection.h \
    battlemapscenesquareselection.h \
    battlemapsquare.h \
    customgraphicspixmapitem.h \
    customgraphicsview.h \
    defines.h \
    dialogsettings.h \
    mainwindow.h \
    masterscreenhandler.h \
    playerscreenhandler.h \
    screencalc.h \
    undocommanddeletecolumnleft.h \
    undocommanddeletecolumnright.h \
    undocommanddeleterowabove.h \
    undocommanddeleterowbelow.h \
    undocommandinsertcolumnleft.h \
    undocommandinsertcolumnright.h \
    undocommandinsertrowabove.h \
    undocommandinsertrowbelow.h \
    undocommandpaste.h \
    undocommandrotatebattlemapleft.h \
    undocommandrotatebattlemapright.h \
    wizardnewbattlemap.h

FORMS += \
    dialogsettings.ui \
    mainwindow.ui \
    wizardnewbattlemap.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    images.qrc
