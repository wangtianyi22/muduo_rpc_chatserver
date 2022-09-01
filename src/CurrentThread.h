#pragma once

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread
{
    extern __thread int t_cachedTid;  // thread_local

    void cacheTid();

    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0))
        {   
            // 获取当前线程的线程id
            cacheTid();
        }
        return t_cachedTid;
    }
}