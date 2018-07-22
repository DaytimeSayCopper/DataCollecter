#include "file_send.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#define PORT 5555

File_Send::File_Send(char ip[])
{
    struct hostent* host;
    if ((host = gethostbyname(ip)) == NULL) {   //获得命令行的第二个参数——主机名
        fprintf(stderr, "The host name error\n");
        exit(1);
    }
    //struct sockaddr_in client_addr;
    int addr_len = sizeof(struct sockaddr_in);
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)    // 建立一个socket
    {       
        perror("socket created failed!");
        exit(1);
    }else{
        std::cout<<"socket created successfully !"<<std::endl;
        std::cout<<"sockfd = "<<sockfd<<std::endl;
    }
    bzero(&server_addr,addr_len);    // 清空代表地址结构的结构体变量
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *((struct in_addr *) host->h_addr);    // IP地址设为本机IP
}

int File_Send::getSockfd()
{
    return sockfd;
}

File_Send::~File_Send()
{

}

void File_Send::sendFiles(struct fileInfo file_main,int sockfd)
{
    std::cout<<"开始发送信息"<<std::endl;
    std::cout<<"文件数量为："<<file_main.file_number<<std::endl;
    send(sockfd, &file_main.file_number,sizeof(int),0);
    usleep(500000);
   
    fflush(stdout);
    for(int i = 0 ; i < file_main.file_number; ++i)
    {
        file_main.file[i].pack_number = i+1;
        write(sockfd,&file_main.file[i],sizeof(struct fileNode));
        std::cout << file_main.file[i].file_name << std::endl;
        usleep(500000);
    }
    std::cout<<"发送信息完毕!"<<std::endl;
}

bool File_Send::ConnectToServer()
{
    int confd;
    if((confd = connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))) == -1)
    {
        perror("Connect failed !");
        return false;
        exit(1);
    }else{
        std::cout<<"Connect Successfully !"<<std::endl;
        return true;
    }
}
