QT = core quick gui
QT += serialport concurrent

TEMPLATE = app

LIBS += -lgcov
#LIBS += -lwiringPi
QMAKE_CXXFLAGS += -g3 -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage
QMAKE_LFLAGS += -g3 -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage

SOURCES += \
    mainIAS.cpp

include(SerialProtocolImpl.pri)

RESOURCES += \
    qml.qrc
