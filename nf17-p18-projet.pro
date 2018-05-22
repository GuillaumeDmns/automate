QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    automate.h \
    etat.h \
    interface.h \
    simulateur.h

SOURCES += \
    automate.cpp \
    etat.cpp \
    interface.cpp \
    main.cpp \
    simulateur.cpp
