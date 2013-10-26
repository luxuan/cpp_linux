#include <iostream>
#include "url.cc"
#include "page.cc"

using namespace std;
int main() {
	
	Url url("www.ask.com");
	Page pg(url);
	cout << pg.getContent() << endl;
}
