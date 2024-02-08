#include <iostream>
#include "../webserver/log.h"

int main(int agrc, char** argv){
        webserver::Logger::ptr logger(new webserver::Logger);
	logger->addAppender(webserver::LogAppender::ptr(new webserver::StdoutLogAppender));
	
        webserver::LogEvent::ptr event(new webserver::LogEvent(__FILE__, __LINE__, 0, 1, 2, time(0)));

	logger->log(webserver::LogLevel::DEBUG, event);
	std::cout << "hello webserver log" << std::endl;

	return 0;
}
