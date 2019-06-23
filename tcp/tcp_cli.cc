#include "tcp_socket.hpp"

//创建套接字
//向服务器发起连接请求
//while(1){
//发送数据
//接受数据
//}
//关闭套接字

int main(int argc,char* argv[]){
    (void)argc,(void)argv;

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Connect(ip,port));

    while(1){
        std::string buf;
        std::cout<<"client say"<<std::endl;
        std::cin>>buf;
        sock.Send(buf);

        buf.clear();

        sock.Recv(buf);
        std::cout<<"server say:"<<buf<<std::endl;
    }
    return 0;
}
