#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <thread>
#include <QString>

class ChatClient : public QWidget {
    Q_OBJECT

public:
    ChatClient(const char* server_ip, int port, const QString& username, const QString& password, QWidget* parent = nullptr);
    ~ChatClient();

    private slots:
        void sendMessage();
    void updateStatus(const QString& message);
    void handleReturnPressed();
    void selectFile();  // Add declaration for selectFile

private:
    const char* server_ip;
    int port;
    int sock;
    QString username;
    std::thread recvThread;
    QTextEdit* chatBox;
    QLineEdit* input;
    QPushButton* sendButton;
    QPushButton* fileButton;  // Declare fileButton
    QStatusBar* statusBar;

    void setupUI();
    void connectSignals();
    void receiveMessages();
    void sendLoginDetails(const QString& username, const QString& password);  // Declare sendLoginDetails
    int connectToServer();
};

#endif // CHATCLIENT_H
