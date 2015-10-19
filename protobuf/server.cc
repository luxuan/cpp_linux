/* *
 * Refer: http://blog.csdn.net/chenkjiang/article/details/12748111
 * Date: 2015.10.19
 * */


#include "request.pb.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define EXIT_ERR(m) do {\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main(void)
{
    Request req;
    int listenfd;
    //监听套接字
    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        EXIT_ERR("socket");
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); //初始化地址，必须要有
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9090);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //允许套接口和一个正在使用的地址捆绑    
    int on = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) <0)
      EXIT_ERR("setsockopt");
    //绑定端口和地址
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
      EXIT_ERR("bind");
    //建立连接套接字
    int conn;
    if(listen(listenfd, SOMAXCONN) < 0)
      EXIT_ERR("listen");
    //对方的地址
    struct sockaddr_in peeraddr;
    //      memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t len = sizeof(peeraddr);
    //接受连接
    if((conn = accept(listenfd, (struct sockaddr*)&peeraddr, &len)) < 0)
      EXIT_ERR("accept");
    close(listenfd);        //接受连接后可以关闭监听套接口
    char recvbuf[1024] = {0};

    while(1) {
        memset(recvbuf, 0, sizeof(recvbuf));
        int ret = recv(conn, recvbuf, 1024, 0);
        if(ret == 0) {
            std::cout<<"client close"<<std::endl;
            break;
        }
        std::string data = recvbuf;
        req.ParseFromString(data);
        std::cout << req.cmd() << " " << req.uid() << std::endl;
    }
    close(conn);
    return 0;
}
