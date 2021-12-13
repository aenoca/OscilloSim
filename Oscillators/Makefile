CXX = g++
CC = $(CXX)
#CXXFLAGS = -std=c++17 -Wall
#LDLIBS = -lm

MODULES= oscillator.o constants.o pendulum.o spring.o weightedpendulum.o doublependulum.o springpendulum.o 

liboscillo.so: $(MODULES)
	$(CC) -shared $^ -o $@

%.o: %.cpp
	$(CC) -fpic -c $^ -o $@

clean:
	rm -r *.o