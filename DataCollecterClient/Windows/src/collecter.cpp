#include "collecter.h"

//将文件的信息存入结构体对象中返回
struct  FileNode *  Collecter::getNode(char * fileName,char *filePath,long int _size)
{
         struct FileNode *fNode=(struct FileNode *)malloc(sizeof(struct FileNode));
         strcpy(fNode->file_name,fileName);
         strcpy(fNode->file_path,filePath);
         fNode->file_size=(int)ceil((double) _size/1024);
         return  fNode;
}

bool  Collecter::setInitDirPath(const char  * DirPath)
{

	//转换目录到m_szInitDir下，判断目录是否存在，若目录不存在返回0
	if(_chdir(DirPath) != 0)
		return false;
	//如果目录的最后一个字母不是'\',则在最后加上一个'\'
	//int len=strlen(DirPath);
	//if (DirPath[len-1] != '\\')
		//strcat(DirPath,"\\");
	    return true;
}
void  Collecter::GetAllFileInfo( const char * DirPath)
{
     _chdir(DirPath);
     _finddata_t fileinfo;
   //首先查找DirPath中符合要求的文件
    long  pFile;
    if ((pFile=_findfirst(FILE_FUFFIX,&fileinfo)) != -1)
	{
    do{
        //查找DirPath中的子目录
    	//当前目录，因此还要重新设置当前目录为DirPath。
	    //执行过_findfirst后，可能系统记录下了相关信息，因此改变目录
	    //对_findnext没有影响
        if(!(fileinfo.attrib & _A_SUBDIR)&&(fileinfo.size>FILE_MIN_LENGTH))
        {
         //  char filename[_MAX_DIR_LEN];
         //strcpy(filename,DirPath);
         //strcat(filename,fileinfo.name);
         FileNode  *node;
         char Path[_MAX_DIR_LEN];
         strcpy(Path,DirPath);
         //cout<<"路径--"<<DirPath<<"文件名--"<<fileinfo.name<<"文件大小--"<<fileinfo.size<<"B"<<endl;
         if((node=getNode(fileinfo.name,Path,fileinfo.size))!=NULL)
         {
             file_vector.insert(file_vector.end(),*node);
             getFile.file_number++;
         }
        }
        }
    while (_findnext(pFile,&fileinfo) == 0);
      _findclose(pFile);
 	}
 	_chdir(DirPath);
    if ((pFile=_findfirst("*.*",&fileinfo)) != -1)
	{
    do{
        //查找DirPath中的子目录
    	//当前目录，因此还要重新设置当前目录为DirPath。
	    //执行过_findfirst后，可能系统记录下了相关信息，因此改变目录
	    //对_findnext没有影响
        if((fileinfo.attrib & _A_SUBDIR))
        {
        if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
        {

        char subDir[_MAX_DIR_LEN];
         strcpy(subDir,DirPath);
         int len=strlen(DirPath);
	     if (DirPath[len-1] != '\\')
		 strcat(subDir,"\\");
         strcat(subDir,fileinfo.name);
         strcat(subDir,"\\");
         GetAllFileInfo(subDir);
        }
        }
     }
    while (_findnext(pFile,&fileinfo) == 0);
      _findclose(pFile);
 	}
}


struct  FileInfo  Collecter::DateConvert()
{
        getFile.file =(struct FileNode*)malloc(sizeof(struct FileNode)*getFile.file_number);
        for (int i = 0; i <file_vector.size() ; ++i)
        {
            getFile.file[i] = file_vector[i];
        }
        return  getFile;
};
