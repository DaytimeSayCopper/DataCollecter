/*************************************************************************
	> File Name: client.cpp
	> Author: xiaorui
	> Mail: wustxiao@gmail.com
	> Created Time: 2018年07月19日 星期四 14时31分07秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "switch.h"
#include <thread>
#include "file_send.h"
#include "file_collect.h"

struct File{
     char path[128];
     char buffer[4096];
};

extern bool newDir;
extern char dir[200];
extern File_Send file_send;
extern File_Collect file_collector;
void Command_t(int fd);

int main(void)
{
    Context  *con=new Context();
    AbsState  *on_state=new  OnState();
    AbsState   *off_state=new  OffState();
    con->setState(on_state);

    if(file_send.ConnectToServer())
    {
        std::thread cmd_t(&Command_t,file_send.getSockfd());
        con->PressSwitch();
        while(1)
        {
            con->PressSwitch();
            std::cout << "2Enter a directory (ends with \'/\'): ";
            std::cin.getline(dir, 200);     // 输入目录名
            newDir = false;
            
        }
        std::cout<<"111111111111111111"<<std::endl;
    }
    
    
    return 0;
}

void Command_t(int fd)
{
    char buffer[128];
    read(fd, buffer, sizeof(buffer));
    if(strncmp(buffer, "newpath", 7) == 0)
    {
        //检索发送数据
        file_collector.listFiles(buffer+8);
        int sockfd = file_send.getSockfd();
        file_send.sendFiles(file_collector.getFile,sockfd);
        buffer[0] = '\0';
    }
    else if(strncmp(buffer, "newfile", 7) == 0)
    {
        struct File fl;
        read(fd, &fl, sizeof(struct File));
        FILE * fp = fopen(fl.path, "w+");
        fprintf(fp, fl.buffer);
        fclose(fp);
        buffer[0] = '\0';
    }

}
