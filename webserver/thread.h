#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

#include <thread>
#include <functional> //执行方法更灵活
#include <memory>
#include <pthread.h>
#include <string>
#include <semaphore.h>
#include <stdint.h>

//pthread_xxx std的互斥量没有分读写锁，会使性能不好，因为写少读多
//std::thread, pthread  线程是协程的容器
namespace webserver{

class Semaphore{ //信号量
public:
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();
private:
    Semaphore(const Semaphore&) = delete;
    Semaphore(const Semaphore&&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
private:
    sem_t  m_semaphore;
};

//互斥量一般在局部范围 构造函数加锁，析构函数解锁 防止漏掉解锁
//模板锁
template<class T>
struct ScopedLockImpl{
public:
    ScopedLockImpl(T& mutex)
        :m_mutex(mutex){
	m_mutex.lock();
	m_locked = true;
    }

    ~ScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
	    m_mutex.lock();
	    m_locked = true;
	}
    }

    void unlock(){
        if(m_locked){
	    m_mutex.unlock();
	    m_locked = false;
	}
    }
private:
    T& m_mutex;
    bool m_locked;
};

template<class T>
struct ReadScopedLockImpl{
public:
    ReadScopedLockImpl(T& mutex)
        :m_mutex(mutex){
        m_mutex.rdlock();
        m_locked = true;
    }

    ~ReadScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.rdlock();
            m_locked = true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    bool m_locked;
};

template<class T>
struct WriteScopedLockImpl{
public:
    WriteScopedLockImpl(T& mutex)
        :m_mutex(mutex){
        m_mutex.wrlock();
        m_locked = true;
    }

    ~WriteScopedLockImpl(){
        unlock();
    }

    void lock(){
        if(!m_locked){
            m_mutex.wrlock();
            m_locked = true;
        }
    }

    void unlock(){
        if(m_locked){
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    bool m_locked;
};

class RWMutex{
public:
    typedef ReadScopedLockImpl<RWMutex> ReadLock;
    typedef WriteScopedLockImpl<RWMutex> WriteLock;
    
    RWMutex(){
        pthread_rwlock_init(&m_lock, nullptr);
    }

    ~RWMutex(){
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock(){
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock(){
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock(){
        pthread_rwlock_unlock(&m_lock);
    }
private:
    pthread_rwlock_t m_lock;
};

class Thread {
public:
    /// 线程智能指针类型， 减少内存泄露风险
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, const std::string& name); //cd线程执行函数
    ~Thread();

    pid_t getId() const { return m_id;}
    const std::string& getName() const { return m_name;}

    void join(); // 等待线程执行完成

    static Thread* GetThis(); //获取当前的线程指针
    static const std::string& GetName(); //获取当前的线程名称
    static void SetName(const std::string& name); //设置当前线程名称
private:
    Thread(const Thread&) = delete;
    Thread(const Thread&&) = delete; //右值引用
    Thread& operator=(const Thread&) = delete;

    static void* run(void* arg); //线程执行函数
private:
    /// 线程id
    pid_t m_id = -1;
    /// 线程结构
    pthread_t m_thread = 0;
    /// 线程执行函数
    std::function<void()> m_cb;
    /// 线程名称
    std::string m_name;

    Semaphore m_semaphore;
};

}

#endif
