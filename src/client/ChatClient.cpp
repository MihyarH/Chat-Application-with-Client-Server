#include "ChatClient.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QScrollBar>
#include <QFileDialog>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

ChatClient::ChatClient(const char* server_ip, int port, const QString& username, const QString& password, QWidget* parent)
    : QWidget(parent), server_ip(server_ip), port(port), sock(-1), username(username) {
    setupUI();
    connectSignals();
    sock = connectToServer();
    if (sock != -1) {
        sendLoginDetails(username, password);
        recvThread = std::thread(&ChatClient::receiveMessages, this);
        updateStatus("Connected to server.");
    } else {
        updateStatus("Failed to connect to server.");
    }
}

ChatClient::~ChatClient() {
    if (sock != -1) {
        ::close(sock);
    }
    if (recvThread.joinable()) {
        recvThread.join();
    }
}

void ChatClient::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    chatBox = new QTextEdit;
    chatBox->setReadOnly(true);
    chatBox->setStyleSheet("background-color: #ffffff; color: #000000; padding: 10px; border: 1px solid #cccccc; border-radius: 10px;");
    mainLayout->addWidget(chatBox);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    input = new QLineEdit;
    input->setStyleSheet("background-color: #ffffff; color: #000000; padding: 10px; border: 1px solid #cccccc; border-radius: 10px;");
    sendButton = new QPushButton("Send");
    sendButton->setStyleSheet("background-color: #0084ff; color: white; padding: 10px; border-radius: 10px;");
    fileButton = new QPushButton("Send File");
    fileButton->setStyleSheet("background-color: #0084ff; color: white; padding: 10px; border-radius: 10px;");
    inputLayout->addWidget(input);
    inputLayout->addWidget(sendButton);
    inputLayout->addWidget(fileButton);
    mainLayout->addLayout(inputLayout);

    statusBar = new QStatusBar;
    statusBar->setStyleSheet("color: #000000;");
    mainLayout->addWidget(statusBar);

    setLayout(mainLayout);
    setWindowTitle("Chat Client");
    setStyleSheet("background-color: #f0f0f0; font-family: Arial, sans-serif; font-size: 14px;");
}

void ChatClient::connectSignals() {
    connect(sendButton, &QPushButton::clicked, this, &ChatClient::sendMessage);
    connect(fileButton, &QPushButton::clicked, this, &ChatClient::selectFile);
    connect(input, &QLineEdit::returnPressed, this, &ChatClient::handleReturnPressed);
}

void ChatClient::sendMessage() {
    if (sock == -1) {
        updateStatus("Not connected to the server.");
        return;
    }

    std::string message = input->text().toStdString();
    int length = message.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, message.c_str(), length, 0);
    chatBox->append("<b style='color: green;'>You:</b> " + QString::fromStdString(message));
    input->clear();
}

void ChatClient::handleReturnPressed() {
    sendMessage();
}

void ChatClient::receiveMessages() {
    char buffer[1024];
    while (true) {
        int length;
        int received = recv(sock, &length, sizeof(length), 0);
        if (received <= 0) {
            updateStatus("Disconnected from server.");
            break;
        }

        received = recv(sock, buffer, length, 0);
        if (received <= 0) {
            updateStatus("Disconnected from server.");
            break;
        }
        buffer[length] = '\0';

        std::string message(buffer);
        std::size_t pos = message.find(": ");
        if (pos != std::string::npos) {
            std::string username = message.substr(0, pos);
            std::string text = message.substr(pos + 2);

            chatBox->append(QString("<b style='color: cyan;'>%1:</b> <span style='color: black;'>%2</span>")
                .arg(QString::fromStdString(username))
                .arg(QString::fromStdString(text)));
        } else {
            chatBox->append(QString("<span style='color: black;'>%1</span>")
                .arg(QString::fromStdString(message)));
        }
    }
}

void ChatClient::sendLoginDetails(const QString& username, const QString& password) {
    std::string user_msg = "USER:" + username.toStdString();
    int length = user_msg.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, user_msg.c_str(), length, 0);

    std::string pass_msg = "PASS:" + password.toStdString();
    length = pass_msg.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, pass_msg.c_str(), length, 0);
}

void ChatClient::selectFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File to Send");
    if (!filePath.isEmpty()) {
        // Implement the file sending logic here
    }
}

int ChatClient::connectToServer() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return -1;
    }

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (::connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        ::close(sock);
        return -1;
    }
    return sock;
}

void ChatClient::updateStatus(const QString& message) {
    statusBar->showMessage(message);
}
