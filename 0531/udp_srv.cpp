/*
udp 服务端程序 udp回显服务器
    1.创建socket                socket()
    2.为socket绑定地址信息      bind()
    3.接受发送数据              sendto() recvfrom()
    4.关闭socket                close()
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
    //创建套接字
    int socketfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socketfd < 0){
        perror("socket create error!");
        return -1;
    }

    //为套接字绑定地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = inet_addr("192.168.122.135");

    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(socketfd,(struct sockaddr*)&addr,len);
    if(ret != 0){
        perror("bind");
        return -1;
    }
    //数据传输
    while(1)
    {
        //接受客户端数据
        struct sockaddr_in cli_addr;
        char buff[1024] = {0};
        recvfrom(socketfd,buff,1023,0,
                (struct sockaddr*)&cli_addr,&len);
        printf("client say:%s\n",buff);

        //向客户端回复数据
        char tmp[1024] = {0};
        printf("you say:");

        scanf("%s",tmp);
        sendto(socketfd,tmp,strlen(tmp),0,(struct sockaddr*)&cli_addr);
    }
    return 0;
}
