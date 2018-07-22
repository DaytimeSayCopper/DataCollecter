//
// Created by mylord on 18-7-19.
//

#ifndef DATACOLLECTERSERVER_SERVER_H
#define DATACOLLECTERSERVER_SERVER_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "clientinfo.h"
#include "fileinfo.h"
#include "findway.h"

class Server : public ClientInfo
{
private:
    int listen_fd;
    sockaddr_in server_addr;
    int port_number;
    int listen_size;

public:
    Server(int port_number = 5555, int listen_size = 10);

    void TCPInit();

    void TCPListen();

    int TCPAcceptConnection(char * ip);

    int ReadFileInfo(int sock_fd, struct FileInfo * file_info);

    int QuitHandler(int sock_fd);

    bool isTarget(char * ip);

    int TCPSendBufferByIP(char * buff, char * ip);

    int TCPSendFileByIP(struct File fl, char * ip);
};


#endif //DATACOLLECTERSERVER_SERVER_H
