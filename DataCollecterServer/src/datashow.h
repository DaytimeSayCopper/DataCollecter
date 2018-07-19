//
// Created by mylord on 18-7-19.
//

#ifndef DATACOLLECTERSERVER_DATASHOW_H
#define DATACOLLECTERSERVER_DATASHOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileinfo.h"

class DataShow
{
private:
    char log_path[128];
    FILE * file;

public:
    DataShow(const char log_path[]);

    ~DataShow();

    void OpenFile();

    bool AddInfo(struct FileInfo * file_info, char * ip);
};


#endif //DATACOLLECTERSERVER_DATASHOW_H
