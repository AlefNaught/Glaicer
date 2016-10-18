#pragma once

#include <vector>

#define LOGGER_MAX_MSG_LEN 1024

class Logger {
public:
	typedef enum class eSeverity {
		FATAL=0,
		ERROR=1,
		WARN=2,
		INFO=3,
		DEBUG=4
	} eSeverity;

	//Logger();
	//~Logger();

	void log(eSeverity severity, const char *msg);
	void logf(eSeverity severity, const char *fmt, ...);

	//Ease of use functions
	inline void fatal(const char *msg);
	inline void fatalf(const char *fmt, ...);
	inline void error(const char *msg);
	inline void errorf(const char *fmt, ...);
	inline void warn(const char *msg);
	inline void warnf(const char *fmt, ...);
	inline void info(const char *msg);
	inline void infof(const char *fmt, ...);
	inline void debug(const char *msg);
	inline void debugf(const char *fmt, ...);

	void addFileStream(FILE *file);
	void addOStream(std::ostream ostream);

protected:
	const char * severityToStr(eSeverity severity);

	std::vector<FILE *> files;
	std::vector<std::ostream> ostreams;

};