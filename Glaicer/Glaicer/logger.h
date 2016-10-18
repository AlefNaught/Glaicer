#pragma once

#include <vector>
#include <ostream>
#include <cstdarg>

#define LOGGER_MAX_MSG_LEN 1024

class Logger {
public:
	typedef enum class eSeverity {
		FATAL=0,
		ERR=1,
		WARN=2,
		INFO=3,
		DEBUG=4
	} eSeverity;

	//Logger();
	//~Logger();

	void log(eSeverity severity, const char *msg);
	void logf(eSeverity severity, const char *fmt, ...);

	//Ease of use functions
	inline void fatal(const char *msg) { this->log(Logger::eSeverity::FATAL, msg); }
	inline void fatalf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::FATAL, fmt, args); va_end(args); }
	inline void error(const char *msg) { this->log(Logger::eSeverity::ERR, msg); }
	inline void errorf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::ERR, fmt, args); va_end(args); }
	inline void warn(const char *msg) { this->log(Logger::eSeverity::WARN, msg); }
	inline void warnf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::WARN, fmt, args); va_end(args); }
	inline void info(const char *msg) { this->log(Logger::eSeverity::INFO, msg); }
	inline void infof(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::INFO, fmt, args); va_end(args); }
	inline void debug(const char *msg) { this->log(Logger::eSeverity::DEBUG, msg); }
	inline void debugf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::DEBUG, fmt, args); va_end(args); }

	void addFileStream(FILE *file);
	//void addOStream(std::ostream ostream);

protected:
	const char * severityToStr(eSeverity severity);

	std::vector<FILE *> files;
	//std::vector<std::ostream> ostreams;

};