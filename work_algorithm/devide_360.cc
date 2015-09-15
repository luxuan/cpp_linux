/* 
 * 将一个整数做因子分解
*/

#include <iostream>
#include <vector>
using namespace std;


char num[10][5][4] = {{
        " - ",
        "| |",
        "   ",
        "| |",
        " - "
    }, {
        "   ",
        " | ",
        "   ",
        " | ",
        "   "
    }, {
        " - ",
        "  |",
        " - ",
        "|  ",
        " - "
    }, {
        " - ",
        "  |",
        " - ",
        "  |",
        " - "
    }, {
        "   ",
        "| |",
        " - ",
        "  |",
        "   "
    }, {
        " - ",
        "|  ",
        " - ",
        "  |",
        " - "
    }, {
        " - ",
        "|  ",
        " - ",
        "| |",
        " - "
    }, {
        " - ",
        "  |",
        "   ",
        "  |",
        "   "
    }, {
        " - ",
        "| |",
        " - ",
        "| |",
        " - "
    }, {
        " - ",
        "| |",
        " - ",
        "  |",
        " - "
    }
};

char star[5][2] = {
    " ",
    " ",
    "*",
    " ",
    " "
};

#define MAX 1000000
char tstring[MAX]; // care maybe overflow

char* fill_string(char *pstr, int n) {
    int ch;
    do {
        *(pstr--) = n % 10 + '0';
        n /= 10;
    } while(n > 0);
    *(pstr--) = '*';
    return pstr;
}


void print_num(vector<int> *rs) {
    char *p;
    char *pstr = tstring + MAX - 2;
    for(int i = rs->size() - 1; i >= 0; --i) {
        pstr = fill_string(pstr, (*rs)[i]);
    }

    //cout << "pstr=" << ++pstr << endl;

    for(int i = 0; i < 5; ++i) {
        p = pstr + 1;
        while(*++p) {
            if(*p == '*') {
                cout << star[i];
            } else {
                cout << num[*p - '0'][i];
            }
        }
        cout << endl;
    }
}

// from: http://c.biancheng.net/cpp/html/2818.html
vector<int>* devide(int n) {
    vector<int> *rs = new vector<int>;
    for(int i = 2; i <= n; ++i){
        while(n != i){
            if(n % i == 0){
                rs->push_back(i);
                n = n / i;
            } else {
                break;
            }
        }
    }
    rs->push_back(n);
    return rs;
}


int main(){
    int n, di;  // 用户输入的整数
    int i;  // 循环标志

    tstring[MAX - 1] = 0;

    while(cin >> n) {
        vector<int> * rs = devide(n);
        print_num(rs);
        delete rs;
    }

    return 0;
}
