    CXX=g++
    CXXFLAGS= -Wall -c -O2
    LDFLAGS= -lm

    SOURCES=$(wildcard *.cpp)
    OBJECTS_NAMES=$(SOURCES:.cpp=.o)
    EXECUTABLE=exec

    all: link_objects

    link_objects: $(OBJECTS_NAMES)
			$(CXX) -pthread -std=c++11 $(OBJECTS_NAMES) $(LDFLAGS) -o $(EXECUTABLE)

    %.o: %.cpp
			$(CXX) -pthread -std=c++11 $^ $(CXXFLAGS) -o $@

    clean:
			rm -rf  *.o *.dat *.png *~ $(EXECUTABLE)

    run:
			make clean
			make
			./$(EXECUTABLE)
			    
val:
			make
			valgrind ./$(EXECUTABLE)
			make clean

