#include  "collecter.h"
#include  "collecter.cpp"

int  main()
{
   char Dir[_MAX_DIR_LEN];
   cout<<"������Ŀ¼����·��:"<<endl;
   //gets(Dir);
   cin>>Dir;
   Collecter col=Collecter();
   if(col.setInitDirPath(Dir)==false)
   {
    cout<<"�����ڸ�Ŀ¼������������"<<endl;
   }
   else
   {
     cout<<"Ŀ¼����,����Ϊ�ռ����ļ���Ϣ"<<endl;
     cout<<"-------------------------------------------"<<endl;
     col.GetAllFileInfo(Dir);
     FileInfo fileInfo=col.DateConvert();
     for(int i=0;i<fileInfo.file_number;i++)
     {
        cout<<"�ռ��ĵ�"<<i+1<<"���ļ���Ϣ:"<<endl;
        cout<<"�ļ���--"<<fileInfo.file[i].file_name<<"·��--"<<fileInfo.file[i].file_path<<"�ļ���С--"<<fileInfo.file[i].file_size<<"KB"<<endl;
     }
   }
   return 1;
}
