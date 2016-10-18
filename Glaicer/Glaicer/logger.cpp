#include <iostream>
#include "VulkanSurface.h"
#include <fstream>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

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




class sevLogger {


public:
	enum eSeverity {
		FATAL,
		ERR,
		WARN,
		INFO,
		DEBUG
	};
	
	void Glacier_Logger(eSeverity, string *filename, int linenum, char *format) {


	}

};
