#include "webserver/webserver.h"
#include <unistd.h>

//不使用namespace防止污染环境

webserver::Logger::ptr g_logger = WEBSERVER_LOG_ROOT();

int count = 0;
webserver::RWMutex s_mutex;

void fun1() {
    WEBSERVER_LOG_INFO(g_logger) << "name: " << webserver::Thread::GetName()
                             << " this.name: " << webserver::Thread::GetThis()->getName()
                             << " id: " << webserver::GetThreadId()
			     << " this.id: " << webserver::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i){
	webserver::RWMutex::WriteLock lock(s_mutex);
        ++count;
    }
}

void fun2(){

}

int main(int argc, char** argv){
    WEBSERVER_LOG_INFO(g_logger) << "thread test begin";
    std::vector<webserver::Thread::ptr> thrs;
    for(int i = 0; i < 5; ++i) {
        webserver::Thread::ptr thr(new webserver::Thread(&fun1, "name_" + std::to_string(i)));
        //sylar::Thread::ptr thr2(new sylar::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        //thrs.push_back(thr2);
    }

    for(int i = 0; i < 5; ++i) {
        thrs[i]->join();
    }
    WEBSERVER_LOG_INFO(g_logger) << "thread test end";
    WEBSERVER_LOG_INFO(g_logger) << "count=" << count;
    return 0;
}
