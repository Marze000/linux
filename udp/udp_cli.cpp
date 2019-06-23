#include"udp_socket.hpp"
#define CHECK_RET(Q) if((Q)==false){return -1;}

int main(int argc,char* argv[]){
    (void)argc,(void)argv;

    std::string srv_ip = argv[1];
    uint16_t srv_port = atoi(argv[2]);
    UdpSocket sock;
    CHECK_RET(sock.Socket());

    while(1){
        std::string buf;
        std::cout<<"client sayy:"<<std::endl;
        std::cin>>buf;
        sock.Send(buf,srv_ip,srv_port);

        buf.clear();
        sock.Recv(buf,srv_ip,srv_port);
        std::cout<<"server say:"<<buf<<std::endl;
    }
    sock.Close();
    return 0;
}
