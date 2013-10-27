#include <iostream>
#include <cstring>
using namespace std;

void get_next(char *patterns, int *nexts) {
    int i = 0, j = -1;
    nexts[0] = -1;
    while(patterns[i] != '\0') {
        if(j == -1 || patterns[i] == patterns[j]) {
            ++i; ++j;
            if(patterns[i] == patterns[j]) {
                nexts[i] = nexts[j];
            } else {
                nexts[i] = j;
            }
        } else {
            j = nexts[j];
        }
    }
}

int index(char *str, char *ptn, int pos) {
    if(pos >= strlen(str)) return -1;
    int *nexts = new int[strlen(ptn)];
    get_next(ptn, nexts);

    int i = pos, j = 0;
    while(str[i] != '\0') {
        if(j == -1 || str[i] == ptn[j]) {
            ++i; ++j;
            if(ptn[j] == '\0') {
                delete[] nexts;
                return i - j;
            }
        } else {
            j = nexts[j];
        }
    }
    delete[] nexts;
    return -1;
}

int index(char *str, char *ptn) {
    return index(str, ptn, 0);
}

void test_get_next() {
    int nexts[100];
    char str0[] = "hello, world!";
    get_next(str0, nexts);
    char str1[] = "aaaab";
    get_next(str1, nexts);
    char str2[] = "abaabcac";
    get_next(str2, nexts);
    char str3[]= "";
}

void test_index() {
    char str0[] = "<a href='http://www.baidu.com/index.html'>baidu</a>";
    char str1[] = "http://";
    char str2[] = "httk";
    char str3[] = "hhttp";
    char ptn[] = "http";
    cout << index(str0, ptn) << endl;
    cout << index(str1, ptn) << endl;
    cout << index(str2, ptn) << endl;
    cout << index(str3, ptn) << endl;

    cout << "\n===============> a4 test <==========" << endl;
    char amul[] = "aaabcaaaaaaabc";
    char aaaab[] = "aaaab";
    cout << index(amul, aaaab) << endl;

    cout << "\n===============> ababa test <==========" << endl;
    char abab[] = "ababcabcacbab";
    char abc[] ="abcac";
    cout << index(abab, abc) << endl;
}
int main(void) {
    test_index();
    return 0;
}
