
#include <string>
#include "fileNode.h"

#include <winsock2.h>
#pragma  comment(lib,"ws2_32.lib")

#define PORT 5555
class FileSend
{
private:
    struct sockaddr_in address;//��������ͨ�ŵĵ�ַ
public:
    FileSend();
    int getSocket();
    bool getConnect(int sockfd);
    void sendFileInfo(int sockfd, struct FileInfo getFile);
};
