#ifndef PAGE_H
#define PAGE_H

//http://sabolasi.iteye.com/blog/1254092
//http://www.binarytides.com/hostname-to-ip-address-c-sockets-linux/

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<errno.h> //For errno - the error number
#include<netdb.h> //hostent

#include "url.cc"
using namespace std;

class Page {
private:
	Url& url;
	string content;
public:
	Page(Url& _url): url(_url) {
		// split url
		getHtml();
	}
	string& getContent() {
		return this->content;
	}

protected:	
	int getHtml() {
		const char *hostname = url.getDomain().c_str();
		const char *path =  url.getPath().c_str();
		int sfd, res, len;

		sfd = socket(AF_INET, SOCK_STREAM, 0);
		if(-1 == sfd){
			return 2;
		}

		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sockaddr_in));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(80);
		sin.sin_addr.s_addr = getIp(hostname);
		res = connect(sfd, (sockaddr*)&sin, sizeof(sockaddr_in));
		if(-1 == res){
			return 3;
		}
		
		const char *req = getRequestHeader(hostname, path).c_str();
		len = write(sfd, req, strlen(req));
		if(-1 == len){
			return 4;
		}

		char buf[1024];
		while(len = read(sfd, buf, 1024)) {
			buf[len] = 0;
			content += buf;
		}
		return 0;
	}
	
private:
	in_addr_t getIp(string domain) {
		struct hostent *he;
		if ((he = gethostbyname(domain.c_str())) == NULL) {
			herror("gethostbyname");
			return 0;
		}

		struct in_addr **addr_list = (struct in_addr **) he->h_addr_list;
		for(int i = 0; addr_list[i] != NULL; i++) {
			//Return the first one;
			char ip[20];
			strcpy(ip , inet_ntoa(*addr_list[i]));
			return inet_addr(ip);
		}
		return 0;
	}
	
	string getRequestHeader(const char *domain, const char *path, char *charset = "UTF-8") {
	//sprintf(req, "GET %s HTTP/1.1\r\nHost: %s\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-cn,zh;q=0.5\r\nAccept-Encoding: gzip,deflate\r\nAccept-Charset: GB2312,utf-8;q=0.7,*;q=0.7\r\nKeep-Alive: 115\r\nConnection: close\r\n\r\n", path, hostname);
		string header = "";
		header += string("GET ") + path + " HTTP/1.1\r\n";
		header += string("Host: ") + domain + "\r\n";
		header += string("Accept-Charset:") + charset + "\r\n";
		header += string("Connection:Close\r\n");
		header += string("\r\n");
		return header;
	}
};

#endif
