#include "server.h"
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

struct Client {
    int socket;
    std::string username;
};

// Global variables for handling clients and threads
std::vector<Client> clients;
std::mutex client_mutex;

void broadcastRecipientList() {
    std::string recipientList = "UPDATE_RECIPIENTS";
    for (const auto& client : clients) {
        recipientList += "," + client.username;
    }
    int length = recipientList.length();
    for (const auto& client : clients) {
        send(client.socket, &length, sizeof(length), 0);
        send(client.socket, recipientList.c_str(), length, 0);
    }
}

void handle_client(int client_socket) {
    char buffer[1024];
    std::string username;

    // Handle login credentials
    int length;
    recv(client_socket, &length, sizeof(length), 0);
    recv(client_socket, buffer, length, 0);
    buffer[length] = '\0';
    if (strncmp(buffer, "USER:", 5) == 0) {
        username = buffer + 5;
    }
    recv(client_socket, &length, sizeof(length), 0);
    recv(client_socket, buffer, length, 0);
    buffer[length] = '\0';
    if (strncmp(buffer, "PASS:", 5) == 0) {
        std::string password = buffer + 5;
        // Handle password verification if needed
    }

    {
        std::lock_guard<std::mutex> lock(client_mutex);
        clients.push_back({client_socket, username});
        std::cout << "Added client: " << username << " with socket: " << client_socket << std::endl;
        broadcastRecipientList();
    }

    while (true) {
        int received = recv(client_socket, &length, sizeof(length), 0);
        if (received <= 0) {
            std::cout << "Client disconnected or error: " << client_socket << std::endl;
            break; // Connection closed or error
        }

        received = recv(client_socket, buffer, length, 0);
        if (received <= 0) {
            std::cout << "Client disconnected or error: " << client_socket << std::endl;
            break; // Connection closed or error
        }
        buffer[length] = '\0';
        std::string message = buffer;

        // Check for private message
        if (message[0] == '@') {
            size_t pos = message.find(": ");
            if (pos != std::string::npos) {
                std::string recipient = message.substr(1, pos - 1);
                std::string private_message = message.substr(pos + 2);

                std::lock_guard<std::mutex> lock(client_mutex);
                auto it = std::find_if(clients.begin(), clients.end(), [&recipient](const Client& client) {
                    return client.username == recipient;
                });
                if (it != clients.end()) {
                    int msg_length = private_message.length();
                    send(it->socket, &msg_length, sizeof(msg_length), 0);
                    send(it->socket, private_message.c_str(), msg_length, 0);
                    std::cout << "Sent private message to client: " << it->username << std::endl;
                } else {
                    std::cerr << "Recipient not found: " << recipient << std::endl;
                }
            }
        } else {
            std::string broadcast_message = username + ": " + message;

            std::lock_guard<std::mutex> lock(client_mutex);
            for (const auto& client : clients) {
                if (client.socket != client_socket) {
                    int msg_length = broadcast_message.length();
                    send(client.socket, &msg_length, sizeof(msg_length), 0);
                    send(client.socket, broadcast_message.c_str(), msg_length, 0);
                    std::cout << "Sent message to client: " << client.socket << std::endl;
                }
            }
        }
    }

    // Cleanup on disconnection
    close(client_socket);
    std::lock_guard<std::mutex> lock(client_mutex);
    clients.erase(std::remove_if(clients.begin(), clients.end(), [client_socket](const Client& client) {
        return client.socket == client_socket;
    }), clients.end());
    std::cout << "Removed client: " << client_socket << std::endl;
    broadcastRecipientList();
}

void run_server() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
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
        std::thread(handle_client, client_socket).detach();
    }
}
