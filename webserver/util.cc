#include "util.h"

namespace webserver{

pid_t GetThreadId(){
        return syscall(SYS_gettid);
}

}
