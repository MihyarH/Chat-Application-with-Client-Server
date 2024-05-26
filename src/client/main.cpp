#include "ChatClient.h"
#include <QApplication>
#include <QInputDialog>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        qCritical("Usage: %s <server_ip> <port>", argv[0]);
        return 1;
    }

    const char* server_ip = argv[1];
    int port = atoi(argv[2]);

    QApplication app(argc, argv);

    // Prompt for username and password
    bool ok;
    QString username = QInputDialog::getText(nullptr, "Login", "Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) {
        return 1;
    }
    QString password = QInputDialog::getText(nullptr, "Login", "Password:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) {
        return 1;
    }

    ChatClient client(server_ip, port, username, password);
    client.show();
    return app.exec();
}
