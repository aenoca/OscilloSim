CXX = g++
CC = $(CXX)
#CXXFLAGS = -std=c++17 -Wall
#LDLIBS = -lm

MODULES= drawable.o drawingsupport.o

libdraw.so: $(MODULES)
	$(CC) -shared $^  -o $@

%.o: %.cpp
	$(CC) -fpic -c $^ -o $@

clean:
	rm -r *.o libdraw.so