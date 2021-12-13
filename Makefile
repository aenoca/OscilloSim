CXX = g++
CC = $(CXX)
#CXXFLAGS = -std=c++17 -Wall
#LDLIBS = -lm

D=Display
S=Simulation
O=Oscillators

# $@ is the target of the rule
# $^ all the prerequisites

OscilloSimText: main.o $(D)/libdraw.so $(O)/liboscillo.so $(S)/libsim.so 
	$(CC) $^ -o $@

libs:
	cd Display && make
	cd .. 
	cd Simulation && make
	cd .. 
	cd Oscillators && make
	cd .. 

%.o: %.cpp
	$(CC) -c $^ -o $@

clean:
	rm -r *.o OscilloSimText

cleanlibs:
	cd Display && make clean
	cd .. 
	cd Simulation && make clean
	cd .. 
	cd Oscillators && make clean
	cd .. 


# OscilloSimText: main.o system.o integratoreuler.o drawingsupport.o pendulum.o weightedpendulum.o doublependulum.o vector.o oscillator.o drawable.o constants.o
# 	$(CC) main.o system.o integratoreuler.o drawingsupport.o pendulum.o weightedpendulum.o doublependulum.o vector.o oscillator.o drawable.o constants.o -o OscilloSimText


# main.o: main.cpp $(S)/system.h $(S)/integratoreuler.h $(D)/drawingsupport.h $(O)/weightedpendulum.h $(O)/doublependulum.h $(S)/vector.h
# 	$(CC) -c main.cpp


# drawingsupport.o: $(D)/drawingsupport.cpp $(D)/drawingsupport.h
# 	$(CC) -c $(D)/drawingsupport.cpp

# drawable.o: $(D)/drawable.cpp $(D)/drawable.h 
# 	$(CC) -c $(D)/drawable.cpp

# # oscillators

# oscillator.o: $(O)/oscillator.cpp $(O)/oscillator.h $(D)/drawingsupport.h
# 	$(CC) -c $(O)/oscillator.cpp

# pendulum.o: $(O)/pendulum.cpp $(O)/pendulum.h $(O)/oscillator.h
# 	$(CC) -c $(O)/pendulum.cpp

# weightedpendulum.o: $(O)/weightedpendulum.cpp $(O)/weightedpendulum.h $(O)/pendulum.h $(O)/constants.h $(D)/drawingsupport.h
# 	$(CC) -c $(O)/weightedpendulum.cpp

# doublependulum.o: $(O)/doublependulum.cpp $(O)/doublependulum.h $(O)/weightedpendulum.h $(O)/constants.h $(D)/drawingsupport.h
# 	$(CC) -c $(O)/doublependulum.cpp

# spring.o: $(O)/spring.cpp $(O)/spring.h $(O)/oscillator.h $(D)/drawingsupport.h $(O)/constants.h
# 	$(CC) -c $(O)/spring.cpp

# springpendulum.o: $(O)/springpendulum.cpp $(O)/springpendulum.h $(O)/pendulum.h $(O)/spring.h $(O)/constants.h $(D)/drawingsupport.h
# 	$(CC) -c $(O)/springpendulum.cpp


# # integrators

# integratoreuler.o: $(S)/integratoreuler.cpp $(S)/integratoreuler.h $(S)/integrator.h $(O)/oscillator.h
# 	$(CC) -c $(S)/integratoreuler.cpp

# integratoreulercromer.o: $(S)/integratoreulercrom.cpp $(S)/integratoreulercromer.h $(S)/integrator.h $(O)/oscillator.h
# 	$(CC) -c $(S)/integratoreulercromer.cpp

# integratornewmark.o: $(S)/integratornewmark.cpp $(S)/integratornewmark.h $(S)/integrator.h $(O)/oscillator.h
# 	$(CC) -c $(S)/integratornewmark.cpp

# integratorrungekutta.o: $(S)/integratorrungekutta.cpp $(S)/integratorrungekutta.h $(S)/integrator.h $(O)/oscillator.h
# 	$(CC) -c $(S)/integratorrungekutta.cpp

# # others

# system.o: $(S)/system.cpp $(S)/system.h $(D)/drawable.h $(D)/drawingsupport.h $(O)/oscillator.h $(S)/integrator.h
# 	$(CC) -c $(S)/system.cpp

# vector.o: $(S)/vector.cpp $(S)/vector.h
# 	$(CC) -c $(S)/vector.cpp

# constants.o: $(O)/constants.cpp $(O)/constants.h
# 	$(CC) -c $(O)/constants.cpp

# clean:
# 	rm -r *.o OscilloSimText