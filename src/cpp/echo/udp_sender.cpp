#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5005

int main() {
    // Set Up Socket that can be used to send UDP Packets.
    int sockfd;
    struct sockaddr_in serverAddr;
    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);
    
    std::cout << "Created socket at " << sockfd << std::endl;
    std::cout << "Sending Packages to " << inet_ntoa(serverAddr.sin_addr) << ":" << ntohs(serverAddr.sin_port) << "\n";

    // Send messages in a loop
    while (true) {
        std::string message;
        std::cout << "Enter message to send (or q to exit): ";
        std::getline(std::cin, message); // Read input from user

        // Exit if user enters 'q'
        if (message == "q") {
            break;
        }

        // Send message to client
        if (sendto(sockfd, message.c_str(), message.size(), 0, 
                   (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Send failed");
            break;
        }
    }

    close(sockfd);
    return 0;
}
