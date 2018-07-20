> -std=c++11是告诉编译我已c++11的标准进行编译，如果不加这一句编译就会出错，因为编译器到时候为默认的c++98标准编译，编译会不通过因为这里面用到了thread库，这个库只有c++11标准才特有的库，-pthread为编译链接库，不添加这个编译能通过，但运行的时候会报错。

### 运行方式

进入`DataCollectorClient`目录下输入`$ make`，没有提示错误后，在文件夹下会出现一个`DataCollector`的可执行文件

然后`./DataCollector`

之后会提示输出目录名:我的电脑对应的测试目录为: `/Users/xiaorui/Desktop/test `

