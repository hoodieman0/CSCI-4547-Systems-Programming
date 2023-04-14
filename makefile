# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Object files
OBJ = main.o job.o tools.o
# Compile target
TARGET = Threads

# Link object files and produce executable
$(TARGET): $(OBJ)
	c++ $(CXXFLAGS) $(OBJ) -o $(TARGET)
	rm $(OBJ)

# Delete executable
clean:
	rm $(TARGET)

# Dependencies
main.o: main.cpp
	c++ $(CXXFLAGS) -c main.cpp

job.o: job.cpp job.hpp
	c++ $(CXXFLAGS) -c job.cpp

tools.o: tools.cpp tools.hpp
	c++ $(CXXFLAGS) -c tools.cpp