#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpSocket{
    public:
        TcpSocket():fd_(-1){}

        bool Socket(){
            fd_ = socket(AF_INET,SOCK_STREAM ,0);
            if(fd_ < 0){
                perror("socket");
                return false;
            }
            return true;
        }

        //给服务器使用
        bool Bind(const std::string& ip,uint16_t port){
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            addr.sin_port = htons(port);
            int ret = bind(fd_,(sockaddr*)&addr,sizeof(addr));
            if(ret < 0){
                perror("bind");
                return false;
            }
            return true;
        }

        //给服务器使用
        bool Listen(){
            // 进入监听状态
            int ret = listen(fd_,10);
            if(ret < 0){
                perror("listen");
                return false;
            }
            return true;
        }

        //给服务器使用
        bool Accept(TcpSocket* peer,std::string* ip,
                uint16_t* port = NULL){
            //从连接队列中取一个连接到用户代码中
            // 如果队列中没有连接会阻塞直到有连接(默认)
            sockaddr_in peer_addr;
            socklen_t len = sizeof(peer_addr);

            //返回值是一个文件描述符 socket
            int client_sock = accept(fd_,(sockaddr*)&peer_addr,&len);
            if(client_sock < 0){
                perror("accpet");
                return false;
            }
            peer->fd_ = client_sock;
            if(ip != NULL){
                *ip = inet_ntoa(peer_addr.sin_addr);
            }
            if(port != NULL){
                *port = ntohs(peer_addr.sin_port);
            }
            return true;
        }

        
        //给服务器和客户端使用
        int Recv(std::string* msg){
            msg->clear();
            char buf[1024*10] = {0};
            ssize_t n = recv(fd_,buf,sizeof(buf)-1,0);
            //如果成功则返回值为读取到字节数
            //如果读取失败 返回结果 -1
            //如果是对端关闭 socket 返回结果 0
            if(n < 0){
                perror("recv");
                return -1;
            }else if(n == 0){
                return 0;
            }else{
                msg->assign(buf);
                return 1;
            }
        }

        //给服务器和客户端使用
        bool Send(const std::string& msg){
            ssize_t n = send(fd_,msg.c_str(),msg.size(),0);
            if(n < 0){
                perror("send");
                return false;
            }
            return true;
        }

        //给客户端使用
        bool Connect(std::string&ip,uint16_t port){
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            addr.sin_port = htons(port);

            int ret = connect(fd_,(sockaddr*)&addr,sizeof(addr));
            if(ret < 0){
                perror("connect");
                return false;
            }
            return true;
        }

        bool Close(){
            if(fd_ != -1){
                close(fd_);
            }
            return true;
        }
    private:
        int fd_;
};
