#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5050


int main(int argc, char const* argv[]){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buf[1024];
    char* greeting = "Hello client";

    int readsize;
    
    char client_message[1024];
    //create socket fd
    if((server_fd = socket(AF_INET, SOCK_STREAM,0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,3)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }


    while(1){
        printf("waiting for a connection on port %d\n",PORT);
        if((new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }

        readsize = read(new_socket,buf,1024);
        printf("%s\n",buf);
        send(new_socket,greeting,strlen(greeting),0);
        

        //recv(new_socket,buf,sizeof(buf),0);
        //printf("%s",buf);
            
        while( (readsize = recv(new_socket , client_message , 2000 , 0)) > 0 )
        {
            //print client message to console
            printf("%s",client_message);
            bzero(&client_message,sizeof(client_message));
        }

        if(readsize == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(readsize == -1)
        {
            perror("recv failed");
        }
        


        close(new_socket);
        //close(server_fd);
    }
    
    shutdown(server_fd,SHUT_RDWR);
    return 0;
}