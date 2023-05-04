# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Build folder for .o files
BUILD = ObjectFiles
# Object files
OBJ = $(BUILD)/main.o $(BUILD)/job.o $(BUILD)/mom.o $(BUILD)/kid.o $(BUILD)/jobTable.o $(BUILD)/tools.o $(BUILD)/Socket.o
# Compile target
TARGET = Sockets

# Link object files and produce executable
$(TARGET): $(BUILD) $(OBJ)
	c++ $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Delete executable and build folder
clean:
	rm -r $(BUILD) $(TARGET) $(OBJ)

# Make build directory
$(BUILD):
	mkdir -p $(BUILD)

# Dependencies
$(BUILD)/main.o: main.cpp mom.hpp kid.hpp job.hpp jobTable.hpp tools.hpp Socket.hpp
	c++ $(CXXFLAGS) -c main.cpp -o $(BUILD)/main.o

$(BUILD)/job.o: job.cpp job.hpp
	c++ $(CXXFLAGS) -c job.cpp -o $(BUILD)/job.o

$(BUILD)/mom.o: mom.cpp mom.hpp
	c++ $(CXXFLAGS) -c mom.cpp -o $(BUILD)/mom.o

$(BUILD)/kid.o: kid.cpp kid.hpp
	c++ $(CXXFLAGS) -c kid.cpp -o $(BUILD)/kid.o

$(BUILD)/jobTable.o: jobTable.hpp jobTable.cpp
	c++ $(CXXFLAGS) -c jobTable.cpp -o $(BUILD)/jobTable.o

$(BUILD)/tools.o: tools.cpp tools.hpp
	c++ $(CXXFLAGS) -c tools.cpp -o $(BUILD)/tools.o

$(BUILD)/Socket.o: Socket.cpp Socket.hpp
	c++ $(CXXFLAGS) -c Socket.cpp -o $(BUILD)/Socket.o
