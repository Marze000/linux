#include "udp_socket.hpp"

#define CHECK_RET(Q) if((Q) == false){return -1;}

int main(int argc,char* argv[])
{
    (void)argc;(void)argv;
    std::string srv_ip = argv[1];
    uint16_t srv_port = atoi(argv[2]);

    UdpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind(srv_ip,srv_port));
    
    while(1){
        std::string cli_ip;
        uint16_t cli_port;
        std::string buf;
        sock.Recv(buf,cli_ip,cli_port);
        //打印出接受到的字符
        printf("client-[%s:%d]--say:%s\n",
                cli_ip.c_str(),cli_port,buf.c_str());
        buf.clear();
        std::cout<<"server say:"<<std::endl;
        std::cin>>buf;
        sock.Send(buf,cli_ip,cli_port);
    }
    sock.Close();
    return 0;
}
