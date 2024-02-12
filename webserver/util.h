#ifndef __WEBSERVER_UTIL_H__
#define __WEBSERVER_UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>

namespace webserver{

pid_t GetThreadId();

}

#endif
