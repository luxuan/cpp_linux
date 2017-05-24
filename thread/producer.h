 /** 
 * @file thread/producer.h
 * @author luxuan
 * @date 2017/05/24 20:31
 * @brief producer extends thread
 *  
 **/
#ifndef THREAD_PRODUCER
#define THREAD_PRODUCER

#include "thread.h"

#include <unistd.h>
#include <iostream>

class Producer: public Thread  {
    void run() {
        for (int i = 0; ; ++i) {
            std::cout << i << ": " << this->pid()  << std::endl;
            sleep(2);
        }
    }
};

#endif  // THREAD_PRODUCER
