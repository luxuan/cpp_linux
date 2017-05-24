 /** 
 * @file thread/test.cpp
 * @author luxuan
 * @date 2017/05/24 20:39
 * @brief main test 
 *  
 **/

#include "producer.h"

#include <unistd.h>

int main() {

    Producer p1, p2;

    p1.start();
    usleep(500000);
    p2.start();

    p1.join();
    p2.join();

    return 0;
}

