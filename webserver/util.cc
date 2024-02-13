#include "util.h"

namespace webserver{

uint32_t GetThreadId(){
        return static_cast<uint32_t>(syscall(SYS_gettid));
}

uint32_t GetFiberId(){
        return 0;
}

}
