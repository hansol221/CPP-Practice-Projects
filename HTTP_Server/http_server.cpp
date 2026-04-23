#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    //Create a server socket
    int http_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (http_serverSocket == -1) {
        cout << "The system failed to create a socket" << endl;
        return -1;
    }
    cout << "Socket created!" << endl;

    //Give server socket an IP address and a port #
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(80);

    if (::bind(http_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cout << "Bind failed!" << endl;
        return -1;
    }
    cout << "Bind successfully!" << endl;

    //Listen for incoming connection on port 80
    if (listen(http_serverSocket, 5) == -1) {
        cout << "Listen failed!" << endl;
        return -1;
    }
    cout << "Listen successfully! Server is on port 80." << endl;
    
    //Wait for client to make a connection
    cout << "Waiting for the connection..." << endl;

    //Accept the client connection and create a new commuication socket
    int http_clientServer = accept(http_serverSocket, nullptr, nullptr);

    if (http_clientServer == -1) {
        cout << "Client connection failed!" << endl;
    }
    cout << "Client connected successfully!" << endl;

    //Receive HTTP request from the client
    char buffer[1024] = {0};
    recv(http_clientServer, buffer, sizeof(buffer), 0);
    cout << "Request received!" << endl;
    cout << buffer << endl;

    //Respond from the request to the server
    string response = "HTTP/1.1 200 OK\r\n" 
                    "Content-Type: text/html\r\n\r\n"
                    "<html>"
                    "<body>TESTING MESSAGE</body>"
                    "<h1>Hello from my HTTP Server!</h1>"
                    "<h2>I don't know </h2>"
                    "<p>Well hello </p>"
                    "<b>This is Hansol</b>"
                    "</html>";
    send(http_clientServer, response.c_str(), response.size(), 0);
    cout << "Response Sent!" << endl;
}