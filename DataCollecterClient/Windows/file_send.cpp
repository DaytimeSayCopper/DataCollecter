#include <WINSOCK2.H>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "file_send.h"

#pragma comment(lib, "ws2_32.lib")

//构造函数
FileSend::FileSend()
{
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("118.89.22.167");//IP
    address.sin_port = htons(PORT); //端口
}

int FileSend::getSocket()
{
    //初始化WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        std::cout<<std::endl<<"WSA Created Failed !"<<std::endl;
        return 0;
    }
    //创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);  //此处 IPPROTO_TCP一定要注意，否则导致失败！
    //printf("%d",sockfd);
    if(sockfd == INVALID_SOCKET)
    {
        std::cout<<std::endl<<"Socket Created Failed "<<std::endl;
        return 0;
    }
    //printf("Socket为：%d\n",sockfd);
    return sockfd;
}

bool FileSend::getConnect(int sockfd)
{
    //获得连接
    if (connect(sockfd, (sockaddr *)&address, sizeof(address)) == -1)
    {
        std::cout<<std::endl<<"Connect Failed "<<std::endl;
        //失败则关闭ocket
        fprintf(stderr,"ERR:%s\n",strerror(errno));
        //closesocket(sockfd);
        return false;
    }
    return true;
}

void FileSend::sendFileInfo(int sockfd, struct FileInfo getFile)
{
    /*std::cout<<"in this"<<std::endl;
    std::cout<<"files' number is :"<<getFile.file_number<<std::endl;*/
    send(sockfd,(const char *)&getFile.file_number,sizeof(int),0);
    Sleep(500);
    for(int i = 0 ; i < getFile.file_number; ++i)
    {
        getFile.file[i].pack_number = i+1;
        send(sockfd,(const char *)&getFile.file[i],sizeof(struct FileNode),0);
        std::cout << getFile.file[i].file_name << std::endl;
        Sleep(500);
    }
}


















