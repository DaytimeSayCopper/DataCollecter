#include  "collecter.h"
#include  "collecter.cpp"

int  main()
{
   char Dir[_MAX_DIR_LEN];
   cout<<"请输入目录所在路径:"<<endl;
   //gets(Dir);
   cin>>Dir;
   Collecter col=Collecter();
   if(col.setInitDirPath(Dir)==false)
   {
    cout<<"不存在该目录，请重新输入"<<endl;
   }
   else
   {
     cout<<"目录存在,以下为收集的文件信息"<<endl;
     cout<<"-------------------------------------------"<<endl;
     col.GetAllFileInfo(Dir);
     FileInfo fileInfo=col.DateConvert();
     for(int i=0;i<fileInfo.file_number;i++)
     {
        cout<<"收集的第"<<i+1<<"个文件信息:"<<endl;
        cout<<"文件名--"<<fileInfo.file[i].file_name<<"路径--"<<fileInfo.file[i].file_path<<"文件大小--"<<fileInfo.file[i].file_size<<"KB"<<endl;
     }
   }
   return 1;
}
