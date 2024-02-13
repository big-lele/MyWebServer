#include <iostream>
#include "../webserver/log.h"
#include "../webserver/util.h"

int main(int agrc, char** argv){
        webserver::Logger::ptr logger(new webserver::Logger);
	logger->addAppender(webserver::LogAppender::ptr(new webserver::StdoutLogAppender));
	
       // webserver::LogEvent::ptr event(new webserver::LogEvent(__FILE__, __LINE__, 0, webserver::GetThreadId(), webserver::GetFiberId(), time(0)));
	//event->getSS() << "hello zml";
	//logger->log(webserver::LogLevel::DEBUG, event);
	std::cout << "hello webserver log" << std::endl;

	WEBSERVER_LOG_INFO(logger) << "test macro";
	WEBSERVER_LOG_ERROR(logger) << "test macro error";
	return 0;
}
