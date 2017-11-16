 /** 
 * @file thread/thread.h
 * @author luxuan
 * @date 2017/05/24 19:58
 * @brief thread like java api
 *  
 **/
#ifndef THREAD_THREAD_H
#define THREAD_THREAD_H

#include <pthread.h>

class Thread {
public:
    Thread() : 
        _started(false),
        _joined(false),
        _pid(0) { } 

    virtual ~Thread() {
        if (_started && !_joined) {
            pthread_detach(_pid);
        }   
        _started = false;
    }   

    virtual void run() = 0;

    bool start() {
        if (_started) {
            return false;
        }   

        if (pthread_create(&_pid, NULL, run_wrapper, (void*)this)) {
            _started = false;
            return false;
        }   
        _started = true;
        return true;
    }   

    void join() {
        _joined = true;
        if (_pid > 0) {
            pthread_join(_pid, NULL);
        }
    }   

    bool is_started() const {
        return _started;
    }   

    unsigned long pid() const {
        return _pid;
    } 

private:
    static void* run_wrapper(void *obj) {
        ((Thread*) obj)->run();
        return NULL;
    } 

private:
    bool _started;
    bool _joined;

    pthread_t _pid;
};


#endif  // THREAD_THREAD_H
