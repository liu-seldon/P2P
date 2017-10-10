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


int main() {
    int sockfd;
    struct sockaddr_in address;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("119.29.197.182");
    address.sin_port = htons(SERV_PORT);

    socklen_t sin_len;
    char message[MAX_LEN];
   int count = 5; 
    while(count) {
        sprintf(message, "send message %d count", count);
        sendto(sockfd, message,sizeof(message),0,(struct sockaddr *)&address,sizeof(address));
        printf("send message : %d\n", count);
        count--;
    }

    return 0;
}
