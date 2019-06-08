#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Usage() {
    printf("usage: ./server [ip] [port]\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        Usage();
        return 1;
        //[ip]:[port], 就能看到显示的结果 "Hello World"
    }
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    //ipv4进行通信,稳定的传输协议 ,阻塞
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    //绑定地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    //地址族使用Ipv4
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    //internet 地址也叫IP地址
    addr.sin_port = htons(atoi(argv[2]));
    //端口号是用户输入的第三个参数
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind");
        return 1;
    }

    ret = listen(fd, 10);
    //由主动连接变为被动连接
    //10 代表的是可以达到最大的上限的连接数
    if (ret < 0) {
        perror("listen");
        return 1;
    }
    
    for (;;) {
        struct sockaddr_in client_addr;
        socklen_t len;//相当于int
        int client_fd = accept(fd, (struct sockaddr*)&client_addr, &len);
        //功能：从队列中抽取第一个连接，创建一个新的套接口返回其句柄
        //client_add: 指针--指向一块缓冲区，它的格式是由创建套接字接口提供的地址族确定
        //&len 指针--指向存有len地址长度的整型数
        //返回值：描述所接受包的socket类型的值
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char input_buf[1024 * 10] = {0}; // 用一个足够大的缓冲区直接把数据读完.
        ssize_t read_size = read(client_fd, input_buf, sizeof(input_buf) - 1);
        if (read_size < 0) {
            return 1;
        }

        printf("[Request] %s", input_buf);
        char buf[1024] = {0};
        const char* hello = "<h1>hello world</h1>";
        sprintf(buf, "HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s", strlen(hello), hello);
        write(client_fd, buf, strlen(buf));
    }
    return 0;
}
