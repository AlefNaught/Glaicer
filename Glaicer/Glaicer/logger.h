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

	void logs(eSeverity severity, const char *msg);
	void logf(eSeverity severity, const char *fmt, ...);

	void addFileStream(FILE *file);

protected:
	const char * severityToStr(eSeverity severity);

	std::vector<FILE *> files;

};