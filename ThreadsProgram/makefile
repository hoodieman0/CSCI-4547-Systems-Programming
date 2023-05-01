# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Object files
OBJ = build/main.o build/job.o build/mom.o build/kid.o build/jobTable.o build/tools.o
# Build folder for .o files
BUILD = build
# Compile target
TARGET = Threads

# Link object files and produce executable
$(TARGET): $(BUILD) $(OBJ)
	c++ $(CXXFLAGS) $(OBJ) -o $(TARGET)

# Delete executable and build folder
clean:
	rm -r $(BUILD) $(TARGET) $(OBJ)

# Make build directory
build:
	mkdir -p $(BUILD)

# Dependencies
$(BUILD)/main.o: main.cpp mom.hpp kid.hpp job.hpp jobTable.hpp tools.hpp
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
