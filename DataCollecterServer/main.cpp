#include <stdio.h>
#include <thread>
#include "src/server.h"
#include "src/datashow.h"

Server server;

DataShow dshow("./collect_information.txt");


void DataCollecter_t(int client_fd, char * ip);

int main()
{
    server.TCPListen();

    dshow.OpenFile();

    printf("listening......\n");

    while(true)
    {
        char ip[15];

        int client_fd = server.TCPAcceptConnection(ip);

        std::thread dc_t(DataCollecter_t, client_fd, ip);

        dc_t.detach();
    }

    return 0;
}

void DataCollecter_t(int client_fd, char * ip)
{
    struct FileInfo file_info;

    while (true)
    {
        if(server.ReadFileInfo(client_fd, &file_info) == 0)
        {
            server.QuitHandler(client_fd);
            printf("客户端%d(ip:%s)断开连接\n", client_fd, ip);
            break;
        }
        printf("完成收集来自%s的数据\t", ip);

//        for(int i = 0 ; i < 10 ; i++)
//            printf("%s %s %d %d\n", file_info.file[i].file_name, file_info.file[i].file_path
//                ,file_info.file[i].file_size, file_info.file[i].pack_number);

        dshow.AddInfo(&file_info, ip);
        printf("写入成功!\n");
    }
}
