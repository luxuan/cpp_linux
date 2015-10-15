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
void *connection_handler(void *socket_desc) {
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
    struct sockaddr_in client;
    int client_sock, c;

    printf("Create thread, tid:%lld\n", pthread_self());
    c = sizeof(struct sockaddr_in);
    while((client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)) > 0) { 
        unsigned int t = client.sin_addr.s_addr;
        printf("pid=%lld, accept.fd=%d, ip=%d.%d.%d.%d\n", pthread_self(), client_sock, 
                    t%256, t/256%256, t/256/256%256, t/256/256/256);

        //Receive a message from client
        if( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ) {
            //Send the message back to client
            write(client_sock , client_message , strlen(client_message));
        }

        if(read_size == 0) {
            puts("Client disconnected");
            fflush(stdout);
            break;
        } else if(read_size == -1) {
            perror("recv failed");
            break;
        }

        if(client_sock % 3 == 0) {
            sleep(10);
        }
    }

    //Free the socket pointer
    free(socket_desc);
     
    return 0;
}


int main(int argc , char *argv[]) {
    int socket_desc;
    struct sockaddr_in server;
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
    pthread_t sniffer_threads[3];
    for(i = 0; i < 3; ++i) {
        int *new_sock = malloc(sizeof(int));
        *new_sock = socket_desc;
         
        if( pthread_create( &sniffer_threads[i] , NULL ,  connection_handler , (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
    }

    for(i = 0; i < 3; ++i) {
        // Now join the thread , so that we dont terminate before the thread
        pthread_join( sniffer_threads[i] , NULL);
    }
     
    return 0;
}
