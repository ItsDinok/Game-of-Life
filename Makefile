CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: life

life: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o life $(SFMLFLAGS)

clean:
	rm -f life
