#ifndef URL_H
#define URL_H
#include <string>
using namespace std;

// only support begin with "http://"
class Url {
	string domain, path;
public:
	Url(const string& url) {
		int ia = extractDomain(url);
		this->path = url.length() == ia ? "/" :  url.substr(ia);
	}
	Url(string url, const string& parent) {
		if(protocolEndIndex(url) > 0) {	// begin with "http://"
			int ia = extractDomain(url);
			this->path = url.length() == ia ? "/" :  url.substr(ia);
		} else if('/' == url.at(0)) {
			extractDomain(parent);
			this->path = url;
		} else {
			int ia = extractDomain(parent);
			int ib = -1;
			string native = "/"; // must end with '/'
			if(parent.length() > ia) {	// erase the end, /path/detail.html -> /path/
				native = parent.substr(ia);
				if((ib = native.rfind('/')) > 0) {
					native = native.substr(0, ib + 1); // end with '/'
				}
			}
			while(url.length() >= 3 && "../" == url.substr(0, 3)) {	// such as ../../path
				url.erase(0, 3);
				if(native.length() > 1 && (ib = native.rfind('/', native.length() - 2)) > 0) {
					native.erase(ib + 1, native.length() - ib);
				}
			}
			if(url.length() >= 2 && "./" == url.substr(0, 2)) {	// such as ./path
				url.erase(0, 2);
			}
			this->path = native + url;	// path begin with no '/', that native end with
		}
	}
 
	string getDomain() {
		return this->domain;
	}
	string getPath() {
		return this->path;
	}
	
	string toString() {
		return this->domain + this->path;
	}

private:
	/* return next usable index after domain */
	int extractDomain(const string& url) {
		int ia = protocolEndIndex(url);
		int ib = url.find('/', ia);
		if(ib > 0) {
			this->domain = url.substr(ia, ib - ia);
			return ib;		// begin with '/'
		} else {
			this->domain = url.substr(ia);
			return url.length();	// end of url
		}		
	}

	/* begin with "http://" */
	int protocolEndIndex(const string& url) {
		const static string httpBegin = "http://";
		const static int length = httpBegin.length();
		return url.substr(0, length) == httpBegin ? length : 0;
	}	
};

#endif
