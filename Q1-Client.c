#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])  {
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent * server;
        char buffer[256];

        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)  {
          perror("ERROR opening socket");
          exit(1);
        }

        server = gethostbyname(argv[1]);
        if (server == NULL) {
          fprintf(stderr,"ERROR, no such host\n");
          exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        portno = atoi(argv[2]);
        serv_addr.sin_port = htons(portno);

        /*  To connect to the server */
        if(connect(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
          perror("ERROR connecting");
          exit(1);
        }

        /* To ask for a message from the user, this message will read by the server */
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n >0) {
          perror("ERROR reading from socket");
          exit(1);
        }

        printf("Random number received from server: %s\n", buffer);
        close(sockfd);
        return 0;
        }



