//
// Created by mylord on 18-7-19.
//

#include "server.h"


Server::Server(int port_number, int listen_size)
{
    this->listen_size = port_number;
    this->listen_size = listen_size;

    TCPInit();
}


void Server::TCPInit()
{
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Socket Init Error:%s\n\a", strerror(errno));
        exit(1);
    }

    //填充server_addr结构体
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port_number);

    if(bind(listen_fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Bind Error:%s\n\a", strerror(errno));
        exit(1);
    }
}


void Server::TCPListen()
{
    if(listen(listen_fd, listen_size) == -1)
    {   //端口绑定成功，监听socketfd描述符，同时处理的最大连接请求数为listen_size
        fprintf(stderr, "Listen error:%s\n\a", strerror(errno));
        exit(1);
    }
}


int Server::TCPAcceptConnection(char * ip)
{
    int sockaddr_size = sizeof(struct sockaddr_in);
    struct ClientStr temp;

    if((temp.client_fd = accept(listen_fd, (struct sockaddr *)(&temp.client_addr),
                                     (socklen_t *) &sockaddr_size)) == -1)
    {   //调用accept接受一个连接请求
        fprintf(stderr, "Accept error:%s\n\a", strerror(errno));
        exit(1);
    }

    strncpy(ip, inet_ntoa(temp.client_addr.sin_addr), 15);

    printf("Connected from %s\tclient fd is %d\n", ip, temp.client_fd);

    get_client_info().push_back(temp);

    return temp.client_fd;
}



int Server::ReadFileInfo(int sock_fd, struct FileInfo * file_info)
{
    int nbytes = 0;
    int pack_number;
    struct FileNode temp;

    nbytes = read(sock_fd, &pack_number, sizeof(int));
    if(nbytes == 0)
        return 0;
    else if(nbytes < 0)
        fprintf(stderr, "Read Pack Number Error:%s\n", strerror(errno));

    file_info->file = (struct FileNode *)malloc(sizeof(struct FileNode) * pack_number);

    for(int i = 1; i <= pack_number; i++)
    {
        nbytes = read(sock_fd, &temp, sizeof(struct FileNode));
        if(nbytes == 0)
            return 0;
        else if(nbytes < 0)
            fprintf(stderr, "Read File Info Error:%s\n", strerror(errno));

        if(temp.pack_number == i)
            file_info->file[i] = temp;
        else if(temp.pack_number > i)
        {
            fprintf(stderr, "Pack %d Missed!\n", i);

            file_info->file[i++].pack_number = -1;
            file_info->file[i] = temp;
        }
        else
            fprintf(stderr, "tan90`!!\n");
    }

    return 1;
}

int Server::QuitHandler(int sock_fd)
{
    std::vector<struct ClientStr>::iterator client_fd_it = find_if(
            get_client_info().begin(), get_client_info().end(), FindByFd(sock_fd));

    get_client_info().erase(client_fd_it);

    close(sock_fd);
}