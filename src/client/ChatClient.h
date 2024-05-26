#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <thread>

class ChatClient : public QWidget {
    Q_OBJECT

public:
    ChatClient(const char* server_ip, int port, QWidget* parent = nullptr);
    ~ChatClient();

    private slots:
        void sendMessage();
    void updateStatus(const QString& message);
    void handleReturnPressed();

private:
    const char* server_ip;
    int port;
    int sock;
    std::thread recvThread;
    QTextEdit* chatBox;
    QLineEdit* input;
    QPushButton* sendButton;
    QStatusBar* statusBar;

    void setupUI();
    void connectSignals();
    void receiveMessages();
    int connectToServer();
};

#endif // CHATCLIENT_H
