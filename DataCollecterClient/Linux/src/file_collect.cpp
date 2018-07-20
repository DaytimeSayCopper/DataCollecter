//
// Created by root on 18-7-20.
//
#include "file_collect.h"

struct fileInfo File_Collect::listFiles(const char * dir)
{
    DIR* pDir;
    struct dirent* ptr;
    if( !(pDir = opendir(dir)) )
        return getFile;

    struct fileNode *node;
    while( (ptr = readdir(pDir)) != NULL)         //readdir,成功返回dirent指针,失败返回null
    {
        if(ptr->d_type==DT_DIR)         //如果为子目录,就递归搜索子目录
        {
            if(strcmp(".",ptr->d_name)==0||strcmp("..",ptr->d_name)==0) continue;   //除去目录"."和".."
            else{
                char str[500]="";       //拼接子目录到str
                strcpy(str,dir);
                strcat(str,ptr->d_name);
                strcat(str,"/");
//                    printf("子目录为:%s\n",str);
                listFiles(str);
            }
        }
        else
        {
            int file_fuffix_length = strlen(FILE_FUFFIX);
            if(strlen(ptr->d_name)>file_fuffix_length)
            {

                if(strcmp(FILE_FUFFIX,ptr->d_name+strlen(ptr->d_name)-file_fuffix_length)==0) //判断文件是不是.txt文件
                {
                    FILE *pFile;
                    char temp[500];         //拼接完整文件名到temp
                    strcpy(temp,dir);
                    strcat(temp,ptr->d_name);
//                        cout<<temp<<endl;
                    pFile = fopen(temp,"r");    //计算文件大小
                    fseek(pFile,0,SEEK_END);
                    int size = ftell(pFile);
                    fclose(pFile);

                    if(size>=FILE_MIN_LENGTH)   //如果文件大小大于过滤的大小
                    {
                        getFile.file_number++;

//                            printf("file_index:%d\n",getFile.file_number);
                        node = (struct fileNode*)malloc(sizeof(struct fileNode));
                        if(node==NULL)
                        {
                            printf("not enough memory!\n");
                            exit(1);
                        }
                        strcpy(node->file_name,ptr->d_name);        //赋值文件名
                        strcpy(node->file_path,dir);            //赋值文件路径
                        node->file_size = (int)ceil((double)size/1024); //将大小转换为kb并赋值
//                            std::cout<<node->file_size<<std::endl;
//                            cout<<node->file_name<<","<<node->file_path<<","<<node->file_size<<endl;
                        file_vector.insert(file_vector.end(),*node);    //将node存入vector
                    }

                }
            }
        }
    }
    closedir(pDir);
    //将vector内的元素依次赋值到结构体
    getFile.file = (struct fileNode*)malloc(sizeof(struct fileNode)*getFile.file_number);
    for (int i = 0; i <file_vector.size() ; ++i) {
        getFile.file[i] = file_vector[i];
    }

    return getFile;
}