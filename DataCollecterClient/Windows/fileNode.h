
//
// Created by root on 18-7-19.
//

#ifndef INC_0709_FILENODE_H
#define INC_0709_FILENODE_H

struct FileNode
{
    char file_name[128];
    char file_path[1024];
    int file_size;
    int pack_number = 1;
};

struct FileInfo
{
    int file_number = 0;      //fileNode的个数
    struct FileNode* file = NULL;   //所有fileNode
};
#endif //INC_0709_FILENODE_H
