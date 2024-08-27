# Minitalk

Minitalk is a small data exchange program using UNIX signals.

![minitalk demo](https://github.com/user-attachments/assets/be77ed7c-e145-4a56-b90b-52b11d2a3c56)

## Description

This project involves creating a communication program in the form of a client and server. The server must be launched first and print its PID. The client takes two parameters:

1. The server PID
2. The string to send

The client must send the string passed as a parameter to the server. Once the string has been received, the server must print it.

## Features

- Server prints its PID on launch
- Client sends messages to server using UNIX signals
- Server displays received messages
- Communication must be done using only SIGUSR1 and SIGUSR2 signals

## Bonus Features

- The server acknowledges every message received by sending back a signal to the client
- Unicode characters support

## Compilation

To compile the project, use the provided Makefile:


##How to use
1. compile
```
make
```

2. Start the server
```
./server
```
The server will print its PID.

3. execute slient
```
./client [server PID] [message]
```

Replace `[server_pid]` with the PID printed by the server, and `[message]` with the string you want to send.
