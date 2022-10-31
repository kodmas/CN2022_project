#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5050

int main(int argc,char const* argv[]){
    int sock = 0, readsize,client_fd;
    struct sockaddr_in serv_addr;
    char* greet = "Hello from client";
    char buf[1024];

    if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("\n Invalid address/ Address not supported \n");
        return -1;
    }

    if((client_fd = connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0){
        printf("\nConnection failed \n");
        return -1;
    }

    send(sock, greet, strlen(greet),0);

    readsize = read(sock,buf,1024);
    printf("%s\n",buf);

    while(1){
        char clientmsg[1024];
        printf("Enter message: \n");
        fgets(clientmsg, sizeof(clientmsg),stdin);

        //Send some data
        if( send(sock , clientmsg , strlen(clientmsg) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        } 
        
        //clientmsg = write(client_fd,buf,sizeof(buf));
    }
    

    


    close(client_fd);
    return 0;

}