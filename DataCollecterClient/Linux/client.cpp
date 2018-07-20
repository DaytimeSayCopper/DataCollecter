/*************************************************************************
	> File Name: client.cpp
	> Author: xiaorui
	> Mail: wustxiao@gmail.com
	> Created Time: 2018年07月19日 星期四 14时31分07秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include "file_collect.h"
#include "file_send.h"

pthread_mutex_t mutex;
static sem_t sem_collect;
static sem_t sem_send;

// std::mutex m;
// std::unique_lock<std::mutex> lk(m);

File_Collect file_collector;    // 创建文件收集者临时对象
File_Send file_send("192.168.43.7");       // 创建文件发送者对象

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
    //pthread_mutex_lock(&mutex);
    sem_wait(&sem_send);    // sem_send-1
    std::cout<<"进入sendToServer"<<std::endl;
    file_send.sendFiles(file_collector.getFile,sockfd);
    //pthread_mutex_unlock(&mutex);
    sem_post(&sem_collect); // sem_collect+1
    std::cout<<"sendToServer执行完毕"<<std::endl;
}



int main(void)
{
    // 初始化信号量
    sem_init(&sem_collect, 1, 1);   // 初始收集信号量为1
    sem_init(&sem_send, 1, 0);     // 初始发送信号量为0

    char dir[200];
    std::cout << "Enter a directory (ends with \'/\'): ";
    std::cin.getline(dir, 200);     // 输入目录名
    
    std::cout<<"111111111111111111"<<std::endl;
    if(file_send.ConnectToServer())
    {
        
        pthread_mutex_init(&mutex,NULL);
        std::cout<<"22222222222222222"<<std::endl;
       
        //file_collector.listFiles(dir);
        // 开一个线程收集数据
        

        //std::thread task01(&collectInfo,dir);
        //std::thread task01(&File_Collect::listFiles,&file_collector,dir);
        
        // 开另一个线程发送数据
        int sockfd = file_send.getSockfd();
        // collectInfo(dir);
        // sendToServer(sockfd);
        //file_send.sendFiles(file_collector.getFile,sockfd);
        //std::thread task02(&sendToServer,sockfd);
        //std::thread task02(&File_Send::sendFiles,&file_send,file_collector.getFile,sockfd);
        //task01.detach();
        //task02.detach();
        std::thread task01(&collectInfo,dir);
        std::thread task02(&sendToServer,sockfd);
        task01.join();
        task02.join();

        std::cout<<"整个发送过程结束"<<std::endl;
    }
    return 0;
}
