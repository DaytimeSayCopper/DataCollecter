#include <iostream>
#include <semaphore.h>
#include <cstdlib>
#include <windows.h>
#include "collecter.h"
#include "collecter.cpp"
#include "file_send.cpp"

struct File
{
    char path[128];
    char buffer[4096];
};

FileInfo fileInfo;
HANDLE hsem1,hsem2;
Collecter col=Collecter();
FileSend filesend = FileSend();
int sockfd;

DWORD WINAPI collectInfo(PVOID pParam)
{
    WaitForSingleObject(hsem1, INFINITE);//等待信号量
    printf("\n************信息收集中************\n");
    char *dir = (char*)pParam;
    std::cout<<"开始信息收集......"<<std::endl;
    col.GetAllFileInfo(dir);
    fileInfo=col.DateConvert();
    std::cout<<"收集到的文件数量为:"<<fileInfo.file_number<<std::endl;

    for(int i = 0 ; i < fileInfo.file_number; ++i)
    {
        fileInfo.file[i].pack_number = i+1;
        send(sockfd,(const char *)&fileInfo.file[i],sizeof(struct FileNode),0);
        std::cout << fileInfo.file[i].file_name << std::endl;
        Sleep(500);
    }

    std::cout<<"信息收集完毕"<<std::endl;
    ReleaseSemaphore(hsem2, 1, NULL);//释放信号量
}

DWORD WINAPI sendToServer(PVOID pParam)
{
    WaitForSingleObject(hsem2, INFINITE);//等待信号量
    printf("\n************信息发送中************\n");
    std::cout<<"准备发送的文件数量为:"<<fileInfo.file_number<<std::endl;
    int *sockfd = (int *) pParam ;
    std::cout<<"开始向服务器发送数据......"<<std::endl;
    filesend.sendFileInfo(*sockfd, fileInfo);
    std::cout<<"信息发送执行完毕"<<std::endl;
    fileInfo.file_number=0;
    fileInfo.file = NULL;
    col.ClaerFileInfo();
    ReleaseSemaphore(hsem1, 1, NULL);//释放信号量
}

DWORD WINAPI getServer(PVOID pParam)
{
    while(true)
    {
        Sleep(500);
        char buffer[128];
        if(recv(sockfd, buffer, 128, 0) <= 0)
        {
            printf("RECV ERROR :%d\n",WSAGetLastError());
            break;
        }
        if(strncmp(buffer, "newfile", 7) == 0)
        {
            std::cout<<std::endl<<"**********接收服务器写入文件命令中**********"<<std::endl;
            std::cout<<"接收服务器写入文件命令开始......"<<std::endl;
            struct File fl;
            recv(sockfd, (char *)&fl, sizeof(struct File), 0);
            FILE * fp = fopen(fl.path, "w+");
            fprintf(fp, fl.buffer);
            fclose(fp);
            Sleep(500);
            std::cout<<"接收服务器写入文件命令结束"<<std::endl;
            buffer[0] = '\0';
            cout<<endl<<"请输入文件信息检索所在路径，输入-1结束运行:"<<endl;
        }
        else if(strncmp(buffer, "newpath", 7) == 0)
        {
            //std::cout<< buffer+8<<std::endl;
            if(col.setInitDirPath(buffer+8))
            {
                std::cout<<std::endl<<"**********接收服务器获取文件信息命令中**********"<<std::endl;
                std::cout<<"接收服务器获取文件信息命令开始......"<< buffer <<std::endl;

                fileInfo.file_number=0;
                fileInfo.file = NULL;
                col.ClaerFileInfo();

                col.setInitDirPath(buffer+8);
                //std::cout<<"接收服务器newpath获取文件信息命令中1......"<<std::endl;
                col.GetAllFileInfo(buffer+8);
                //std::cout<<"接收服务器newpath获取文件信息命令中2......"<<std::endl;
                fileInfo=col.DateConvert();
                //std::cout<<"接收服务器newpath获取文件信息命令中3......"<<std::endl;
                filesend.sendFileInfo(sockfd, fileInfo);
                //std::cout<<"接收服务器newpath获取文件信息命令中4......"<<std::endl;

                fileInfo.file_number=0;
                fileInfo.file = NULL;
                col.ClaerFileInfo();
                buffer[0] = '\0';
                std::cout<<"接收服务器命令结束"<<std::endl;
                cout<<endl<<"请输入文件信息检索所在路径，输入-1结束运行:"<<endl;
            }
            else
            {
                std::cout<<"服务器命令路径不存在！"<<std::endl;
                cout<<endl<<"请输入文件信息检索所在路径，输入-1结束运行:"<<endl;
            }
        }
    }
}

int main(void)
{
    std::cout<<"请等待，与服务器连接中......"<<std::endl;
    sockfd = filesend.getSocket();
    if(sockfd == 0)
    {
        return 1;
    }
    if(!(filesend.getConnect(sockfd)))
    {
        return 1;
    }
    std::cout<<"与服务器连接成功"<<std::endl;
    HANDLE res = CreateThread(NULL, 0, getServer, NULL, 0, NULL);
    //创建信号量
    hsem1 = CreateSemaphore(NULL, 1, 1, NULL);
    hsem2 = CreateSemaphore(NULL, 0, 1, NULL);
    while(1)
    {
        g1:char dir[100];
        cout<<endl<<"请输入文件信息检索所在路径，输入-1结束运行:"<<endl;
        cin>>dir;
        if(dir[0]=='-'&&dir[1]=='1')
            break;
        if(col.setInitDirPath(dir)==false)
        {
            cout<<"不存在该目录"<<endl;
            goto g1;
            Sleep(500);
            return 1;
        }
        else
        {
            HANDLE task01 = CreateThread(NULL, 0, collectInfo, dir, 0, NULL);
            HANDLE task02 = CreateThread(NULL, 0, sendToServer, &sockfd, 0, NULL);
            //std::cout<<std::endl<<"*******9999******"<<std::endl;
            //等待子线程结束
            WaitForSingleObject(task01, INFINITE);
            WaitForSingleObject(task02, INFINITE);
            std::cout<<std::endl<<"------------------一次信息收集发送执行完毕------------------"<<std::endl;
            //关闭线程句柄
            CloseHandle(task01);
            CloseHandle(task02);
        }
    }
    //关闭线程句柄
    CloseHandle(res);
    CloseHandle(hsem1);
    CloseHandle(hsem2);
    cout<<"正常退出程序"<<endl;
    return 1;
}

