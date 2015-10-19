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
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define EXIT_ERR(m) do {\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main(void) {
    int listenfd;
    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
      EXIT_ERR("socket");

    //要连接的对方的地址
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9090);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //连接
    if(connect(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
      EXIT_ERR("connect");

    char sendbuf[1024] = {0};
    std::string data;  

    Request req;
    Request::CMD cmd = Request_CMD_SET;
    uint64_t uid = 98989898989;
    //while(1) {
    {
        memset(sendbuf, 0, sizeof(sendbuf));
        req.set_cmd(cmd);
        req.set_uid(uid);
        req.SerializeToString(&data);
        strcpy(sendbuf, data.c_str());
        if(send(listenfd, sendbuf, strlen(sendbuf), 0) <= 0) {
            EXIT_ERR("send");
            //break;
        }
    }
    close(listenfd);
    return 0;
}
