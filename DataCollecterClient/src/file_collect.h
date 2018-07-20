//
// Created by root on 18-7-19.
//

#ifndef INC_0709_FILE_COLLECT_H
#define INC_0709_FILE_COLLECT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include "fileNode.h"
#define FILE_FUFFIX ".txt"
#define FILE_MIN_LENGTH 1*1024


class File_Collect {
private:
    std::vector<struct fileNode> file_vector;
protected:
    struct fileInfo getFile;
public:

    /*
     * 返回值类型:struct fileInfo
     * 返回值为:  成员变量 getFile
     * */
    struct fileInfo listFiles(const char * dir);
};
#endif //INC_0709_FILE_COLLECT_H
