#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 200
#define SERV_PORT 34567
#define CLIENT_PORT 45253

typedef struct {
    char name[20];
}User;


int main() {
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("119.29.197.182");
    address.sin_port = htons(SERV_PORT);

    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(CLIENT_PORT);
    if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) == -1) {
        printf("bind error\n");
        exit(-1);
    }


    User user;
    sprintf(user.name, "%s", "liuzeng-ubuntu");
    sendto(sockfd, user.name , sizeof(User), 0, (struct sockaddr *)&address,sizeof(address));

    char message[MAX_LEN];
    socklen_t sin_len;
    while(1) {
        recvfrom(sockfd, message, MAX_LEN, 0, (struct sockaddr*)&servaddr, &sin_len);
        printf("receive data\n");
        char* ip = inet_ntoa(servaddr.sin_addr);
        int port = ntohs(servaddr.sin_port);
        printf("client ip is %s\n, prot is %d\n", ip, port);
        printf("recive message : %s\n", message);
    }

    return 0;
}
