// UDP 通用服务器
#pragma once
#include "udp_socket.hpp"
#include <functional>

// C 式写法  typedef void (*Handler)(const std::string& req, std::string* resp);
// C++ 11 式写法, 能够兼容函数指针, 仿函数, 和 lamda
typedef std::function<void (const std::string&, std::string* resp)> Handler;

class UdpServer
{
public:
  UdpServer()
  {
    assert(sock_.Socket());
  }

  ~UdpServer()
  {
    sock_.Close();
  }

  bool Start(const std::string& ip, uint16_t port, Handler handler)
  {
    // 1. 创建 socket
    // 2. 绑定端口号
    bool ret = sock_.Bind(ip, port);
    if (!ret)
    {
      return false;
    }

    // 3. 进入事件循环
    for (;;)
    {
      // 4. 尝试读取请求
      std::string req;
      std::string remote_ip;
      uint16_t remote_port = 0;
      bool ret = sock_.RecvFrom(&req, &remote_ip, &remote_port);
      if (!ret)
      {
        continue;
      }
    
      std::string resp;
      // 5. 根据请求计算响应
      handler(req, &resp);

      // 6. 返回响应给客户端
      sock_.SendTo(resp, remote_ip, remote_port);
      printf("[%s:%d] req: %s, resp: %s\n", remote_ip.c_str(), remote_port,
      req.c_str(), resp.c_str());
    }
    sock_.Close();
    return true;
}

private:
  UdpSocket sock_;
};
