#ifndef __WEBSERVER_CONFIG_H__
#define __WEBSERVER_CONFIG_H__

#include <memory>   //智能指针
#include <sstream>  //序列化
#include <string>
#include <boost/lexical_cast.hpp>  //内存转化
#include "webserver/log.h"

namespace webserver{

class ConfigVarBase{ //定义基类，存放公有的属性
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(const std::string& name, const std::string& description = "")
		:m_name(name)
		,m_description(description){
	}
	virtual ~ConfigVarBase(){}

	const std::string& getName() const {return m_name;}
	const std::string& getDescription() const {return m_description;}

	virtual std::string toString() = 0; //转换成明文
	virtual bool fromString(const std::string& val) = 0;  //解析,初始化
protected:
	std::string m_name;
	std::string m_description;
};

//定义实现类
template<class T>
class ConfigVar : public ConfigVarBase{
public:
	typedef std::shared_ptr<ConfigVar> ptr;

	ConfigVar(const std::string& name
		,const T& default_value
		,const std::string& description = "")
		:ConfigVarBase(name, description)
		,m_val(default_value){
	}

	std::string toString() override{
	        try{
		        return boost::lexical_cast<std::string>(m_val); //类型转换
		} catch(std::exception& e){
		        WEBSERVER_LOG_ERROR(WEBSERVER_LOG_ROOT()) << "ConfigVar::toString exception"
				<< e.what() << "convert:" << typeid(m_val).name() << "to string";
			//返回一个指向异常描述字符串的指针
		}
		return "";
	}

	bool fromString(const std::string& val) override{
	       try{
		       m_val = boost::lexical_cast<T>(val);
	       } catch(std::exception& e){
	               WEBSERVER_LOG_ERROR(WEBSERVER_LOG_ROOT()) << "ConfigVar::toString exception"
                                << e.what() << "convert: string to " << typeid(m_val).name();
	       }
	       return false;
	}

	const T getValue() const {return m_val;}
	void setValue(const T& v){m_val = v;}
private:
	T m_val;
};

class Config{
public:
	typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name, // typename告诉编译器此处为类型，因为有些情况::后 为变量名
			const T& default_value, const std::string& description = ""){
		auto tmp = Lookup<T>(name);
		if(tmp){
		        WEBSERVER_LOG_INFO(WEBSERVER_LOG_ROOT()) << "Lookup name=" << name << " exists";
			return tmp;
		}

		if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._0123456789") 
			!= std::string::npos){
		        WEBSERVER_LOG_ERROR(WEBSERVER_LOG_ROOT()) << "Lookup name invalid " << name;
			throw std::invalid_argument(name);
		}

	        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
		s_datas[name] = v;	
		return v;
	}

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name){
		auto it = s_datas.find(name);
		if(it == s_datas.end()){
		        return nullptr;
		}
		return std::dynamic_pointer_cast<ConfigVar<T> >(it->second); //加空格用来和 >> 区分
	}
private:
	static ConfigVarMap s_datas;
};

}

#endif
