//
// Created by mylord on 18-7-19.
//

#ifndef DATACOLLECTERSERVER_FILEINFO_H
#define DATACOLLECTERSERVER_FILEINFO_H

struct FileNode             //收集到的单个文件数据
{
    char file_name[128];
    char file_path[1024];
    int file_size;
    int pack_number = -1;
};

struct FileInfo             //收集到的所有文件数据
{
    int file_number;
    struct FileNode * file = NULL;
};

struct File{
    char file_path[128];
    char buffer[4096];
};

#endif //DATACOLLECTERSERVER_FILEINFO_H
