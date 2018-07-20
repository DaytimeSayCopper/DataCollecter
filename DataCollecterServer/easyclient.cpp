//
// Created by mylord on 18-7-19.
//

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>
#include "src/fileinfo.h"


#define PORT_NUMBER 5555


int main(int argc, char * argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;     //定义服务器端套接字数据结构server_addr
    struct hostent *host;

    if (argc != 2) {
        fprintf(stderr, "Usage:%s hostname \a\n", argv[0]);
        exit(1);
    }

    if ((host = gethostbyname(argv[1])) == NULL) {   //获得命令行的第二个参数——主机名
        fprintf(stderr, "The host name error\n");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {   //客户程序开始建立socket描述符
        fprintf(stderr, "Socket Error:%s\a\n", strerror(errno));
        exit(1);
    }

    //客户端填充服务端的资料
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUMBER);
    server_addr.sin_addr = *((struct in_addr *) host->h_addr);

    //客户程序发起连接请求
    if (connect(sockfd, (struct sockaddr *) (&server_addr), sizeof(struct sockaddr)) < 0) {
        fprintf(stderr, "Connect Error:%s\a\n", strerror(errno));
        close(sockfd);
        exit(1);
    }

    while (true)
    {
           struct FileNode fn;
        int num = 10;
        write(sockfd, &num, sizeof(int));
        usleep(1000);
        strncpy(fn.file_name, "filename", 128);
        strncpy(fn.file_path, "/path/path/path", 1024);
        for (int i = 1; i <= num; i++) {
            fn.pack_number = i;
            fn.file_size = i * 1024;
            write(sockfd, &fn, sizeof(struct FileNode));
            usleep(10000);
        }
        printf("yes\n");
        sleep(5);
    }
}