#include <iostream>
#include "../url.cc"
using namespace std;

void testUrl() {
	string p1[][2] = {
		{"http://www.baidu.com", "www.baidu.com/"},
		{"http://www.baidu.com/path2/path21", "www.baidu.com/path2/path21"},
		{"http://www.baidu.com/path3/path31/hello.html", "www.baidu.com/path3/path31/hello.html"}
	};
	string p2[][3] = {
		{"/path4", "www.baidu.com", "www.baidu.com/path4"},
		{"path5/hello.html", "http://www.baidu.com", "www.baidu.com/path5/hello.html"},
		{"path6/a/hello.html", "http://www.baidu.com/baike/a/b", "www.baidu.com/baike/a/path6/a/hello.html"},
		{"../../hello", "http://www.baidu.com/path7/a/b/c/2.html", "www.baidu.com/path7/a/hello"},
		{"./path8/hello.html", "http://www.baidu.com/a/b/c", "www.baidu.com/a/b/path8/hello.html"},
		{"../hello", "http://www.baidu.com/path9/a/b/c/2.html", "www.baidu.com/path9/a/b/hello"},
		{"http://www.csdn.net/hello", "http://www.baidu.com/path9/a/b/c/2.html", "www.csdn.net/hello"},
		{":///hello", "http://www.baidu.com/path10/a/b/c/2.html", "www.baidu.com/path10/a/b/c/:///hello"},
		{"http/hello", "http://www.baidu.com/path11/a/b/c/2.html", "www.baidu.com/path11/a/b/c/http/hello"},
		{"hello/?src=http://www.cek.edu", "http://www.baidu.com/path12/a/b/c/2.html", "www.baidu.com/path12/a/b/c/hello/?src=http://www.cek.edu"}
	};

	cout << "================= test begin ===================" << endl;
	for(int i = 0; i < 3; ++i) {
		Url url(p1[i][0]);
		if(p1[i][1] != url.toString()) {
			cout << "error: 1 args=" << p1[i][0] << " result=" << url.toString() << endl;
		}
	}
	for(int i = 0; i < 10; ++i) {
		Url url(p2[i][0], p2[i][1]);
		if(p2[i][2] != url.toString()) {
			cout << "error: 2 args=" << p2[i][0] << "," << p2[i][1] << " result=" << url.toString() << endl;
		}
	}
	cout << "================= test end ===================" << endl;
}




int main() {
	testUrl();
}
