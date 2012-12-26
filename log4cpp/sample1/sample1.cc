/*
 * Log4cpp sample program
 * See http://goodjob.boy.jp/chirashinoura/id/94.html
 */
#include "Log4cppDef.h"

int main(){
	log4cpp::SimpleConfigurator::configure("./log4cpp.init1");  // READ CONFIGURATION FILE
	logger.debug("output debug");
	logger.error("output error");
	logger.warn("output warn");
	logger.info("output info");
}
