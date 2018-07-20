//
// Created by root on 18-7-9.
//

#include <iostream>
#include "file_collect.h"
int main()
{
    char dir[200];
    std::cout << "Enter a directory (ends with \'/\'): ";
    std::cin.getline(dir, 200);

//    cout<<strcat(dir,"是傻逼!")<<endl;
//    string name="铜钱";
//    string add = "是傻逼!";
//    cout<<name+add<<endl;
    File_Collect file_temp = File_Collect();
    struct fileInfo file_main = file_temp.listFiles(dir);
    printf("number = %d\n",file_main.file_number);
    for (int i = 0; i < file_main.file_number; ++i) {
        std::cout<<file_main.file[i].file_name<<","<<file_main.file[i].file_path<<","<<file_main.file[i].file_size<<std::endl;
    }

    return 0;
}