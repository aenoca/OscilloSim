CXX = g++
CC = $(CXX)
#CXXFLAGS = -std=c++17 -Wall
#LDLIBS = -lm

MODULES= integrator.o integratoreuler.o integratoreulercromer.o integratornewmark.o integratorrungekutta.o system.o vector.o 

libsim.so: $(MODULES)
	$(CC) -shared $^ -o $@

%.o: %.cpp
	$(CC) -fpic -c $^ -o $@

clean:
	rm -r *.o libsim.so