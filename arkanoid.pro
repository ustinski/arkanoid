QT += opengl

QMAKE_LFLAGS += -lSDL2 -lSDL2_mixer -lBox2D

SOURCES += \
    main.cpp \
    glwidget.cpp \
    window.cpp \
    gl.cpp \
    gameobjects.cpp \
    physics.cpp \
    listener.cpp \
    background.cpp \
    emesh.cpp \
    mesh.cpp \
    box.cpp \
    deck.cpp \
    ball.cpp \
    arkanoid.cpp \
    fontrenderer.cpp \
    sdlmixer.cpp \
    wavfile.cpp

HEADERS += \
    glwidget.h \
    window.h \
    gl.h \
    gameobjects.h \
    physics.h \
    listener.h \
    background.h \
    emesh.h \
    mesh.h \
    box.h \
    deck.h \
    ball.h \
    arkanoid.h \
    fontrenderer.h \
    sdlmixer.h \
    wavfile.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    font.qrc \
    sounds.qrc

# TODO

# base class for ball and deck
