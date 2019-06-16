//UDP版本的服务器
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main()
{
    // 1.先创建一个socket 
    //   AF_INET是一个宏，表示使用ipv4协议
    //   SOCK_DGRAM表示使用 UDP 协议
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        perror("socket");
        return 1;
    }

    // 2.把当前的socket绑定一个ip + 端口号
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    //ip地址也是一个整数 需要转换为网络字节序
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(9090);//主机转网络序 
    int ret = bind(sock,(sockaddr*)&addr,sizeof(addr));
    if(ret < 0){
        perror("bind");
        return 1;
    }
    printf("server start ok\n");

    //3. 处理服务器(回显服务器)
    //服务器基本工作流程
    //1.初始化(服务器)
    //2.进入一个主循环

    while(true){
        //(a)读取客户端发送来的 “请求”
        sockaddr_in peer;
        socklen_t len = sizeof(peer);//输入输出参数
        char buf[1024]={0};
        ssize_t n = recvfrom(sock,buf,sizeof(buf)-1,0,
                (sockaddr*)&peer,&len);
        if(n < 0){
            perror("recvfrom");
            continue;//考虑到容错
        }
        buf[n] = '\0';
        printf("[%s:%d]buf : %s\n",inet_ntoa(peer.sin_addr),
                ntohs(peer.sin_port),buf); 
        //(b)根据请求内容 计算响应内容
        
        //(c)把响应数据返回给客户端
        n = sendto(sock,buf,strlen(buf),0,
                (sockaddr*)&peer,len);
        if(n < 0){
            perror("sendto");
            continue;
        }
    }
    close(sock);

    return 0;
}
