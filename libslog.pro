TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    src/SLog.cpp

HEADERS += \
    src/SLog.hpp \
    src/SharedQueue.hpp \
    src/ActiveInterface.hpp
