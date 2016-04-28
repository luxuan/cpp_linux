/* *****************************
 * @Date: 2014.10.20
 * @Reference: http://www.cnblogs.com/jaw-crusher/p/3516029.html
 * @Toview: http://blog.chinaunix.net/uid-23069658-id-3283534.html
 *
 * *****************************/
#include "header.h"
#include <string.h>
#include <sys/ioctl.h>

int Open_Raw_Socket(void);
int Set_Promisc(char *interface, int sock);
void dump(const unsigned char*data_buffer, const unsigned int length);

int main() {
    int sock;
    sock = Open_Raw_Socket();
    printf("raw socket is %d\n", sock);

    char buffer[65535];
    
    int bytes_recieved;
    size_t fromlen;
    struct  sockaddr_in from;
    
    struct ip *ip;
    struct tcp *tcp;
    
    // 设置网卡eth0为混杂模式
    Set_Promisc("eth0", sock);
    // 输出TCP/IP报头的长度
    printf("IP header is %d \n", sizeof(struct ip));
    printf("TCP header is %d \n", sizeof(struct tcp));
    
    while (1) {
        fromlen = sizeof(from);
        bytes_recieved = recvfrom(sock, buffer, sizeof(buffer),
                0, (struct sockaddr*)&from, &fromlen);
        
        printf("\nBytes recieved: %5d\n", bytes_recieved);
        printf("Source address: %s\n", inet_ntoa(from.sin_addr));
        
        ip = (struct ip*)buffer;
        if (ip->ip_p == 6) {
            printf("Dest address is: %s\n", inet_ntoa(ip->ip_dst));
            printf("IP header Length is :%d\n", ip->ip_len);
            printf("Protocol: %d\n", ip->ip_p);
            printf("Type of Server: %d\n", ip->ip_tos);
            printf("Time to live is : %d\n",ip->ip_ttl);
            printf("Check Sum is : %d\n", ip->ip_sum);
            tcp = (struct tcp*)(buffer + 20);        // IP数据包和TCP数据包有20个字节的距离
            printf("Dest port is: %d\n", ntohs(tcp->th_dport));
            printf("Source port is: %d\n", ntohs(tcp->th_sport));
            printf("Seq number is : %d\n", tcp->th_seq);
            printf("Ack number is : %d\n", tcp->th_ack);
            printf("Flags is %d\n", tcp->th_flags);
            
            dump((const unsigned char*)buffer, bytes_recieved);
            
        }
    }
    return 0;
    
}


// 建立一个原始socket句柄
int Open_Raw_Socket(void) {
    int sock;
    if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
        perror("raw socket error\n");
        exit(1);
    }
    return sock;
}

// 设置eth0为混杂模式

int Set_Promisc(char *interface, int sock) {
    struct ifreq ifr;
    
    strncpy(ifr.ifr_name, interface, strnlen(interface, sizeof(interface)) + 1);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("set promisc error one if\n");
        exit(2);
    }
    
    printf("The interface is %s\n", interface);
    printf("Retrieved flags from interface is ok\n");
    
    ifr.ifr_flags |= IFF_PROMISC;
    
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("Can not set PROMISC flag:");
        exit(-1);
    }
    
    printf("Set Promisc ok\n");
    
    return 0;
    
    
}

// 输出buffer内容
void dump(const unsigned char*data_buffer, const unsigned int length) {

    unsigned char byte;
    unsigned int i, j;
    
    for (i = 0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if ((i % 16 == 15) || (i == length -1)) {
            for (j = 0; j < 15 -(i % 16); j++) {
                printf("   ");
            }
            printf("|");
            for (j = (i - (i % 16)); j <= i; j++) {
                byte = data_buffer[j];
                if (byte > 31 && byte < 127)
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    
}
