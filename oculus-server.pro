TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -pthread
LIBS += -lboost_system -lboost_thread

SOURCES += \
    main.cpp \
    TcpClient.cpp \
    TcpClients.cpp \
    TcpServer.cpp \
    TcpSession.cpp \
    TcpMessage.cpp

HEADERS += \
    TcpMessage.hpp \
    TcpSession.hpp \
    TcpClient.hpp \
    TcpServer.hpp \
    TcpClients.hpp

