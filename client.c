#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
// #include <netinet/ip.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080

int createSocket(void) {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    return sockfd;
}

int clientConnect(int sockfd) {
    int retVal = -1;
    struct sockaddr_in addr;

    // have to set the ip, the internet family, and port
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr.sin_port = htons(PORT);
    retVal = connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    return retVal;
}

int main(void) {
    int clientSocketfd;

    clientSocketfd = createSocket();
    printf("Client socket created: #%d\n", clientSocketfd);
    
    printf("Attempting to connect to server: %s\n", SERVER_IP);
    if (clientConnect(clientSocketfd) < 0) {
        perror("error on connect");
        exit(1);
    }
    printf("Connected!\n");
    
    return 0;
}