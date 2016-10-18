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

void Logger::log(Logger::eSeverity severity, const char *msg) {
	for (auto file_it = files.begin(); file_it != files.end(); ++file_it) {
		fprintf(*file_it, "[%s] %s\n", severityToStr(severity), msg);
	}
	for (auto ostream_it = ostreams.begin(); ostream_it != ostreams.end(); ++ostream_it) {
		*ostream_it << msg << std::endl;
	}
}

void Logger::logf(Logger::eSeverity severity, const char *fmt, ...) {
	va_list args;
	char msg[LOGGER_MAX_MSG_LEN];

	va_start(args, fmt);
	vsnprintf(msg, LOGGER_MAX_MSG_LEN, fmt, args);
	va_end(args);
	this->log(severity, msg);
}

//Ease of use functions
void Logger::fatal(const char *msg) { this->log(Logger::eSeverity::FATAL, msg); }
void Logger::fatalf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::FATAL, fmt, args); va_end(args); }
void Logger::error(const char *msg) { this->log(Logger::eSeverity::ERROR, msg); }
void Logger::errorf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::ERROR, fmt, args); va_end(args); }
void Logger::warn(const char *msg) { this->log(Logger::eSeverity::WARN, msg); }
void Logger::warnf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::WARN, fmt, args); va_end(args); }
void Logger::info(const char *msg) { this->log(Logger::eSeverity::INFO, msg); }
void Logger::infof(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::INFO, fmt, args); va_end(args); }
void Logger::debug(const char *msg) { this->log(Logger::eSeverity::DEBUG, msg); }
void Logger::debugf(const char *fmt, ...) { va_list args; va_start(args, fmt); this->logf(Logger::eSeverity::DEBUG, fmt, args); va_end(args); }

void Logger::addFileStream(FILE *file) {
	if (file)
		files.push_back(file);
}

void Logger::addOStream(std::ostream ostream) {
	if (ostream.good())
		ostreams.push_back(ostream);
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