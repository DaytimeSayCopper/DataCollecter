//
// Created by root on 18-7-19
//

#ifndef INC_0709_FILE_COLLECT_H
#define INC_0709_FILE_COLLECT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include "fileNode.h"
#define FILE_FUFFIX ".txt"    // 文件后缀
#define FILE_MIN_LENGTH 1



class File_Collect {
protected:
    std::vector<struct fileNode> file_vector;
public:
    struct fileInfo getFile;
    void listFiles(const char * dir)
    {
        getFile.file=NULL;
        getFile.file_number=0;
        file_vector.clear();
        std::cout<<"开始收集信息"<<std::endl;
        DIR* pDir;
        struct dirent* ptr;
        int index=0;
        if( !(pDir = opendir(dir)) )
            return ;

        struct fileNode *node;
        while( (ptr = readdir(pDir)) != 0 )
        {
            if(ptr->d_type==DT_DIR)
            {
                if(strcmp(".",ptr->d_name)==0||strcmp("..",ptr->d_name)==0) continue;
                else{
                    char str[500]="";
                    strcpy(str,dir);
                    strcat(str,ptr->d_name);
                    strcat(str,"/");
                    printf("子目录为:%s\n",str);
                    listFiles(str);
                }
            }
            else
            {
                int file_fuffix_length = strlen(FILE_FUFFIX);
                if(strlen(ptr->d_name)>file_fuffix_length)
                {

                    if(strcmp(FILE_FUFFIX,ptr->d_name+strlen(ptr->d_name)-file_fuffix_length)==0) //文件名是.txt文件
                    {
                        FILE *pFile;
                        char temp[500];
                        strcpy(temp,dir);
                        strcat(temp,ptr->d_name);
                        std::cout<<temp<<std::endl;
                        pFile = fopen(temp,"r");
                        fseek(pFile,0,SEEK_END);
                        int size = ftell(pFile);
                        fclose(pFile);

                        if(size>=FILE_MIN_LENGTH)
                        {
                            getFile.file_number++;
                            std::cout<<"number = "<<getFile.file_number<<std::endl;
                            printf("file_index:%d\n",getFile.file_number);
                            node = (struct fileNode*)malloc(sizeof(struct fileNode));
                            if(node==NULL)
                            {
                                printf("not enough memory!\n");
                                exit(1);
                            }
                            strcpy(node->file_name,ptr->d_name);
                            strcpy(node->file_path,dir);
                            
                            node->file_size = (int)ceil((double)size/1024);
                            std::cout<<"file_size"<<node->file_size<<std::endl;
                            file_vector.insert(file_vector.end(),*node);
                        }

                    }
                }
            }
        }
        
        std::cout<<"vector_size:"<<file_vector.size()<<std::endl;
        getFile.file = (struct fileNode*)malloc(sizeof(struct fileNode)*getFile.file_number);
        
        for (int i = 0; i <file_vector.size() ; ++i) {
            
            getFile.file[i] = file_vector[i];
            std::cout<<"文件名："<<getFile.file[i].file_name<<std::endl;
            std::cout<<"文件路径"<<getFile.file[i].file_path<<std::endl;
        }
        std::cout<<"收集信息完毕"<<std::endl;
        closedir(pDir);
    }
};
#endif //INC_0709_FILE_COLLECT_H
