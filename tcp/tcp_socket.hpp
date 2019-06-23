#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define CHECK_RET(Q) if((Q)==false){return -1;}

class TcpSocket{
    public:
        TcpSocket():_sockfd(-1) {}
        ~TcpSocket(){
        }

        bool  Socket(){
            _sockfd = socket(AF_INET,SOCK_STREAM,0);
            if(_sockfd < 0){
                perror("socket");
                return false;
            }
            return true;
        }

        bool Bind(std::string &ip,uint16_t port){
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            socklen_t len = sizeof(struct sockaddr_in);
            int ret = bind(_sockfd,(struct sockaddr*)&addr,len);
            if(ret < 0){
                perror("bind");
                return false;
            }
            return true;
        }

        bool Listen(int backlog = 5){
            //backlog 代表的是服务端同一时间的并发连接数
            int ret = listen(_sockfd ,backlog);
            if(ret < 0){
                perror("listen");
                return false;
            }
            return true;
        }


        bool Accept(TcpSocket &cli,std::string &cliip,uint16_t port){
            //请求连接客户端地址信息
            struct sockaddr_in addr;
            socklen_t len = sizeof(struct sockaddr_in);

            int newsockfd = accept(_sockfd,(struct sockaddr*)&addr,&len);
            if(newsockfd < 0){
                perror("accept");
                return false;
            }
            cli._sockfd = newsockfd;
            cliip = inet_ntoa(addr.sin_addr);
            port = ntohs(addr.sin_port);
            return true;
        } 

        bool Connect(std::string &srv_ip,uint16_t srv_port){
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(srv_port);
            addr.sin_addr.s_addr = inet_addr(srv_ip.c_str());

            socklen_t len = sizeof(struct sockaddr_in);
            int ret = connect(_sockfd,(struct sockaddr*)&addr,len);
            if(ret < 0 ){
                perror("connect");
                return false;
            }
            return true;
        }

        bool Recv(std::string &buf){
            char tmp[4096];
            int ret = recv(_sockfd,tmp,4096,0);
            if(ret < 0){
                perror("recv");
                return false;
            }else if(ret == 0){
                std::cout<<"peer shutdown"<<std::endl;
                return false;
            }
            buf.assign(tmp,ret);
            return true;
        }

        bool Send(std::string &buf){
            int ret = send(_sockfd,buf.c_str(),buf.size(),0);
            if(ret < 0){
                perror("send");
                return false;
            }
            return true;
        }

        bool Close(){
            close(_sockfd);
            return false;
        }

    private:
        int _sockfd;
};
