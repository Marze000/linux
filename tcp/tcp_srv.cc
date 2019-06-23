#include "tcp_socket.hpp"

/*
创建套接字
绑定地址信息
开始监听
while(1){
    获取新建客户端连接socket
    同过新建客户端连接socket 与指定客户端通信recv
    发送数据
    关闭套接字
}*/

int main(int argc,char* argv[]){
    (void)argc,(void)argv;

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind(ip,port));
    CHECK_RET(sock.Listen());

    while(1){
        TcpSocket clisock;
        std::string cliip;
        uint16_t cliport;

        if(sock.Accept(clisock,cliip,cliport) == false){
            continue;
        }
        std::cout<<"new client:"<<cliip<<":"<<cliport<<std::endl;

        std::string buf;
        clisock.Recv(buf);
        std::cout<<"client say:"<<buf<<std::endl;

        buf.clear();
        std::cout<<"server say:"<<std::endl;
        std::cin>>buf;
        clisock.Send(buf);
    }
    
    sock.Close();
    
    return 0;
}
