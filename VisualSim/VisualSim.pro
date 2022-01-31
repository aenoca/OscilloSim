TEMPLATE = app

QT += openglwidgets
QMAKE_CXXFLAGS += -std=c++17
LIBS += -lOpengl32
QT += widgets

TARGET = OscilloSim

#####
#LIBS += -L../Display -lDisplay
#LIBS += -L../Simulation -lSimulation
#LIBS += -L../Oscillators -lOscillators
##LIBS += -LSimWindow -lSimWindow
##LIBS += -LGUI -lGUI

## LIBS += -L../general -lgeneral

#PRE_TARGETDEPS += ../Display/libDisplay.a
#PRE_TARGETDEPS += ../Simulation/libSimulation.a
#PRE_TARGETDEPS += ../Oscillators/libOscillators.a
##PRE_TARGETDEPS += SimWindow/libSimWindow.a
##PRE_TARGETDEPS += GUI/libGUI.a

INCLUDEPATH += ../Display
INCLUDEPATH += ../Simulation
INCLUDEPATH += ../Oscillators

SOURCES += \
    ../Display/drawable.cpp \
    ../Display/drawingsupport.cpp \
    ../Oscillators/constants.cpp \
    ../Oscillators/oscillator.cpp \
    ../Oscillators/pendulum.cpp \
    ../Oscillators/weightedpendulum.cpp \
    ../Oscillators/spring.cpp \
    ../Oscillators/doublependulum.cpp \
    ../Oscillators/springpendulum.cpp \
    ../Simulation/integrator.cpp \
    ../Simulation/integratoreuler.cpp \
    ../Simulation/integratoreulercromer.cpp \
    ../Simulation/integratornewmark.cpp \
    ../Simulation/integratorrungekutta.cpp \
    ../Simulation/system.cpp \
    ../Simulation/vector.cpp \
    dpendulumpage.cpp \
    pendulumpage.cpp \
    spendulumpage.cpp \
    springpage.cpp \
    homepage.cpp \
    page.cpp \
    window.cpp \
    pageosc.cpp \
    glsphere.cc \
    glwidget.cc \
    view_opengl.cc \
    main.cpp

HEADERS += \
    ../Display/drawable.h \
    ../Display/drawingsupport.h \
    ../Oscillators/constants.h \
    ../Oscillators/oscillator.h \
    ../Oscillators/pendulum.h \
    ../Oscillators/weightedpendulum.h \
    ../Oscillators/spring.h \
    ../Oscillators/doublependulum.h \
    ../Oscillators/springpendulum.h \
    ../Simulation/integrator.h \
    ../Simulation/integratoreuler.h \
    ../Simulation/integratoreulercromer.h \
    ../Simulation/integratornewmark.h \
    ../Simulation/integratorrungekutta.h \
    ../Simulation/system.h \
    ../Simulation/vector.h \
    dpendulumpage.h \
    pendulumpage.h \
    spendulumpage.h \
    springpage.h \
    homepage.h \
    page.h \
    window.h \
    pageosc.h \
    glsphere.h \
    glwidget.h \
    view_opengl.h \
    vertex_shader.h

RESOURCES += resource.qrc

#SOURCES += \
#    GUI/PageOsc/dpendulumpage.cpp \
#    GUI/PageOsc/pendulumpage.cpp \
#    GUI/PageOsc/spendulumpage.cpp \
#    GUI/PageOsc/springpage.cpp \
#    GUI/homepage.cpp \
#    GUI/page.cpp \
#    GUI/window.cpp \
#    GUI/PageOsc/pageosc.cpp \
#    SimWindow/glsphere.cc \
#    SimWindow/glwidget.cc \
#    SimWindow/view_opengl.cc \
#    main.cpp

#HEADERS += \
#    GUI/PageOsc/dpendulumpage.h \
#    GUI/PageOsc/pendulumpage.h \
#    GUI/PageOsc/spendulumpage.h \
#    GUI/PageOsc/springpage.h \
#    GUI/homepage.h \
#    GUI/page.h \
#    GUI/window.h \
#    GUI/PageOsc/pageosc.h \
#    SimWindow/glsphere.h \
#    SimWindow/glwidget.h \
#    SimWindow/view_opengl.h \
#    SimWindow/vertex_shader.h
    

