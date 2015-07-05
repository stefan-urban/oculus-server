TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QMAKE_CFLAGS += -std=gnu11

LIBS += -pthread
LIBS += -lboost_system -lboost_thread -lboost_serialization

SOURCES += \
    main.cpp \
    TcpClient.cpp \
    TcpClients.cpp \
    TcpServer.cpp \
    TcpSession.cpp \
    vendor/edvstools/Edvs/EventIO.cpp \
    vendor/edvstools/Edvs/EventStream.cpp \
    vendor/edvstools/Edvs/edvs.c \
    EdvsEventsCollection.cpp \
    Message.cpp \
    Message_EventCollection.cpp \
    Robot.cpp \
    vendor/dispatcher/Dispatcher.cpp \
    Message_RobotCommand.cpp \
    Message_RobotBeepCommand.cpp \
    SerialCommunication.cpp \
    Message_EventWithoutTimestampCollection.cpp

HEADERS += \
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
    EdvsEventsCollection.hpp \
    Message.hpp \
    Message_EventCollection.hpp \
    Robot.hpp \
    vendor/dispatcher/Dispatcher.hpp \
    Message_RobotCommand.hpp \
    Message_RobotBeepCommand.hpp \
    SerialCommunication.hpp \
    Message_EventWithoutTimestampCollection.hpp

