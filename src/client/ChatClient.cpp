#include "ChatClient.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QScrollBar>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QComboBox>
#include <QInputDialog>
#include <QCryptographicHash>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <QDebug>
#include <QMessageBox>

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
        QMessageBox::critical(this, "Connection Error", "Failed to connect to server.");
    }
    loadChatHistory();
}

ChatClient::~ChatClient() {
    if (sock != -1) {
        ::close(sock);
    }
    if (recvThread.joinable()) {
        recvThread.join();
    }
    saveChatHistory();
}

/**
 * @brief Sets up the user interface of the chat client.
 */
void ChatClient::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    chatBox = new QTextEdit;
    chatBox->setReadOnly(true);
    chatBox->setStyleSheet("background-color: #ffffff; color: #000000; padding: 10px; border: 1px solid #cccccc; border-radius: 10px;");
    mainLayout->addWidget(chatBox);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    input = new QLineEdit;
    input->setStyleSheet("background-color: #ffffff; color: #000000; padding: 10px; border: 1px solid #cccccc; border-radius: 10px;");
    recipientComboBox = new QComboBox;
    recipientComboBox->setStyleSheet("background-color: #ffffff; color: #000000; padding: 10px; border: 1px solid #cccccc; border-radius: 10px;");
    recipientComboBox->setEditable(true);
    sendButton = new QPushButton("Send");
    sendButton->setStyleSheet("background-color: #0084ff; color: white; padding: 10px; border-radius: 10px;");
    privateButton = new QPushButton("Send Private");
    privateButton->setStyleSheet("background-color: #ff6600; color: white; padding: 10px; border-radius: 10px;");
    inputLayout->addWidget(input);
    inputLayout->addWidget(recipientComboBox);
    inputLayout->addWidget(sendButton);
    inputLayout->addWidget(privateButton);
    mainLayout->addLayout(inputLayout);

    statusBar = new QStatusBar;
    statusBar->setStyleSheet("color: #000000;");
    mainLayout->addWidget(statusBar);

    setLayout(mainLayout);
    setWindowTitle("Chat Client");
    setStyleSheet("background-color: #f0f0f0; font-family: Arial, sans-serif; font-size: 14px;");
}

/**
 * @brief Connects signals and slots for the UI components.
 */
void ChatClient::connectSignals() {
    connect(sendButton, &QPushButton::clicked, this, &ChatClient::sendMessage);
    connect(privateButton, &QPushButton::clicked, this, &ChatClient::sendPrivateMessage);
    connect(input, &QLineEdit::returnPressed, this, &ChatClient::handleReturnPressed);
}

void ChatClient::sendMessage() {
    if (sock == -1) {
        updateStatus("Not connected to the server.");
        QMessageBox::warning(this, "Connection Error", "Not connected to the server.");
        return;
    }

    std::string message = input->text().toStdString();
    if (message.empty()) {
        return; // Silently ignore empty messages
    }

    int length = message.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, message.c_str(), length, 0);
    chatBox->append("<b style='color: green;'>You:</b> " + QString::fromStdString(message));
    chatHistory.push_back("<b style='color: green;'>You:</b> " + QString::fromStdString(message));
    input->clear();
}

void ChatClient::sendPrivateMessage() {
    if (sock == -1) {
        updateStatus("Not connected to the server.");
        QMessageBox::warning(this, "Connection Error", "Not connected to the server.");
        return;
    }

    std::string recipient = recipientComboBox->currentText().toStdString();
    std::string message = input->text().toStdString();
    if (message.empty()) {
        return; // Silently ignore empty messages
    }

    std::string privateMessage = "@" + recipient + ": " + username.toStdString() + ": " + message;
    int length = privateMessage.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, privateMessage.c_str(), length, 0);
    chatBox->append("<b style='color: green;'>Private to " + QString::fromStdString(recipient) + ":</b> " + QString::fromStdString(message));
    chatHistory.push_back("<b style='color: green;'>Private to " + QString::fromStdString(recipient) + ":</b> " + QString::fromStdString(message));
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
        if (message[0] == '@') {
            // Private message format
            size_t pos = message.find(": ");
            if (pos != std::string::npos) {
                size_t second_pos = message.find(": ", pos + 2);
                if (second_pos != std::string::npos) {
                    std::string recipient = message.substr(1, pos - 1);
                    std::string sender = message.substr(pos + 2, second_pos - pos - 2);
                    std::string private_text = message.substr(second_pos + 2);

                    QString formattedMessage = QString("<b style='color: orange;'>Private from %1:</b> <span style='color: black;'>%2</span>")
                                                .arg(QString::fromStdString(sender))
                                                .arg(QString::fromStdString(private_text));
                    chatBox->append(formattedMessage);
                    chatHistory.push_back(formattedMessage);
                }
            }
        } else if (message.find("UPDATE_RECIPIENTS") == 0) {
            // Handle recipient list update
            QStringList recipients = QString::fromStdString(message.substr(17)).split(",");
            availableRecipients.clear();
            for (const QString& recipient : recipients) {
                if (recipient != username) {
                    availableRecipients.push_back(recipient);
                }
            }
            updateRecipientList(availableRecipients);
        } else {
            // Normal message format
            size_t pos = message.find(": ");
            if (pos != std::string::npos) {
                std::string sender = message.substr(0, pos);
                std::string text = message.substr(pos + 2);

                QString formattedMessage = QString("<b style='color: cyan;'>%1:</b> <span style='color: black;'>%2</span>")
                                            .arg(QString::fromStdString(sender))
                                            .arg(QString::fromStdString(text));
                chatBox->append(formattedMessage);
                chatHistory.push_back(formattedMessage);
            }
        }
    }
}

void ChatClient::sendLoginDetails(const QString& username, const QString& password) {
    // Hash the password before sending
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    std::string user_msg = "USER:" + username.toStdString();
    int length = user_msg.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, user_msg.c_str(), length, 0);

    std::string pass_msg = "PASS:" + hashedPassword.toHex().toStdString();
    length = pass_msg.length();
    send(sock, &length, sizeof(length), 0);
    send(sock, pass_msg.c_str(), length, 0);
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
    // Log the status message to the console for debugging
    qDebug() << message;
}

void ChatClient::loadChatHistory() {
    QString path = QDir::currentPath() + "/client_data/chat_history.txt";
    QDir().mkpath(QDir::currentPath() + "/client_data");  // Ensure the directory exists
    std::cout << "Loading chat history from: " << path.toStdString() << std::endl;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            chatBox->append(line);
            chatHistory.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Failed to open chat history file for reading." << std::endl;
    }
}

void ChatClient::saveChatHistory() {
    QString path = QDir::currentPath() + "/client_data/chat_history.txt";
    QDir().mkpath(QDir::currentPath() + "/client_data");  // Ensure the directory exists
    std::cout << "Saving chat history to: " << path.toStdString() << std::endl;
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const QString& line : chatHistory) {
            out << line << "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to open chat history file for writing." << std::endl;
    }
}

void ChatClient::updateRecipientList(const std::vector<QString>& recipients) {
    recipientComboBox->clear();
    for (const QString& recipient : recipients) {
        recipientComboBox->addItem(recipient);
    }
}
