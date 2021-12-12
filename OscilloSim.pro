QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Oscillators/doublependulum.cpp \
    Oscillators/pendulum.cpp \
    Oscillators/spring.cpp \
    Oscillators/springpendulum.cpp \
    Oscillators/weightedpendulum.cpp \
    Oscillators/constants.cpp \
    Display/drawable.cpp \
    Display/drawingsupport.cpp \
    Simulation/integrator.cpp \
    Oscillators/oscillator.cpp \
    Simulation/integratoreuler.cpp \
    Simulation/integratoreulercromer.cpp \
    Simulation/integratornewmark.cpp \
    Simulation/integratorrungekutta.cpp \
    Simulation/system.cpp \
    Simulation/vector.cpp \
    main.cpp

HEADERS += \
    Oscillators/doublependulum.h \
    Oscillators/pendulum.h \
    Oscillators/spring.h \
    Oscillators/springpendulum.h \
    Oscillators/weightedpendulum.h \
    Oscillators/constants.h \
    Display/drawable.h \
    Display/drawingsupport.h \
    Simulation/integrator.h \
    Oscillators/oscillator.h \
    Simulation/integratoreuler.h \
    Simulation/integratoreulercromer.h \
    Simulation/integratornewmark.h \
    Simulation/integratorrungekutta.h \
    Simulation/system.h \
    Simulation/vector.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
