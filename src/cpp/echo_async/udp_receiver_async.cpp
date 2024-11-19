#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

#define PORT 5005
#define BUFFER_SIZE 1024

// Global variables for message cache and lock
std::vector<std::string> message_cache;
std::mutex cache_mutex;



void udp_receiver() {
    /** Function to receive UDP messages and cache them
     * 
     * This function listens for UDP messages on the specified port and IP address.
     * It receives messages and adds them to the message cache.
     * 
     * The function runs in an infinite loop until an error occurs.
     * 
     * The function does not return any value.
     */


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
        return;
    }

    // Bind the socket
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces. Not specific to any IP.
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return;
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

        // Safely add the message to the cache
        std::lock_guard<std::mutex> lock(cache_mutex);
        message_cache.push_back(buffer);
    }

    close(sockfd);
}


int main() {
 // Start the receiver thread
    std::thread receiver_thread(udp_receiver);

    // Periodically print cached messages
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second

        // Safely access and print the message cache
        {
            std::lock_guard<std::mutex> lock(cache_mutex);
            if (message_cache.empty()) {
                std::cout << "No messages received yet.\n";
            } else {
                std::cout << "Received messages:\n";
                for (const auto& msg : message_cache) {
                    std::cout << "- " << msg << "\n";
                }
                message_cache.clear(); // Clear the cache after printing
            }
        }
    }
    return 0;
}
