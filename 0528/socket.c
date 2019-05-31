/**************************************************************
 *    socket 接口 *
 * ****************

 什么是socket ？ 它是用于两个基于TCP/IP协议的应用程序之间的相互通信
 也叫做 "套接字",它就是一个库函数，里面包含了大量的函数和相应的数据结构
 支持网络通信，程序猿可以了解函数使用方法进行网络编程 
 简单来讲：socket 就是网络应用的程序接口，是应用层到传送层的接口，也就是用户进程与系统内核接口
 以下就是一些接口函数

 创建 socket 文件描述符 (TCP/UDP, 客户端 + 服务器)
 int socket(int domain, int type, int protocol);
 
 绑定端口号 (TCP/UDP, 服务器)
 int bind(int socket, const struct sockaddr *address,socklen_t address_len);

 开始监听socket (TCP, 服务器)
 int listen(int socket, int backlog);
 
 接收请求 (TCP, 服务器)
 int accept(int socket, struct sockaddr* address, socklen_t* address_len);

 建立连接 (TCP, 客户端)
 int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
 **************************************************************** */

/**************************
** 创建 socket 文件描述符  int socket(int domain, int type, int protocol);
***************************  
参数(1)domain：  协议域，又称协议族（family）常用的协议族有AF_INET、AF_INET6、AF_LOCAL
                 或称AF_UNIX，Unix域Socket AF_ROUTE等
                 SOCK_STREAM 流式套接字------提供字节流服务 默认使用的是TCP协议
                 SOCK_DGRAM  数据报套接字----提供数据报传输服务  默认使用的是UDP
                                            

    (2)type：    指定Socket类型。常用的socket类型有 SOCK_STREAM、SOCK_DGRAM、
                 SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等。
       
    (3)protocol：指定协议 常用协议有
                 IPPROTO_TCP、IPPROTO_UDP、IPPROTO_STCP、IPPROTO_TIPC
                 TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议

注意：1.type 和 protocol不可以随意组合，
        如 SOCK_STREAM 不可以跟 IPPROTO_UDP 组合。
        当第三个参数为0时，会自动选择第二个参数类型对应的默认协议。

      2.WindowsSocket下protocol参数中不存在IPPROTO_STCP
　　
返回值：如果调用成功: 返回新创建的套接字的描述符，
        如果失败返回: INVALID_SOCKET（Linux下失败返回-1）
        
套接字描述符是一个整数类型的值。每个进程的进程空间里都有一个套接字描述符表，

该表中存放着(1)套接字描述符
            (2)套接字数据结构的对应关系

因此根据套接字描述符就可以找到其对应的套接字数据结构。

*******************************
* 绑定端口号 (TCP/UDP, 服务器)*
*******************************
函数原型   int bind(SOCKET socket, const struct sockaddr* address, socklen_t address_len);

参数说明：(1)socket：     是一个套接字描述符。
          (2)address：    是一个sockaddr结构指针，该结构中包含了要结合的地址和端口号。
          (3)address_len：确定address缓冲区的长度。
返回值：成功，返回0  否则为 SOCKET_ERROR。

***********
* 接收    *
***********
int recv(SOCKET socket, char FAR* buf, int len, int flags);

参数说明：(1)socket  一个标识已连接套接口的描述字。
          (2)buf     用于接收数据的缓冲区。
          (3)len     缓冲区长度。
          (4)flags   指定调用方式。取值：MSG_PEEK 查看当前数据，
                     数据将被复制到缓冲区中，但并不从输入队列中删除；MSG_OOB 处理带外数据。

返回值：(1)若无错误发生，recv()返回读入的字节数。
        (2)如果连接已中止，返回0。
        (3)否则的话，返回SOCKET_ERROR错误，应用程序可通过WSAGetLastError()获取相应错误代码。

函数原型：
ssize_t recvfrom(int sockfd, void buf, int len, unsigned int flags, 
                  struct socketaddr* from, socket_t* fromlen);
参数说明：
(1)sockfd     标识一个已连接套接口的描述字。
(2)buf        接收数据缓冲区。
(3)len        缓冲区长度。
(4)flags      调用操作方式。是以下一个或者多个标志的组合体，可通过or操作连在一起：
(5)from       （可选）指针，指向装有源地址的缓冲区。
(6)fromlen    （可选）指针，指向from缓冲区长度值。


***************
**发送
***************
    int sendto( SOCKET s, const char FAR* buf, int size, int flags, 
                   const struct sockaddr FAR* to, int tolen );

参数说明：(1)s      套接字
          (2)buf    待发送数据的缓冲区
          (3)size   缓冲区长度
          (4)flags  调用方式标志位, 一般为0, 改变Flags，将会改变Sendto发送的形式
          (5)addr  （可选）指针，指向目的套接字的地址
          (6)tolen  addr所指地址的长度
返回值：成功返回: 发送的字节数
        失败返回；SOCKET_ERROR

***************
* 接收连接请求  int accept( int fd, struct socketaddr* addr, socklen_t* len );
* ************* 
参数说明：(1)fd     套接字描述符。
          (2)addr   返回连接着的地址
          (3)len    接收返回地址的缓冲区长度
返回值：成功返回:   客户端的文件描述符，
        失败返回:   -1
**********************************************************************/
