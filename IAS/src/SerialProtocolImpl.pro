QT = core quick gui
QT += serialport concurrent

TEMPLATE = app

LIBS += -lgcov
QMAKE_CXXFLAGS += -g3 -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage
QMAKE_LFLAGS += -g3 -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage

SOURCES += \
    main.cpp

include(SerialProtocolImpl.pri)

RESOURCES += \
    qml.qrc
