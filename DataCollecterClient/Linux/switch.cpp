#include "switch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <unistd.h>
#include "file_collect.h"
#include "file_send.h"

pthread_mutex_t mutex;
sem_t sem_collect;
sem_t sem_send;

File_Collect file_collector;    // 创建文件收集者临时对象
File_Send file_send("118.89.22.167");       // 创建文件发送者对象
bool newDir = true;
bool always = true;

char dir[200];
void collectInfo(char dir[])
{
    sem_wait(&sem_collect); // sem_collect-1
    std::cout<<"进入collectInfo"<<std::endl;
    file_collector.listFiles(dir);
    std::cout<<"文件数量:"<<file_collector.getFile.file_number<<std::endl;
    sem_post(&sem_send);    // sem_send+1
    std::cout<<"collectInfo执行完毕"<<std::endl;
}

void sendToServer(int sockfd)
{
    pthread_mutex_lock(&mutex);
    sem_wait(&sem_send);    // sem_send-1
    std::cout<<"进入sendToServer"<<std::endl;
    file_send.sendFiles(file_collector.getFile,sockfd);
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_collect); // sem_collect+1
    std::cout<<"sendToServer执行完毕"<<std::endl;
}


void OnState::handle(Context *pContext)
{
    // if(file_send.ConnectToServer())
    // {
        int res1,res2;
        res1 = sem_init(&sem_collect,0,1);   // 初始收集信号量为1
        if(res1)//初始化信号量失败
        {
            perror("sem_collect Semaphore initialization failed\n");
            exit(EXIT_FAILURE);
        }

        res2 = sem_init(&sem_send,0,0);     // 初始发送信号量为0
        if(res2)//初始化信号量失败
        {
            perror("sem_send Semaphore initialization failed\n");
            exit(EXIT_FAILURE);
        }

            

            std::cout << "1Enter a directory (ends with \'/\'): ";
            if(newDir == true)
            {
                std::cin.getline(dir, 200);     // 输入目录名
            }
            always = false;
            newDir = false;
            pthread_mutex_init(&mutex,NULL);
            std::cout<<"22222222222222222"<<std::endl;
            
            int sockfd = file_send.getSockfd();

            std::thread task01(&collectInfo,dir);
            std::thread task02(&sendToServer,sockfd);
            task01.join();
            task02.join();

            std::cout<<"整个发送过程结束"<<std::endl;
    //}

    if(pContext!=NULL)
    {
        AbsState  *ppState=new OffState();
        pContext->setState(ppState);
        delete this;
    }
}

void OffState::handle(Context *pContext)
{
    while(newDir == true)
    {
        sleep(1);
    }
    if(pContext!=NULL)
    {
        AbsState  *ppState=new  OnState();
        pContext->setState(ppState);
        delete this;
    }
}


void Context::setState(AbsState *ppState)
{
    pState=ppState;
}

void Context::PressSwitch()
{
    pState->handle(this);
}
