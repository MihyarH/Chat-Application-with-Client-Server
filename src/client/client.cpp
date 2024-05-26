#include "ChatClient.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        qCritical("Usage: %s <server_ip> <port>", argv[0]);
        return 1;
    }

    const char* server_ip = argv[1];
    int port = atoi(argv[2]);

    QApplication app(argc, argv);
    ChatClient client(server_ip, port);
    client.show();
    return app.exec();
}
