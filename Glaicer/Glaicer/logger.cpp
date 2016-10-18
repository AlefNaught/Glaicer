#include "Logger.h"

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

static const char * severityToStrMap[] = {
	"FATAL",
	"ERROR",
	"WARN",
	"INFO",
	"DEBUG"
};

/*
//declare time to be used in the logger.
namespace Util {
	const std::string CurrentDateTime() {
		time_t now = time(NULL);
		struct tm timeStruct;
		char core[80];
		localtime_s(&timeStruct, &now);
		strftime(core, sizeof(core), "%Y-%m-%d.%X", &timeStruct);
	}
}
*/

void Logger::logs(Logger::eSeverity severity, const char *msg) {
	for (auto file_it = files.begin(); file_it != files.end(); ++file_it) {
		*file_it;
		fprintf(*file_it, "[%s] %s\n", severityToStr(severity), msg);
	}
}

void Logger::logf(Logger::eSeverity severity, const char *fmt, ...) {
	va_list args;
	char msg[LOGGER_MAX_MSG_LEN];

	va_start(args, fmt);
	vsnprintf(msg, LOGGER_MAX_MSG_LEN, fmt, args);
	va_end(args);
	this->logs(severity, msg);
}

void Logger::addFileStream(FILE *file) {
	if (file)
		files.push_back(file);
}

const char * Logger::severityToStr(Logger::eSeverity severity) {
	int severityInt = static_cast<int> (severity);
	int severityIntMin = static_cast<int> (Logger::eSeverity::FATAL);
	int severityIntMax = static_cast<int> (Logger::eSeverity::DEBUG);

	if (severityIntMin <= severityInt && severityInt <= severityIntMax) {
		return severityToStrMap[severityInt];
	}
	else {
		return "????";
	}
}