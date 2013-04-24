QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pong-client
TEMPLATE = app

DEPENDPATH += . headers src
INCLUDEPATH += . headers

UI_HEADERS_DIR += ui

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/renderlabel.cpp \
    src/scene.cpp \
    src/bat.cpp \
    src/jobcannotbedone.cpp \
    src/arena.cpp \
    src/mathutils.cpp \
    src/serveurcommunicator.cpp \
    src/GameState.cpp \
    src/Lockable.cpp \
    src/serversync.cpp \
    src/lobby.cpp

HEADERS  += headers/mainwindow.h \
    headers/renderlabel.h \
    headers/scene.h \
    headers/bat.h \
    headers/jobcannotbedone.h \
    headers/arena.h \
    headers/mathutils.h \
    headers/serveurcommunicator.h \
    headers/GameState.hpp \
    headers/PongTypes.hpp \
    headers/Lockable.hpp \
    headers/serversync.h \
    headers/lobby.h

FORMS    += ui/mainwindow.ui \
    ui/lobby.ui
