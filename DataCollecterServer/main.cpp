#include <stdio.h>
#include <map>
#include <thread>
#include "src/server.h"
#include "src/datashow.h"

using std::string;


Server server;

DataShow dshow("./collect_information.xls");

std::map<string, struct FileInfo> file;

void DataCollecter_t(int client_fd, char * ip);

void Command_t();

int main()
{
    time_t t = time((time_t *) 0);

    server.TCPListen();

    dshow.OpenFile();

    printf("%slistening......\n", ctime(&t));

    std::thread cmd_t(Command_t);
    cmd_t.detach();

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
    char IP[15];
    strncpy(IP, ip, 15);

    while (true)
    {
        if(server.ReadFileInfo(client_fd, &file_info) == 0)
        {
            server.QuitHandler(client_fd);
            printf("客户端%d(ip:%s)断开连接\n", client_fd, IP);
            break;
        }
        printf("完成收集来自%d(ip:%s)的数据\t", client_fd, IP);

        dshow.AddInfo(&file_info, IP);

        file.erase(string(IP));
        file.insert(std::map<string, struct FileInfo>::value_type(string(IP), file_info));

        printf("写入成功!\n");
    }
}


void Command_t()
{
    char cmd[10];
    char ip[15];
    while(true)
    {
        printf("cmd:");scanf("%s", cmd);
        if(strcmp(cmd, "newpath") == 0)
        {
            printf("ip:");scanf("%s", ip);
            if(server.isTarget(ip) == true )
            {
                printf("client %s is online\n", ip);
                char path[64], buffer[128];
                printf("path:");scanf("%s", path);
                strcpy(buffer, "newpath/");
                strcat(buffer, path);
                server.TCPSendBufferByIP(buffer, ip);

                printf("\tCMD-newpath is send!\n");
            }
            else
                fprintf(stderr, "ip为%s的客户端没有连接!\n", ip);
        }
        else if(strcmp(cmd, "newfile") == 0)
        {
            printf("ip:");scanf("%s", ip);
            if(server.isTarget(ip) == true )
            {
                printf("client %s is online\n", ip);
                struct File fl;
                printf("path+filename:");scanf("%s", fl.file_path);
                printf("file content:");scanf("%s", fl.buffer);
                server.TCPSendBufferByIP("newfile", ip);
                usleep(50000);
                server.TCPSendFileByIP(fl, ip);

                printf("\tCMD-newfile is send!\n");
            }
            else
                fprintf(stderr, "ip为%s的客户端没有连接!\n", ip);
        }
        else if(strcmp(cmd, "searchbyip") == 0)
        {
            printf("ip:");scanf("%s", ip);
            struct FileInfo file_info = file[string(ip)];
            if(file_info.file == NULL)
            {
                fprintf(stderr, "查无此ip\n");
            }
            else
            {
                char file_name[32];
                printf("file name:");scanf("%s", file_name);
                for(int i = 0; i < file_info.file_number; i++)
                {
//                    printf("%s\n", file_info.file[i].file_name);

                    if (strncmp(file_info.file[i].file_name, file_name, 128) == 0) {
                        printf("full name is : %s%s\n",
                               file_info.file[i].file_path, file_info.file[i].file_name);
                    }
                }
            }

        }
        else if(strcmp(cmd, "searchall") == 0)
        {
            char file_name[32];
            printf("file name:");scanf("%s", file_name);

            std::map<string,struct FileInfo>::iterator it;
            for(it = file.begin(); it != file.end(); it++)
            {
                for(int i = 0; i < it->second.file_number; i++)
                {
//                   printf("%s\n", file_info.file[i].file_name);

                    if (strncmp(it->second.file[i].file_name, file_name, 128) == 0) {
                        printf("full name is : %s%s\n",
                               it->second.file[i].file_path, it->second.file[i].file_name);
                    }
                }
            }
        }
    }
}
