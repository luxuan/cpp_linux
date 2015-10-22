/* *
 * Date: 2015.10.22
 * */

#include <iostream>  
#include <fstream>  
#include <ctime>
#include <cstdlib>  // srand, rand
using namespace std;  

#define MAX_BIT  23
#define FILENAME "out.txt"

/* *
 * View http://www.cnblogs.com/zhenjing/archive/2012/06/10/c_random.html
 * 1) rand/random性极佳。在64位机器上，其性能大约比简单自增略低30%(32位的自增比64位性能高出1倍以上)！
 * 2) srand/srandom性能极差极差。只有调用rand的1%，没必要每次调用rand之前都调用srand。
 *
 * int rand(void);        return [0, 1 << 31) 
 * long int random(void); return [0, 1 << 63) (64bit system) ?? TODO
 *
 * (((1<<31) - 1000000000) * 10 + 900000000 * 9 + 90000000 * 8 + 9000000 * 7 + 900000 * 6 
 *  + 90000 * 5 + 9000 * 4 + 900 * 3 + 90 * 2 + 10)  * 1.0/ (1<<31) ==  9.482598570175469
 *  9.741299285087734 for unsigned int
 * */
void randomToFile(ofstream &out, int n) {
    unsigned int t;
    int i = 0;
    time_t begin, end;

    // srandom(time(NULL));
    srand(time(NULL));
    cout << sizeof(long int) << " " << sizeof(1L) << endl;

    begin = time(NULL);
    // ~= 1M/s
    while(i++ < n) {
        //out << (random() & 0xFFFFFFFFL) << endl; // not work
        t = rand();
        if(rand() & 1) {
            t |= 0x80000000;
        }
        out << t << endl;
    }
    end = time(NULL);

    cout << "UsedTime:" << (end -begin) << "s, " <<  n / (end -begin) << " /s" << endl;
}

int main() {  
    /* *
     * CPP File: http://blog.csdn.net/lh3325251325/article/details/4761575
     * */
    ofstream out(FILENAME);  
    if(!out){  
        cout << "Unable to open outfile" << endl;  
        return -1;
    }  
    randomToFile(out, 1 << MAX_BIT);

    out.close();  
    return 0;  
}  
