#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define PORT 5050



int main(int argc, char const* argv[]){
    

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char* greeting = "Hello client";

    int readsize;
    
    char client_message[1024];
    //
    int ret;
    long fsize;
    FILE *fp = fopen("content.html", "rb");
    if (!fp){
        perror("The file was not opened");    
        exit(1);    
    }

    printf("The file was opened\n");

    if (fseek(fp, 0, SEEK_END) == -1){
        perror("The file was not seeked");
        exit(1);
    }

    fsize = ftell(fp);
    if (fsize == -1) {
        perror("The file size was not retrieved");
        exit(1);
    }
    rewind(fp);

    char *msg = (char*) malloc(fsize);
    if (!msg){
        perror("The file buffer was not allocated\n");
        exit(1);
    }
/*
    if (fread(msg, fsize, 1, fp) != 1){
        perror("The file was not read\n");
        exit(1);
    }
    else{
        printf("------\n");
    }
    */
    //fclose(fp);
    rewind(fp);
    //create socket fd
    if((server_fd = socket(AF_INET, SOCK_STREAM,0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Creating Socket...\n");
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Binding...\n");
    }

    if(listen(server_fd,3)<0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Listening...\n");
    }

        printf("waiting for a connection on port %d\n",PORT);
        if((new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        else{
            printf("Connection Established\n");
        }
        
        
        
        //send html header to client
        //printf("Length of file=%d\n", fsize);
        //write(new_socket, buf, strlen(buf));
        printf("Header was send\n");
        
        //printf("The file size is %ld\n", fsize);  
        //bzero(&buf,sizeof(buf));
        char buf[fsize];
        bzero(&buf,strlen(buf));
        sprintf(buf, "HTTP/1.1 200 OK\nContent-Length: %ld\nConnection: keep-alive\nContent-Type: %s\n charset=UTF-8\n\n", 2*fsize-100, "text/html");
        write(new_socket,buf,fsize);
        //recv(new_socket,buf,sizeof(buf),0);
        bzero(&buf,sizeof(buf));
        /*
        const char *a = "<html>\n<head>\n\t<meta http-equiv="Content-Type" content="text/html; charset=utf-8">\t\n</head>\n\t<title>CN Project Phase 1</title>\n\t\t<body>\n\t\t\t<h1>Personal Profile</h1>\n\t\t\t<p>Studeccccccccccccccccccccccnt ID";
        const char *b = ": b09901142</p>\n\t\t\t<p>Department EE Year 3</p>\n\t\t\t<p>Name: Jerry Lu</p>\n\t\t</body></html>";
        send(new_socket,a,strlen(a),0);
        send(new_socket,b,strlen(b),0);            */
        if((ret = fread(buf, fsize,fsize,fp)) > 0){
            printf("number of bytes read=%d\n", ret);
            //write data to client,it will make connection reset
            send(new_socket, buf, strlen(buf),0);
            //send(new_socket, buf, strlen(buf),0);
            printf("%s\n",buf);
        }
        else{
            printf("####\n");
        }
        /*
            while ((ret = read(html, buff, 1023)) > 0)
                {
                    printf("number of bytes read=%d\n", ret);
                    //write data to client,it will make connection reset
                    write(client_socketfd, buff, ret);
                }
            }*/
        
        while(1){

        //readsize = read(new_socket,buf,1024);
        //printf("%s\n",buf);
        send(new_socket,greeting,strlen(greeting),0);
        //recv(new_socket,buf,sizeof(buf),0);
        //printf("%s",buf);
            
        while( (readsize = recv(new_socket , client_message , 2000 , 0)) > 0 )
        {
            //print client message to console
            printf("%s\n",client_message);
            bzero(&client_message,sizeof(client_message));
        }
/*
        if(readsize == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(readsize == -1)
        {
            perror("recv failed");
        }
        
*/

        
        //shutdown(server_fd,SHUT_RDWR);
        //close(server_fd);
    }
    //free(server_fd);
    close(new_socket);
    shutdown(server_fd,SHUT_RDWR);
    return 0;
}