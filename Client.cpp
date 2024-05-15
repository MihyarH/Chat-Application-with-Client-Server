#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

// Function to connect to the server
int connect_to_server(const char* server_ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return -1;
    }

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        return -1;
    }

    std::cout << "Connected to the server." << std::endl;
    return sock;
}

// Function to send messages to the server
void send_message(int sock) {
    std::string message;
    while (true) {
        std::cout << "Enter message (type 'exit' to quit): ";
        std::getline(std::cin, message); // Get line of text from standard input

        if (message == "exit") { // Check if the user wants to exit
            break;
        }

        // Send the message to the server
        ssize_t bytes_sent = send(sock, message.c_str(), message.length(), 0);
        if (bytes_sent == -1) {
            std::cerr << "Failed to send message" << std::endl;
            break;
        }
    }
}

// Function to receive messages from the server
void receive_messages(int sock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(sock, buffer, sizeof(buffer), 0);
        if (len <= 0) {
            std::cout << "Disconnected from server or error occurred." << std::endl;
            break;
        }
        std::cout << "Server: " << buffer << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port>" << std::endl;
        return 1;
    }

    const char* server_ip = argv[1];
    int port = atoi(argv[2]);

    int sock = connect_to_server(server_ip, port);
    if (sock == -1) {
        return 1;
    }

    send_message(sock); // Function to send messages to the server

    close(sock); // Close the socket when done
    return 0;
}