QT       += core widgets
TARGET = Minesweeper
TEMPLATE = app
SOURCES += main.cpp \
           mainwindow.cpp \
           customButton.cpp
HEADERS += mainwindow.h \
    customButton.h
RESOURCES += \
    resources.qrc

DISTFILES += \
    README.md
