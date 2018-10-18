TEMPLATE = app
CONFIG += console c++11 c++14 c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    chatserver.cpp \
    client.cpp

HEADERS += \
    chatserver.h \
    client.h
LIBS += -lpthread -pthread

unix|win32: LIBS += -ljsoncpp

FORMS += \
    form.ui
