#!/bin/sh

# Run the SCRIPT on a PORT (tcp) with a
# little help from a named pipe and netcat

SCRIPT=./server.sh
PORT=6666
PIPE=pipa

# First create the pipe (if it doesn't exist)
if ! test -p $PIPE; then
  rm -f $PIPE
  mkfifo $PIPE || exit 1
fi
  
# Start the script and redirect stdin/stdout
# to netcat through the named pipe
$SCRIPT < $PIPE | nc -l localhost $PORT 2>&1 > $PIPE

# Now you can interact with the script by
# connecting to the port. Example:
# nc localhost 6666
# When the client disconnects from
# the port the server will also finish.
# You could restart it through something
# like xinetd if you like. That would also
# allow multiple clients to connect simultaneously.

echo "Server finished"
