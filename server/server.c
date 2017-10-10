#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 200
#define SERV_PORT 34567

typedef struct User {
    char name[20];
    char ip[20];
    int port;
}User;

typedef struct {
    struct list* next;
    User user;
}list;

list* getNode() {
    return (list*)malloc(sizeof(list));
}

list* head;

int main() {
    int sockfd;
    struct sockaddr_in servaddr, clientaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) == -1) {
        printf("bind error\n");
        exit(-1);
    }

    socklen_t sin_len;
    char message[MAX_LEN];
    
    while(1) {
        recvfrom(sockfd, message, MAX_LEN, 0, (struct sockaddr*)&clientaddr, &sin_len);
        printf("receive data\n");
        char* ip = inet_ntoa(clientaddr.sin_addr);
        printf("client ip is %s\n, prot is %d\n", ip, clientaddr.sin_port);
        printf("recive message : %s\n", message);
    }

    return 0;
}
