//
// Created by mylord on 18-7-19.
//

#ifndef DATACOLLECTERSERVER_FINDWAY_H
#define DATACOLLECTERSERVER_FINDWAY_H

#include <algorithm>
#include <string.h>
#include <vector>
#include "clientinfo.h"

class FindByFd
{
private:
    int fd;

public:
    FindByFd(int fd)
    {
        this->fd = fd;
    }
    bool operator()(std::vector<struct ClientStr>::value_type & value)
    {
        return value.client_fd == this->fd;
    }
};


class FindByIP
{
private:
    char ip[15];

public:
    FindByIP(char * ip)
    {
        strncpy(this->ip, ip, 15);
    }
    bool operator()(std::vector<struct ClientStr>::value_type & value)
    {
        return strcmp(this->ip, inet_ntoa(value.client_addr.sin_addr)) == 0;
    }
};

#endif //DATACOLLECTERSERVER_FINDWAY_H
