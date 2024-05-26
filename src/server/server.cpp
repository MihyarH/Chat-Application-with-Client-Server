#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <algorithm>

const int PORT = 8888;

// Global variables for handling clients and threads
std::vector<int> client_sockets;
std::vector<std::thread> client_threads;
std::mutex client_mutex;

// Function to handle each client connection
void handle_client(int client_socket) {
    char buffer[1024];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int read_size = recv(client_socket, buffer, sizeof(buffer), 0);
        if (read_size <= 0) {
            break; // Connection closed or error
        }

        // Lock the mutex to safely update shared resources
        std::lock_guard<std::mutex> lock(client_mutex);
        for (int sock : client_sockets) {
            if (sock != client_socket) {
                send(sock, buffer, read_size, 0); // Broadcast message to other clients
            }
        }
    }

    // Cleanup on disconnection
    close(client_socket);
    std::lock_guard<std::mutex> lock(client_mutex);
    client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end());
    std::cout << "Client disconnected: " << client_socket << std::endl;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Setting up the server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {  // Listening for up to 10 clients
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        std::cout << "New connection: " << client_socket << std::endl;

        {
            // Locking while modifying the shared resources
            std::lock_guard<std::mutex> lock(client_mutex);
            client_sockets.push_back(client_socket);
            client_threads.emplace_back(handle_client, client_socket);
            client_threads.back().detach();  // Detach the thread to handle independently
        }
    }

    return 0;
}
