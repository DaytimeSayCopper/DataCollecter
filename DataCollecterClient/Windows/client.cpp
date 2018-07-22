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
    WaitForSingleObject(hsem1, INFINITE);//�ȴ��ź���
    printf("\n************��Ϣ�ռ���************\n");
    char *dir = (char*)pParam;
    std::cout<<"��ʼ��Ϣ�ռ�......"<<std::endl;
    col.GetAllFileInfo(dir);
    fileInfo=col.DateConvert();
    std::cout<<"�ռ������ļ�����Ϊ:"<<fileInfo.file_number<<std::endl;

    for(int i = 0 ; i < fileInfo.file_number; ++i)
    {
        fileInfo.file[i].pack_number = i+1;
        send(sockfd,(const char *)&fileInfo.file[i],sizeof(struct FileNode),0);
        std::cout << fileInfo.file[i].file_name << std::endl;
        Sleep(500);
    }

    std::cout<<"��Ϣ�ռ����"<<std::endl;
    ReleaseSemaphore(hsem2, 1, NULL);//�ͷ��ź���
}

DWORD WINAPI sendToServer(PVOID pParam)
{
    WaitForSingleObject(hsem2, INFINITE);//�ȴ��ź���
    printf("\n************��Ϣ������************\n");
    std::cout<<"׼�����͵��ļ�����Ϊ:"<<fileInfo.file_number<<std::endl;
    int *sockfd = (int *) pParam ;
    std::cout<<"��ʼ���������������......"<<std::endl;
    filesend.sendFileInfo(*sockfd, fileInfo);
    std::cout<<"��Ϣ����ִ�����"<<std::endl;
    fileInfo.file_number=0;
    fileInfo.file = NULL;
    col.ClaerFileInfo();
    ReleaseSemaphore(hsem1, 1, NULL);//�ͷ��ź���
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
            std::cout<<std::endl<<"**********���շ�����д���ļ�������**********"<<std::endl;
            std::cout<<"���շ�����д���ļ����ʼ......"<<std::endl;
            struct File fl;
            recv(sockfd, (char *)&fl, sizeof(struct File), 0);
            FILE * fp = fopen(fl.path, "w+");
            fprintf(fp, fl.buffer);
            fclose(fp);
            Sleep(500);
            std::cout<<"���շ�����д���ļ��������"<<std::endl;
            buffer[0] = '\0';
            cout<<endl<<"�������ļ���Ϣ��������·��������-1��������:"<<endl;
        }
        else if(strncmp(buffer, "newpath", 7) == 0)
        {
            //std::cout<< buffer+8<<std::endl;
            if(col.setInitDirPath(buffer+8))
            {
                std::cout<<std::endl<<"**********���շ�������ȡ�ļ���Ϣ������**********"<<std::endl;
                std::cout<<"���շ�������ȡ�ļ���Ϣ���ʼ......"<< buffer <<std::endl;

                fileInfo.file_number=0;
                fileInfo.file = NULL;
                col.ClaerFileInfo();

                col.setInitDirPath(buffer+8);
                //std::cout<<"���շ�����newpath��ȡ�ļ���Ϣ������1......"<<std::endl;
                col.GetAllFileInfo(buffer+8);
                //std::cout<<"���շ�����newpath��ȡ�ļ���Ϣ������2......"<<std::endl;
                fileInfo=col.DateConvert();
                //std::cout<<"���շ�����newpath��ȡ�ļ���Ϣ������3......"<<std::endl;
                filesend.sendFileInfo(sockfd, fileInfo);
                //std::cout<<"���շ�����newpath��ȡ�ļ���Ϣ������4......"<<std::endl;

                fileInfo.file_number=0;
                fileInfo.file = NULL;
                col.ClaerFileInfo();
                buffer[0] = '\0';
                std::cout<<"���շ������������"<<std::endl;
                cout<<endl<<"�������ļ���Ϣ��������·��������-1��������:"<<endl;
            }
            else
            {
                std::cout<<"����������·�������ڣ�"<<std::endl;
                cout<<endl<<"�������ļ���Ϣ��������·��������-1��������:"<<endl;
            }
        }
    }
}

int main(void)
{
    std::cout<<"��ȴ����������������......"<<std::endl;
    sockfd = filesend.getSocket();
    if(sockfd == 0)
    {
        return 1;
    }
    if(!(filesend.getConnect(sockfd)))
    {
        return 1;
    }
    std::cout<<"����������ӳɹ�"<<std::endl;
    HANDLE res = CreateThread(NULL, 0, getServer, NULL, 0, NULL);
    //�����ź���
    hsem1 = CreateSemaphore(NULL, 1, 1, NULL);
    hsem2 = CreateSemaphore(NULL, 0, 1, NULL);
    while(1)
    {
        g1:char dir[100];
        cout<<endl<<"�������ļ���Ϣ��������·��������-1��������:"<<endl;
        cin>>dir;
        if(dir[0]=='-'&&dir[1]=='1')
            break;
        if(col.setInitDirPath(dir)==false)
        {
            cout<<"�����ڸ�Ŀ¼"<<endl;
            goto g1;
            Sleep(500);
            return 1;
        }
        else
        {
            HANDLE task01 = CreateThread(NULL, 0, collectInfo, dir, 0, NULL);
            HANDLE task02 = CreateThread(NULL, 0, sendToServer, &sockfd, 0, NULL);
            //std::cout<<std::endl<<"*******9999******"<<std::endl;
            //�ȴ����߳̽���
            WaitForSingleObject(task01, INFINITE);
            WaitForSingleObject(task02, INFINITE);
            std::cout<<std::endl<<"------------------һ����Ϣ�ռ�����ִ�����------------------"<<std::endl;
            //�ر��߳̾��
            CloseHandle(task01);
            CloseHandle(task02);
        }
    }
    //�ر��߳̾��
    CloseHandle(res);
    CloseHandle(hsem1);
    CloseHandle(hsem2);
    cout<<"�����˳�����"<<endl;
    return 1;
}

