/*
   C socket server example
From: http://www.binarytides.com/server-client-example-c-sockets-linux/
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

/*
 * This will handle connection for each client
 * */
int connection_handler(int sock) {
    //Get the socket descriptor
    int read_size;
    char *message , client_message[2000];

    //Receive a message from client
    if( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
    }

    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if(read_size == -1) {
        perror("recv failed");
    }

    return 0;
}


int main(int argc , char *argv[]) {
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");





    int i;
    pid_t pid;
    for(i = 0; i < 3; ++i) {
        pid = fork();
        if(pid < 0) {
            printf("error in fork!");  
        } else if(pid == 0) {
            printf("I'am the parent process\n");
        } else {
            printf("I'm the child pid:%d\n", getpid());
            c = sizeof(struct sockaddr_in);
            while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
                printf("Accept client socket pid:%d\n", getpid());

                unsigned int t = client.sin_addr.s_addr;
                printf("accept.fd=%d, ip=%d.%d.%d.%d\n", client_sock, t%256, t/256%256, t/256/256%256, t/256/256/256);
                connection_handler(client_sock);
                if(getpid() % 3== 0) {
                    sleep(10);
                }
            }

            if (client_sock < 0) {
                perror("accept failed");
                return 1;
            }
        }
    }

    if(pid > 0) {
        //sleep(100);
    }

    return 0;
}
