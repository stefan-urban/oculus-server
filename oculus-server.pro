TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_CFLAGS += -std=gnu11

LIBS += -pthread
LIBS += -lboost_system -lboost_thread

SOURCES += \
    main.cpp \
    TcpClient.cpp \
    TcpClients.cpp \
    TcpServer.cpp \
    TcpSession.cpp \
    TcpMessage.cpp \
    vendor/edvstools/Edvs/EventIO.cpp \
    vendor/edvstools/Edvs/EventStream.cpp \
    vendor/edvstools/Edvs/edvs.c \
    EdvsMessage.cpp \
    EdvsEventsCollection.cpp

HEADERS += \
    TcpMessage.hpp \
    TcpSession.hpp \
    TcpClient.hpp \
    TcpServer.hpp \
    TcpClients.hpp \
    vendor/edvstools/Edvs/edvs.h \
    vendor/edvstools/Edvs/edvs_impl.h \
    vendor/edvstools/Edvs/event.h \
    vendor/edvstools/Edvs/Event.hpp \
    vendor/edvstools/Edvs/EventIO.hpp \
    vendor/edvstools/Edvs/EventStream.hpp \
    EdvsEventsCollection.h \
    EdvsMessage.h

