ocket传输
* 状态模式
* 线程同步
---
## 快速开始
* git clone https://github.com/DaytimeSayCopper/DataCollecter.git
* cd DataCollecter/DataCollecterServer/
* cmake ./
* make
* ./main
* 另开一终端,cd DataCollecter/DataCollecterClient/Linux/
* 在switch.cpp中把IP改为localhost在本地测试
* cmake ./
* make
* ./collector
## 目录结构
```
+ DataCollecterClient      //客户端
  |+ Linux
    |-client.cpp            // 主函数
    |-CMakeList.txt
    |-file_collector.h      // 实现数据收集
    |-file_send.cpp
    |-file_send.h           // 实现数据发送
    |-fileNode.h
    |-switch.cpp
    |-switch.h              // 状态模式开关,实现循环发送接收消息切换

  |+ Windows
    |-client.cpp    //客户端主程序
    |-collector.cpp     //数据收集者函数
    |-collector.h       //数据收集者定义
    |-file_send.cpp     //数据发送者函数
    |-file_send.h       //数据发送者定义
    |-fileNode.h        //数据结构体
+ DataCollecterServer     //服务器
  |+src
    |-clientinfo.cpp
    |-clientinfo.h  //内存中所有已连接的客户端的信息
    |-datashow.cpp
    |-datashow.h    //把客户端的信息存到文件中
    |-fileinfo.h    //客户端与服务器连接的接口
    |-findway.h     //用于find_if进行查找
    |-server.cpp
    |-server.h      //服务器与客户端连接,接收数据,发送数据
  |-CMakeList.txt
  |-main.cpp        //主函数
  |-easyclient.cpp  //用于调试服务器
- README.md
```
---
## 时序图
![时序图片]()
## Last

