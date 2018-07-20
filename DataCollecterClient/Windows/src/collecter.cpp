#include "collecter.h"

//���ļ�����Ϣ����ṹ������з���
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

	//ת��Ŀ¼��m_szInitDir�£��ж�Ŀ¼�Ƿ���ڣ���Ŀ¼�����ڷ���0
	if(_chdir(DirPath) != 0)
		return false;
	//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'
	//int len=strlen(DirPath);
	//if (DirPath[len-1] != '\\')
		//strcat(DirPath,"\\");
	    return true;
}
void  Collecter::GetAllFileInfo( const char * DirPath)
{
     _chdir(DirPath);
     _finddata_t fileinfo;
   //���Ȳ���DirPath�з���Ҫ����ļ�
    long  pFile;
    if ((pFile=_findfirst(FILE_FUFFIX,&fileinfo)) != -1)
	{
    do{
        //����DirPath�е���Ŀ¼
    	//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼ΪDirPath��
	    //ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼
	    //��_findnextû��Ӱ��
        if(!(fileinfo.attrib & _A_SUBDIR)&&(fileinfo.size>FILE_MIN_LENGTH))
        {
         //  char filename[_MAX_DIR_LEN];
         //strcpy(filename,DirPath);
         //strcat(filename,fileinfo.name);
         FileNode  *node;
         char Path[_MAX_DIR_LEN];
         strcpy(Path,DirPath);
         //cout<<"·��--"<<DirPath<<"�ļ���--"<<fileinfo.name<<"�ļ���С--"<<fileinfo.size<<"B"<<endl;
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
        //����DirPath�е���Ŀ¼
    	//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼ΪDirPath��
	    //ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼
	    //��_findnextû��Ӱ��
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
