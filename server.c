#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 5

int createSocket(void) {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    return sockfd;
}
/**
 * sockaddr is a generic descriptor for any kind of socket operation, whereas 
 * sockaddr_in is a struct specific to IP-based communication (IIRC, "in" stands for "InterNet"). As far as I know, this is a kind of 
 * "polymorphism" : the bind() function pretends to take a struct sockaddr *, but in fact, it will assume that the appropriate type
 *  of structure is passed in; i. e. one that corresponds to the type of socket you give it as the first argument.
 */
int bindSocket(int sockfd) {
    int retVal = -1;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    retVal = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    return retVal;
}

int main(void) {
    int serverSockfd, clientSockfd;
    int clientLen;
    struct sockaddr_in clientAddr;
    printf("Creating Socket\n");
    serverSockfd = createSocket();
    if (serverSockfd == 0) {
        perror("socket failed");
        exit(1);
    }
    printf("Socket created: #%d\n", serverSockfd);

    printf("Binding socket\n");
    if (bindSocket(serverSockfd) < 0) {
        perror("bind failed");
        exit(1);
    }
    printf("Socket binded\n");

    printf("Listen on socket\n");
    if (listen(serverSockfd, BACKLOG) < 0) {
        perror("listen failed\n");
        exit(1);
    }
    printf("Listen added\n");

    printf("Accepting new connections\n");
    clientLen = sizeof(struct sockaddr_in);
    clientSockfd = accept(serverSockfd, (struct sockaddr *) &clientAddr, (socklen_t *) &clientLen);
    printf("Client accepted: #%d\n", clientSockfd);
    return 0;
}