#pragma once

#include "udp_socket.hpp"
#include <assert.h>

//同用的 Udp 服务器类
//1. 读取请求
//2. 根据请求计算响应
//3. 把响应写会客户端

typedef void (*Handler)(const std:: string& req,
        std::string* resp);


class UdpServer{
    public:
        UdpServer(){
            assert(sock_.Socket());
        }

        ~UdpServer(){
            sock_.Close();
        }

        bool Start(const std::string& ip,uint16_t port,Handler handler){
            //1、创建socket
            //2、绑定端口号
            bool ret = sock_.Bind(ip,port);
            if(!ret){
                return false;
            }
            //3、进入一个死循环
            while(true){
                //读取请求 
                std::string req;
                std::string peer_ip;
                uint16_t peer_port;
                sock_.RecvFrom(&req,&peer_ip,&peer_port);
                //计算响应
                std::string resp;
                handler(req,&resp);
                //把响应返回客户端
                sock_.SendTo(resp,peer_ip,peer_port);
            }
            return true;
        }

     private:
       UdpSocket sock_; 
};
