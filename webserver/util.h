#ifndef __WEBSERVER_UTIL_H__
#define __WEBSERVER_UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

namespace webserver{

uint32_t GetThreadId(); //pid_t
uint32_t GetFiberId();

}

#endif
