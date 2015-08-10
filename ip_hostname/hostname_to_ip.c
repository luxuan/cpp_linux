//From: http://my.oschina.net/u/158589/blog/62896
//View: https://en.wikipedia.org/wiki/Getaddrinfo
//View: http://blog.csdn.net/leesphone/article/details/2138775

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool ip_to_hostname(char *ip) {
    struct addrinfo hints;
    struct addrinfo *result, *result_pointer;
    int ret;
    /* obtaining address matching host */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME | AI_NUMERICHOST;
    hints.ai_protocol = 0;  /* any protocol */

    ret = getaddrinfo(ip, NULL, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return false;
    }
    /* traverse the returned list and output the ip addresses */
    for (result_pointer = result; result_pointer != NULL; result_pointer = result_pointer->ai_next) {
        char hostname[1025] = "";
        ret = getnameinfo(result_pointer->ai_addr, result_pointer->ai_addrlen, hostname, sizeof(hostname), NULL, 0, NI_NAMEREQD);
        if (ret != 0) {
            fprintf(stderr, "error in getnameinfo: %s \n", gai_strerror(ret));
        } else {
            printf("hostname: %s \n", hostname);
        }
        //              printf("hostname: %s \n", result_pointer->ai_canonname);                                                                                               
    }
    freeaddrinfo(result);
    return true;
}

bool hostname_to_ip(char *host) {
    struct addrinfo hints;
    struct addrinfo *result, *result_pointer;
    int ret;
    /* obtaining address matching host */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_protocol = 0;  /* any protocol */

    ret = getaddrinfo(host, NULL, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return false;
    }
    /* traverse the returned list and output the ip addresses */
    for (result_pointer = result; result_pointer != NULL; result_pointer = result_pointer->ai_next) {
        char hostname[1025] = "";
        ret = getnameinfo(result_pointer->ai_addr, result_pointer->ai_addrlen, hostname, sizeof(hostname), NULL, 0, NI_NUMERICHOST);
        if (ret != 0) {
            fprintf(stderr, "error in getnameinfo: %s \n", gai_strerror(ret));
            continue;
        } else {
            printf("IP: %s \n", hostname);
        }
    }
    freeaddrinfo(result);
    return true;
}

bool hostname_to_ip1(char *domain) {
    struct hostent *host;
    char **pptr, *p;
    struct timeval begin, end;
    int msec, count;

    gettimeofday(&begin, NULL);
    host = gethostbyname(domain);
    if(!host) {
        printf("gethostbyname error\n" );
        return false;
    }
    gettimeofday(&end, NULL);
    msec = (end.tv_sec - begin.tv_sec) * 1000 
         + (end.tv_usec - begin.tv_usec) / 1000;

    count = 0;
    for(pptr=host->h_addr_list; *pptr!=NULL; pptr++) {
        p = *pptr;
        ++count;
        /* inet_ntop/inet_ntoa: Segmentation fault (core dumped) */
        //printf("addr=%d.%d.%d.%d\n", (unsigned char)p[0], (unsigned char)p[1], (unsigned char)p[2], (unsigned char)p[3]);
    }
    printf("count=%d, time=%d ms\n", count, msec);
    return true;
}

 
int main(int argc, char *argv[]) {
    // for i in {1..10}; do for j in {1..100};do echo "10.23.$i.$j t.domain.com"; done;done > t
    char *host = "t.domain.com";
    printf("host=%s\n", host);
    hostname_to_ip1(host);

    //hostname_to_ip(host);
    //ip_to_hostname(host);
    return 0;
}
