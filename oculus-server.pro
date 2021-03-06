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
    Message.cpp \
    Robot.cpp \
    vendor/dispatcher/Dispatcher.cpp \
    Message_RobotCommand.cpp \
    Message_RobotBeepCommand.cpp \
    SerialCommunication.cpp \
    Message_EventCollection2.cpp \
    Message_JoystickEvent.cpp \
    App_EdvsCameras.cpp \
    App_Robot.cpp

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
    Message.hpp \
    Robot.hpp \
    vendor/dispatcher/Dispatcher.hpp \
    Message_RobotCommand.hpp \
    Message_RobotBeepCommand.hpp \
    SerialCommunication.hpp \
    Message_EventCollection2.hpp \
    Message_JoystickEvent.hpp \
    App_EdvsCameras.hpp \
    Application.hpp \
    App_Robot.hpp

