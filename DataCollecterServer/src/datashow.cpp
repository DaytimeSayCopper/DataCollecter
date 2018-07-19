//
// Created by mylord on 18-7-19.
//

#include "datashow.h"

DataShow::DataShow(const char log_path[])
{
    strncpy(this->log_path, log_path, 128);
    OpenFile();
}


DataShow::~DataShow()
{
    fclose(file);
    file = NULL;
}


void DataShow::OpenFile()
{
    file = fopen(log_path, "at+");
}


bool DataShow::AddInfo(struct FileInfo * file_info, char ip[])
{
    fprintf(file, "******收到来自%s的数据(共计%d个文件)******\n", ip, file_info->file_number);
    for(int i = 1; i <= file_info->file_number; i++)
    {
        fprintf(file, "Number:%d\n", i);
        if(file_info->file[i - 1].pack_number == -1)
            fprintf(file, "\t此文件信息丢失!\n");
        else
        {
            fprintf(file, "\t文件名:%s\n", file_info->file[i - 1].file_name);
            fprintf(file, "\t文件路径:%s\n", file_info->file[i - 1].file_path);
            fprintf(file, "\t文件大小:%dKB\n", file_info->file[i - 1].file_size);
        }
    }
    fflush(file);
    return true;
}