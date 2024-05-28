#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QStatusBar>
#include <thread>
#include <QString>
#include <vector>

class ChatClient : public QWidget {
    Q_OBJECT

public:
    ChatClient(const char* server_ip, int port, const QString& username, const QString& password, QWidget* parent = nullptr);
    ~ChatClient();

    private slots:
        void sendMessage();
    void sendPrivateMessage();
    void updateStatus(const QString& message);
    void handleReturnPressed();

private:
    const char* server_ip;
    int port;
    int sock;
    QString username;
    std::thread recvThread;
    QTextEdit* chatBox;
    QLineEdit* input;
    QComboBox* recipientComboBox;
    QPushButton* sendButton;
    QPushButton* privateButton;
    QStatusBar* statusBar;
    std::vector<QString> chatHistory;
    std::vector<QString> availableRecipients;

    void setupUI();
    void connectSignals();
    void receiveMessages();
    void sendLoginDetails(const QString& username, const QString& password);
    int connectToServer();
    void loadChatHistory();
    void saveChatHistory();
    void updateRecipientList(const std::vector<QString>& recipients);
};

#endif // CHATCLIENT_H
