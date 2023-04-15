# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Object files
OBJ = build/main.o build/job.o build/tools.o
# Build folder for .o files
BUILD = build
# Compile target
TARGET = Threads

# Link object files and produce executable
$(TARGET): $(BUILD) $(OBJ)
	c++ $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Delete executable
clean:
	rm -r $(BUILD)
	rm $(TARGET)

# Make build directory
build:
	mkdir -p $(BUILD)

# Dependencies
$(BUILD)/main.o: main.cpp sharedData.hpp
	c++ $(CXXFLAGS) -c main.cpp -o $(BUILD)/main.o

$(BUILD)/job.o: job.cpp job.hpp
	c++ $(CXXFLAGS) -c job.cpp -o $(BUILD)/job.o

$(BUILD)/tools.o: tools.cpp tools.hpp
	c++ $(CXXFLAGS) -c tools.cpp -o $(BUILD)/tools.o
