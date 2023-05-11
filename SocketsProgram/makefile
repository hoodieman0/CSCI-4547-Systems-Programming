# Compiler flags
CXXFLAGS = -Wall -std=c++17
# Build folder for .o files
BUILD = ObjectFiles
SERVERBUILD = ObjectFiles/Server
CLIENTBUILD = ObjectFiles/Client
# Server Object files
SERVER = $(SERVERBUILD)/main.o $(SERVERBUILD)/job.o $(SERVERBUILD)/mom.o $(SERVERBUILD)/tools.o $(SERVERBUILD)/Socket.o
# Client Object fies
CLIENT = $(CLIENTBUILD)/client.o $(CLIENTBUILD)/kid.o $(CLIENTBUILD)/Socket.o $(CLIENTBUILD)/tools.o $(CLIENTBUILD)/job.o
# Compile target
SERVERTARGET = serverMom
PATTARGET = clientPat
MARYTARGET = clientMary
JOHNTARGET = clientJohn

all: $(SERVERTARGET) clients

# Link object files and produce executable
$(SERVERTARGET): $(BUILD) $(SERVER)
	c++ $(CXXFLAGS) $(SERVER) -o $(SERVERTARGET)

clients: $(BUILD) $(CLIENT)
	c++ $(CXXFLAGS) $(CLIENT) -o $(PATTARGET)
	c++ $(CXXFLAGS) $(CLIENT) -o $(MARYTARGET)
	c++ $(CXXFLAGS) $(CLIENT) -o $(JOHNTARGET)

# Delete executable and build folder
clean:
	rm -r $(SERVERTARGET) $(PATTARGET) $(MARYTARGET) $(JOHNTARGET) $(SERVER) $(CLIENT) $(BUILD) 

# Make build directory
$(BUILD):
#	 mkdir -p $(BUILD)
	mkdir -p $(SERVERBUILD) && mkdir -p $(CLIENTBUILD)

# Dependencies
$(SERVERBUILD)/main.o: main.cpp mom.hpp job.hpp jobTable.hpp tools.hpp Socket.hpp
	c++ $(CXXFLAGS) -c main.cpp -o $(SERVERBUILD)/main.o

$(SERVERBUILD)/job.o: job.cpp job.hpp
	c++ $(CXXFLAGS) -c job.cpp -o $(SERVERBUILD)/job.o

$(SERVERBUILD)/mom.o: mom.cpp mom.hpp
	c++ $(CXXFLAGS) -c mom.cpp -o $(SERVERBUILD)/mom.o

$(SERVERBUILD)/tools.o: tools.cpp tools.hpp
	c++ $(CXXFLAGS) -c tools.cpp -o $(SERVERBUILD)/tools.o

$(SERVERBUILD)/Socket.o: Socket.cpp Socket.hpp
	c++ $(CXXFLAGS) -c Socket.cpp -o $(SERVERBUILD)/Socket.o


$(CLIENTBUILD)/client.o: client.cpp kid.hpp Socket.hpp
	c++ $(CXXFLAGS) -c client.cpp -o $(CLIENTBUILD)/client.o

$(CLIENTBUILD)/kid.o: kid.cpp kid.hpp Socket.hpp
	c++ $(CXXFLAGS) -c kid.cpp -o $(CLIENTBUILD)/kid.o

$(CLIENTBUILD)/tools.o: tools.cpp tools.hpp
	c++ $(CXXFLAGS) -c tools.cpp -o $(CLIENTBUILD)/tools.o

$(CLIENTBUILD)/Socket.o: Socket.cpp Socket.hpp
	c++ $(CXXFLAGS) -c Socket.cpp -o $(CLIENTBUILD)/Socket.o

$(CLIENTBUILD)/job.o: job.cpp job.hpp
	c++ $(CXXFLAGS) -c job.cpp -o $(CLIENTBUILD)/job.o
