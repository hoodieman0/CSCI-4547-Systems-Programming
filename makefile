# Compile flags
CXXFLAGS = -g -Wall

# C++ file objects
OBJ = main.o FileID.o params.o sniff.o tools.o

# Main entry
all: sniff

# Compile all the object files
sniff: $(OBJ)
	g++ -o sniff $(CXXFLAGS) $(OBJ)

# Create the main.o object file
main.o: main.cpp tools.hpp main.cpp
	g++ -c $(CXXFLAGS) main.cpp

sniff.o: sniff.cpp sniff.hpp
	g++ -c $(CXXFLAGS) sniff.cpp

FileID.o: FileID.cpp FileID.hpp
	g++ -c $(CXXFLAGS) FileID.cpp

params.o: params.cpp params.hpp
	g++ -c $(CXXFLAGS) params.cpp

# Create the tools.o object file
tools.cpp: tools.hpp tools.cpp 
	g++ -c $(CXXFLAGS) tools.cpp

# Remove all the newly created files
clean:
	rm -f $(OBJ) sniff