#ifndef __WEBSERVER_SINGLETON_H__
#define __WEBSERVER_SINGLETON_H__

namespace webserver{

template<class T, class X = void, int N = 0> //懒汉式单例对象（设计模式）
class Singleton{
public:
	static T* GetInstance(){
	        static T v;
		return &v;
	}
};

template<class T, class X = void, int N = 0>
class SingletonPtr{
public:
        static std::shared_ptr<T> GetInstance(){
                static std::shared_ptr<T> v(new T);;
                return v;
        }
};

}

#endif
