//通用的 TCP 服务器
#pragma once

#include <functional>
#include "tcp_socket.hpp"

#define CHECK_RET(ecp) if(!(ecp)){\
    return false;\
}

typedef std::function<void (const std::string&,const std::string*)> Handler;

class TcpServer{
    public:
        TcpServer(){}

        bool Start(const std::string& ip,uint16_t port,Handler handler){
            //1.创建一个socket 
            CHECK_RET(listen_sock_.Socket());
            //2. 绑定端口号
            CHECK_RET(listen_sock_.Bind(ip,port));
            //3. 进行监听,
            CHECK_RET(listen_sock_.Listen()); 
            printf("server satrt ok\n");
            //4.进入主循环  
            
            while(true){
                //5.通过accept获取连接
                TcpSocket client_sock;
                std::string ip;
                uint16_t port;
                bool ret = listen_sock_.Accept(&client_sock,&ip,&port);
                if(!ret){
                    continue;
                }
                printf("[%s:%d]有客户端连接\n",ip.c_str(),port);
                //6.和客户端进行具体沟通
                while(true){
                    //读取请求
                    std::string req;
                    client_sock.Recv(&req);
                    int r = client_sock.Recv(&req);
                    if(r < 0){
                        continue;
                    }
                    if(r == 0){
                        //对端关闭
                        client_sock.Close();
                        printf("[%s:%d]对端关闭了连接\n",ip.c_str(),port);
                        break;
                    }
                    printf("[%s:%d]对客户端发送了%s\n",ip.c_str(),
                            port,req.c_str());
                    // 根据请求计算响应
                    std::string resp;
                    handler(req,&resp);
                    //把响应写会客户端
                    client_sock.Send(resp);
                } 
            }
        }

    private:
        TcpSocket listen_sock_;
};
