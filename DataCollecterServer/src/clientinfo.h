//
// Created by mylord on 18-7-19.
//

#ifndef DATACOLLECTERSERVER_CLIENTINFO_H
#define DATACOLLECTERSERVER_CLIENTINFO_H

#include <stdio.h>
#include <vector>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>



struct ClientStr
{
    sockaddr_in client_addr;    //ip获取方式:inet_ntoa(temp.client_addr.sin_addr)
    int client_fd;
};


class ClientInfo
{
private:
    std::vector<struct ClientStr> client_info;
protected:
    std::vector<struct ClientStr> & get_client_info();
};


#endif //DATACOLLECTERSERVER_CLIENTINFO_H
