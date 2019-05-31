#include <stdio.h>
#include <string>
// size_t 类型 malloc free system exit 需要包含该头文件
#include <stdlib.h>
//C++ assert 宏包含在该头文件中
#include <cassert>
//针对系统调用的封装 比如：fork write read close
#include <unistd.h>
// 网络 socket 需要包含该头文件
#include <sys/socket.h>
//socketaddr_in 结构体 htons 系统调用
#include <netinet/in.h>

#include <arpa/inet.h>
using namespace std;

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

class UdpSocket
{
  public:
    UdpSocket() : fd_(-1)
    {

    }

    bool Socket()
    {
      //创建文件描述符
      //参数：协议族  socket类型  自动与第二个类型匹配的协议 
      fd_ = socket(AF_INET, SOCK_DGRAM, 0);
      if (fd_ < 0)
      {
        perror("socket");
        return false;
      }
      return true;
    }

    bool Close()
    {
      //关闭当前进程的 socket id 
      close(fd_);
      return true;
    }

    bool Bind(const std::string& ip, uint16_t port)
    {
      sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip.c_str());
      addr.sin_port = htons(port);
      
      //绑定端口号 参数 套接字描述符 要结合的地址和端口号 前一个缓冲区的长度
      int ret = bind(fd_, (sockaddr*)&addr, sizeof(addr));
      if (ret < 0)
      {
        perror("bind");
        return false;
      }
      return true;
    }
    
    
    bool RecvFrom(std::string* buf, std::string* ip = NULL, uint16_t* port = NULL)
    {
      char tmp[1024 * 10] = {0};
      sockaddr_in peer;
      socklen_t len = sizeof(peer);
      //接受参数
      ssize_t read_size = recvfrom(fd_, tmp,sizeof(tmp) - 1, 0, (sockaddr*)&peer, &len);
      if (read_size < 0)
      {
        perror("recvfrom");
        return false;
      }
        // 将读到的缓冲区内容放到输出参数中
       buf->assign(tmp, read_size);
       if (ip != NULL)
       {
         *ip = inet_ntoa(peer.sin_addr);
       }
       if (port != NULL)
       {
         *port = ntohs(peer.sin_port);
       }
       return true;
    }

     bool SendTo(const std::string& buf, const std::string& ip, uint16_t port)
     {
       sockaddr_in addr;
       addr.sin_family = AF_INET;
        // UDP通用服务器
       addr.sin_addr.s_addr = inet_addr(ip.c_str());
       addr.sin_port = htons(port);
       //发送数据
       ssize_t write_size = sendto(fd_, buf.data(), buf.size(), 0,
                                    (sockaddr*)&addr, sizeof(addr));
       if (write_size < 0)
       {
         perror("sendto");
         return false;
       }
       return true;
     }
  private:
       int fd_;
};
