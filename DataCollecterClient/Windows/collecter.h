#ifndef INTERFACE_DEFINE_AND_REALIZE
#define INTERFACE_DEFINE_AND_REALIZE
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string>
#include<cstring>
#include <math.h>
#include<io.h>
#include <vector>
#define FILE_FUFFIX "*.txt"
#define _MAX_DIR_LEN   100
#define FILE_MIN_LENGTH 1*1024
#include "fileNode.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using std::cout;
using std::endl;
using std::cin;
//windows下收集数据的类
class Collecter
{
protected:
    struct FileInfo  getFile;
    std::vector<struct FileNode> file_vector;
public:
    bool    setInitDirPath(char * DirPath);
    void    GetAllFileInfo(const char * DirPath);
    void    ClaerFileInfo();
    struct  FileNode*   getNode(char * fileName,char *filePath,long int _size);
    struct  FileInfo    DateConvert();
};
#endif
