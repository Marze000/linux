#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE sizeof(fd_set)*8
#define INIT -1
using namespace std;

int StartUp(int port_){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        cerr<<"socket error!"<<endl;
        exit(1);
    }

    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port_);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        cerr<<"bind error!"<<endl;
        exit(2);
    }

    if(listen(sock,5) < 0){
        cerr<<"listen error"<<endl;
        exit(3);
    }
    cout<<"listen sock create sucess"<<endl;
    return sock;
}

void InitFdArray(int fd_array[],int size){
    for(auto i = 0; i < size; ++i){
        fd_array[i] = INIT;
    } 
}

int ArrayFdToSet(int fd_array[],int size , fd_set &rfds){
    int max = fd_array[0];
    for(auto i = 0; i < size; ++i){
        if(fd_array[i] == INIT){
            continue;
        }
        FD_SET(fd_array[i], &rfds);

        if(max < fd_array[i]){
            max = fd_array[i];
        }
    }
    return max;
}

void AddFdToArray(int fd_array[],int &size,const int &sock){
    if(size == SIZE){
        cout<<"socket is full"<<endl;
        close(sock);
    }
    fd_array[size++] = sock;
}

int main(){
    int fd_array[SIZE];
    //合法的描述符个数为0
    int size = 0;
    //初始化数组
    InitFdArray(fd_array,SIZE);
    int listen_sock = StartUp(8888);
    fd_array[size++] = listen_sock;
    for(;;){
        //读文件描述符集
       fd_set rfds;
       FD_ZERO(&rfds);

       int max_fd = ArrayFdToSet(fd_array,size,rfds);
       FD_SET(listen_sock,&rfds);

       //读文件描述符集
       struct timeval timeout = {5,0};

       switch(select(max_fd + 1,&rfds,NULL,NULL,&timeout)){
           case -1:
               cerr<<"select error..."<<endl;
               break;
           case 0:
               cout<<"time out..."<<endl; 
               break;
           default:
               //读的事件已经就绪
               for(auto i = 0; i < size;++i ){
                   int sock = fd_array[i];
                   if(sock < 0){
                       continue;
                   }
                   //检测是否就绪
                   if(FD_ISSET(sock,&rfds)){
                       if(sock == listen_sock){
                           //accept

                           struct sockaddr_in peer;
                           socklen_t len = sizeof(peer);
                           //accept不会阻塞
                           int sock = accept(listen_sock,
                                   (struct sockaddr*)&peer,&len);
                           if(sock < 0){
                               cerr<<"accept error"<<endl;
                               continue;
                           }
                           AddFdToArray(fd_array,size,sock);
                       }else{
                            //read
                            int buffer[10240];
                            ssize_t s = read(sock,buffer,sizeof(buffer));
                            if(s > 0){
                                buffer[s] = 0;
                                cout<<buffer<<endl;
                                std::string response = 
 "HTTP/1.0 200 OK\r\n\r\n<html><h3>hello select server!</h3></html>\r\n";
                                send(sock,response.c_str(),
                                        response.size(),0);
                            }else if(s == 0){

                            }else{

                            }
                       }
                   }
                   break;
               }
       }

    }
    return 0;
}
