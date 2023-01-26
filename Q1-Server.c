#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;

        /* To call socket() function */
        sockfd = socket(AF_INET, SOCK_STREAM , 0);
        if(sockfd < 0) {
          perror("ERROR opening socket");
          exit(1);
        }

        /* To initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(argv[1]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        /* To bind the host address using bind() call */
        if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0) {
          perror("ERROR on binding");
          exit(1);
        }

        /* To start listening for the clients here, it will go in sleep mode to wait
           for the incoming connection */
        listen(sockfd,5);
        clilen = sizeof(cli_addr);

        /* To accept the actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
          perror("ERROR on accept");
          exit(1);
        }

        /* If the connection is established, then it will start communicating */
        bzero(buffer,256);
        int random_number = rand() % 900 + 100; // to generate random number between 100 and>
        sprintf(buffer,"%d", random_number);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0) {
          perror("ERROR writing to socket");
          exit(1);
        }

        close(newsockfd);
        close(sockfd);
        return 0;
  }

