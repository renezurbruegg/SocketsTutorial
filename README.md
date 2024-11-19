# Socket Tutorial

This repository contains a collection of tutorials for UDP and TCP sockets in Python. The tutorials are designed to be easy to follow and include code snippets to help you get started.


## Tutorials
This repository contains the following tutorials:
- echo
  - This tutorial demonstrates how to create a simple echo server using UDP sockets in Python and C++. It consists of a sender and a receiver. The sender sends a message to the receiver, which then prints the message to the console.
- echo_async
  - This tutorial demonstrates how to create an asynchronous echo server using UDP sockets in Python and C++. As oopposed to the echo tutorial, the receiver keeps listening to messages in the background (different thread) and prints all received messages to the console every second.
## Installation
### Clone the repository
To clone the repository, run the following command in the terminal:

```bash
git clone git@github.com:renezurbruegg/SocketsTutorial.git
cd SocketsTutorial
```

### CPP
The c++ code needs to be compiled before running. To compile the code, run the following command in the terminal (Assuming you have g++ installed and are in the root directory of the project):

```bash
mkdir build # Create a build directory
# Build the executables. 
# Build the udp_sender
g++ src/cpp/echo/udp_sender.cpp -o build/udp_sender
# Build the udp_receiver
g++ src/cpp/echo/udp_receiver.cpp -o build/udp_receiver
# Build the async udp_receiver
g++ src/cpp/echo_async/udp_receiver_async.cpp -o build/udp_receiver_async -lpthread
```

## Usage
### Python
To run the python code, run the following command in the terminal:

```bash
# Terminal 1
python src/python/echo/udp_sender.py

# Terminal 2 (If using the echo tutorial)
python src/python/echo/udp_receiver.py
# Terminal 2 (If using the echo_async tutorial)
python src/python/echo_async/udp_receiver_async.py
```

### CPP
To run the c++ code, run the following command in the terminal:

```bash
# Terminal 1
./build/udp_receiver

# Terminal 2 (If using the echo tutorial)
./build/udp_sender
# Terminal 2 (If using the echo_async tutorial)
./build/udp_sender
```


## Connecting with different PCs
If you want to connect the sender and receiver on different PCs, you need to change the IP address in the code.

Make sure that the sender and receiver are on the same network (I.e. connected over ethernet or wifi (e.g using a hotspot)).

To find the IP address of the receiver, you can run the following command in the terminal:
```bash
ifconfig
```
Or you can open the network settings on the receiver PC and find the IP address there.


## Cross-Language Communication
Note that you can also run the python sender and the c++ receiver or vice versa. The code is designed to be cross-language compatible.

