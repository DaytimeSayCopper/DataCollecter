#ifndef WUST_0719_FILE_SEND_H
#define WUST_0719_FILE_SEND_H

#include "fileNode.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE 1024
class File_Send{
private:
    int sockfd,confd;
    struct sockaddr_in server_addr;    // 定义IPv4套接口地址数据结构
public:
    File_Send(char ip[]);
    ~File_Send();
    int getSockfd();
    bool ConnectToServer();
    void sendFiles(struct fileInfo file_main,int sockfd);
};

#endif