#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5005
#define BUFFER_SIZE 1024

int main() {

    // Create buffer to store received data
    char buffer[BUFFER_SIZE];
    
    // Set up socket that can be used to receive UDP packets
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Bind the socket
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces. Not specific to any IP.
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    std::cout << "Listening for messages on port " << PORT << "...\n";

    // Receive messages in a loop
    while (true) {
        ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, 
                               (struct sockaddr*)&clientAddr, &addrLen);
        if (len < 0) {
            perror("Receive failed");
            break;
        }
        buffer[len] = '\0';  // Null-terminate the received data, so std::cout knows where to stop.
        std::cout << "Received: " << buffer << "\n";
    }

    close(sockfd);
    return 0;
}
