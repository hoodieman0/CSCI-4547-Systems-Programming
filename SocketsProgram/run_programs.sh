#!/bin/bash

make

# Open a new terminal window and run ./serverMom
xterm -e "./serverMom" &

# Wait for a few seconds to allow the server to start up
sleep 3

# Open another terminal window and run ./clientPat
xterm -e "./clientPat localhost" &
