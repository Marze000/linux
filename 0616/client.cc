//UDP版本的客户端
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main(int argc ,char* argv[]){
    (void)argc;
    (void)argv;
    //1.先创建一个socket 
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        perror("socket");
        return 1;
    }
    //客户端一般不需要绑定(bind)
    //如果不绑定，操作系统随机分配一个端口号
    //2. 准备好服务器sockaddr_in结构
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(9090);
    //3. 客户端直接发送数据即可 
    while(1){
        char buf[1024] = {0};
        printf("请输入一段内容:");
        fflush(stdout);
        scanf("%s",buf);
        sendto(sock,buf,strlen(buf),0,
                (sockaddr*)&server_addr,sizeof(server_addr));
        char buf_output[1024] = {0};
        //NULL 表示不关注对端的地址
        recvfrom(sock,buf_output,sizeof(buf_output)-1,0, NULL,NULL);

        printf("sever resp:%s\n",buf_output);
    }

    return 0;
}
