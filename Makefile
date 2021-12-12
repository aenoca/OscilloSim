CXX = g++
CC = $(CXX)
#CXXFLAGS = -std=c++17 -Wall
#LDLIBS = -lm

D=Display
S=Simulation
O=Oscillators

OscilloSimText: main.o system.o integrator.o integratoreuler.o drawingsupport.o weightedpendulum.o doublependulum.o
	$(CC) main.o system.o integrator.o oscillator.o integratoreuler.o drawingsupport.o -o OscilloSimText

main.o: main.cpp $(S)/system.h $(S)/integratoreuler.h $(D)/drawingsupport.h $(O)/weightedpendulum.h $(O)/doublependulum.h
	$(CC) -c main.cpp


drawingsupport.o: $(D)/drawingsupport.cpp $(D)/drawingsupport.h

drawable.o: $(D)/drawable.cpp $(D)/drawingsupport.h $(D)/drawable.h 
	$(CC) -c $(D)/drawable.cpp

# oscillators

oscillator.o: $(O)/oscillator.cpp $(O)/oscillator.h $(D)/drawable.h $(S)/vector.h $(D)/drawingsupport.h
	$(CC) -c $(O)/oscillator.cpp

pendulum.o: $(O)/pendulum.cpp $(O)/pendulum.h $(O)/oscillator.h
	$(CC) -c $(O)/pendulum.cpp

weightedpendulum.o: $(O)/weightedpendulum.cpp $(O)/weightedpendulum.h $(O)/pendulum.h $(S)/constants.h $(D)/drawingsupport.h
	$(CC) -c $(O)/weightedpendulum.cpp

doublependulum.o: $(O)/doublependulum.cpp $(O)/doublependulum.h $(O)/weightedpendulum.h $(S)/constants.h $(D)/drawingsupport.h
	$(CC) -c $(O)/doublependulum.cpp

spring.o: $(O)/spring.cpp $(O)/spring.h $(O)/oscillator.h $(D)/drawingsupport.h $(S)/constants.h
	$(CC) -c $(O)/spring.cpp

springpendulum.o: $(O)/springpendulum.cpp $(O)/springpendulum.h $(O)/pendulum.h $(O)/spring.h $(S)/constants.h $(D)/drawingsupport.h
	$(CC) -c $(O)/springpendulum.cpp


# integrators

integratoreuler.o: $(S)/integratoreuler.cpp $(S)/integratoreuler.h $(S)/integrator.h $(O)/oscillator.h
	$(CC) -c $(S)/integratoreuler.cpp

integratoreulercromer.o: $(S)/integratoreulercrom.cpp $(S)/integratoreulercromer.h $(S)/integrator.h $(O)/oscillator.h
	$(CC) -c $(S)/integratoreulercromer.cpp

integratornewmark.o: $(S)/integratornewmark.cpp $(S)/integratornewmark.h $(S)/integrator.h $(O)/oscillator.h
	$(CC) -c $(S)/integratornewmark.cpp

integratoreuler.o: $(S)/integratorrungekutta.cpp $(S)/integratorrungekutta.h $(S)/integrator.h $(O)/oscillator.h
	$(CC) -c $(S)/integratorrungekutta.cpp

# others

system.o: $(S)/system.cpp $(S)/system.h $(D)/drawable.h $(D)/drawingsupport.h $(O)/oscillator.h $(S)/integrator.h
	$(CC) -c $(S)/system.cpp

vector.o: $(S)/vector.cpp $(S)/vector.h
	$(CC) -c $(S)/vector.cpp






SRC=../Src
BUILD=Build
PRO=Protocol

TARGET = OscilloSimText
TARGETo = $(TARGET).o
TARGETcpp = $(TARGET).cpp

ROSDIST = noetic

ROSoptions = -I/opt/ros/$(ROSDIST)/include -L/opt/ros/$(ROSDIST)/lib -lroscpp -lrostime -lrosconsole -lroscpp_serialization

# check out wildcard
# SRC = src
# SOURCES := $(wildcard $(SRC)/*.cpp)


$(TARGET): $(TARGETo) IOBus.o MessageBus.o NetworkBus.o NetworkClientIO.o NetworkServerIO.o
	$(CC) -pthread $(TARGETo) IOBus.o MessageBus.o NetworkBus.o NetworkClientIO.o NetworkServerIO.o -o $(TARGET) $(ROSoptions)

$(TARGETo): $(TARGETcpp) $(SRC)/$(BUILD)/Build.h $(SRC)/RoCo.h handlers_cs.h
	$(CC) -c $(TARGETcpp) $(ROSoptions)

IOBus.o: $(SRC)/IOBus.cpp $(SRC)/IOBus.h $(SRC)/MessageBus.h
	$(CC) -c $(SRC)/IOBus.cpp
MessageBus.o: $(SRC)/MessageBus.cpp $(SRC)/MessageBus.h
	$(CC) -c $(SRC)/MessageBus.cpp
NetworkBus.o: $(SRC)/NetworkBus.cpp $(SRC)/$(PRO)/Protocol.h $(SRC)/NetworkBus.h $(SRC)/IOBus.h
	$(CC) -c $(SRC)/NetworkBus.cpp
NetworkClientIO.o: $(SRC)/NetworkClientIO.cpp $(SRC)/NetworkClientIO.h $(SRC)/IODriver.h $(SRC)/NetworkIO.h
	$(CC) -c -pthread $(SRC)/NetworkClientIO.cpp
NetworkServerIO.o: $(SRC)/NetworkServerIO.cpp $(SRC)/NetworkServerIO.h $(SRC)/IODriver.h $(SRC)/NetworkIO.h
	$(CC) -c -pthread $(SRC)/NetworkServerIO.cpp

clean:
	rm -r *.o $(TARGET)