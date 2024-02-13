#ifndef __WEBSERVER_LOG_H__ //防止在同一个源文件中多次包含同一个头文件，以避免重复定义和编译错误
#define __WEBSERVER_LOG_H__

#include <string>
#include <stdint.h> //固定宽度的整数类型定义
#include <memory>   //包含智能指针std::shared_ptr
#include <list>
#include <sstream>  //字符串流头文件
#include <fstream>  //文件输入输出流头文件
#include <map>
#include <vector>
#include "singleton.h"

#define WEBSERVER_LOG_LEVEL(logger, level) \
	if(logger->getLevel() <= level) \
	        webserver::LogEventWrap(webserver::LogEvent::ptr(new webserver::LogEvent(logger, level, \
			__FILE__, __LINE__, 0, webserver::GetThreadId(), \
			webserver::GetFiberId(), time(0)))).getSS()

//使用流式方式将日志级别level的日志写入到logger
#define WEBSERVER_LOG_DEBUG(logger) WEBSERVER_LOG_LEVEL(logger, webserver::LogLevel::DEBUG)
#define WEBSERVER_LOG_INFO(logger) WEBSERVER_LOG_LEVEL(logger, webserver::LogLevel::INFO)
#define WEBSERVER_LOG_WARN(logger) WEBSERVER_LOG_LEVEL(logger, webserver::LogLevel::WARN)
#define WEBSERVER_LOG_ERROR(logger) WEBSERVER_LOG_LEVEL(logger, webserver::LogLevel::ERROR)
#define WEBSERVER_LOG_FATAL(logger) WEBSERVER_LOG_LEVEL(logger, webserver::LogLevel::FATAL)

#define WEBSERVER_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        webserver::LogEventWrap(webserver::LogEvent::ptr(new webserver::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, webserver::GetThreadId(),\
                webserver::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

//使用格式化方式将日志级别debug的日志写入到logger
#define WEBSERVER_LOG_FMT_DEBUG(logger, fmt, ...) WEBSERVER_LOG_FMT_LEVEL(logger, webserver::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define WEBSERVER_LOG_FMT_INFO(logger, fmt, ...)  WEBSERVER_LOG_FMT_LEVEL(logger, webserver::LogLevel::INFO, fmt, __VA_ARGS__)
#define WEBSERVER_LOG_FMT_WARN(logger, fmt, ...)  WEBSERVER_LOG_FMT_LEVEL(logger, webserver::LogLevel::WARN, fmt, __VA_ARGS__)
#define WEBSERVER_LOG_FMT_ERROR(logger, fmt, ...) WEBSERVER_LOG_FMT_LEVEL(logger, webserver::LogLevel::ERROR, fmt, __VA_ARGS__)
#define WEBSERVER_LOG_FMT_FATAL(logger, fmt, ...) WEBSERVER_LOG_FMT_LEVEL(logger, webserver::LogLevel::FATAL, fmt, __VA_ARGS__)


namespace webserver{

class Logger;

//日志级别
class LogLevel{
public:
        enum Level{
                UNKNOW = 0,
                DEBUG = 1, //用于记录详细的调试信息
                INFO = 2,  //用于记录一般性的信息性消息
                WARN = 3,  //用于记录潜在的问题或警告
                ERROR = 4, //用于记录可恢复的错误或异常
                FATAL = 5  //用于记录严重的错误，导致应用程序无法继续执行
        };

        static const char* ToString(LogLevel::Level level);
};

//日志事件
class LogEvent{
public:
	typedef std::shared_ptr<LogEvent> ptr;  //别名
	LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
		, const char* file, int32_t line, uint32_t elapse
		, uint32_t thread_id, uint32_t fiber_id, uint64_t time);

	const char* getFile() const {return m_file;}
	int32_t getLine() const {return m_line;}
	uint32_t getElapse() const {return m_elapse;}
	uint32_t getThreadId() const {return m_threadId;}
	uint32_t getFiberId() const {return m_fiberId;}
	uint64_t getTime() const {return m_time;}
	std::string getContent() const{return m_ss.str();}
	std::shared_ptr<Logger> getLogger() const{return m_logger;}
	LogLevel::Level getLevel() const{return m_level;}

	std::stringstream& getSS(){return m_ss;}
	void format(const char* fmt, ...);
	void format(const char* fmt, va_list al);
private:                               //考虑内存对齐
	const char* m_file = nullptr;  //文件名
        int32_t m_line = 0;	       //行号
	uint32_t m_elapse = 0;	       //程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;       //线程id
	uint32_t m_fiberId = 0;	       //协程id
	uint64_t m_time = 0;           //时间戳
	std::stringstream m_ss;	       

	std::shared_ptr<Logger> m_logger;
	LogLevel::Level m_level;
};

class LogEventWrap{
public:
	LogEventWrap(LogEvent::ptr e);
	~LogEventWrap();
	LogEvent::ptr getEvent() const { return m_event;}
	std::stringstream& getSS();
private:
	LogEvent::ptr m_event;
};

//日志格式器
class LogFormatter{
public:
	typedef std::shared_ptr<LogFormatter> ptr;
        LogFormatter(const std::string& pattern);

	std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
	class FormatItem{
	public:
		typedef std::shared_ptr<FormatItem> ptr;
		virtual ~FormatItem(){}
         	virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0; //不输出string，因为需要组合，这样的性能更好
	};

	void init(); //做pattern的解析
private:
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;
};

//日志输出地 将日志消息输出到指定的目标
class LogAppender{
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender(){}   //虚析构函数是为了确保在继承关系中正确释放资源
				   
 	virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0; //纯虚函数，则子类必须实现该方法，使基类成为抽象类
									  //抽象类是一种不能被实例化的类，它的存在主要用于作为其他类的基类或接口，并为派生类提供一种共享的接口和行为规范
        void setFormatter(LogFormatter::ptr val){ m_formatter = val;}
	LogFormatter::ptr getFormatter() const {return m_formatter;}

	LogLevel::Level getLevel() const {return m_level;}
	void setLevel(LogLevel::Level val){m_level = val;}
protected:  //可以被派生类访问
	LogLevel::Level m_level;
	LogFormatter::ptr m_formatter;
};

//日志器 记录和管理日志消息
class Logger : public std::enable_shared_from_this<Logger>{
public:
	typedef std::shared_ptr<Logger> ptr;

	Logger(const std::string& name = "root");
	void log(LogLevel::Level level, LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);

	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	LogLevel::Level getLevel() const { return m_level; }  //获取日志级别
	void setLevel(LogLevel::Level val) { m_level = val; } //设置日志级别

	const std::string& getName() const{return m_name;}
private:
	std::string m_name;                       //日志名称
	LogLevel::Level m_level;                  //日志级别
        std::list<LogAppender::ptr> m_appenders;  //Appender是个列表集合
	LogFormatter::ptr m_formatter;
};

//输出到控制台的Appender
class StdoutLogAppender: public LogAppender{
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override; //关键字，用于显式地标记派生类中的成员函数，以表示它们是对基类中的虚函数进行重写（覆盖）的
};

//输出到文件的Appender
class FileLogAppender: public LogAppender{
public:
	typedef std::shared_ptr<FileLogAppender> ptr;
	FileLogAppender(const std::string& filename);
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

	bool reopen();  //重新打开文件
private:
	std::string m_filename;
	std::ofstream m_filestream;
};

class LoggerManager{
public:
	LoggerManager();
	Logger::ptr getLogger(const std::string& name);

	void init();
private:
	std::map<std::string, Logger::ptr> m_loggers;
	Logger::ptr m_root;
};

typedef webserver::Singleton<LoggerManager> LoggerMgr;

}

#endif
