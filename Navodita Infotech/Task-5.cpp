#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

vector<int> clients;

void handleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            close(clientSocket);
            break;
        }

        for (int client : clients) {
            if (client != clientSocket) {
                send(client, buffer, bytesReceived, 0);
            }
        }
    }
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error binding" << endl;
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        cerr << "Error listening" << endl;
        return 1;
    }

    cout << "Server is listening on port 12345" << endl;

    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        clients.push_back(clientSocket);

        thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    return 0;
}
