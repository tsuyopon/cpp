#ifndef LOG4CPPDEF_H_
#define LOG4CPPDEF_H_

// log4cpp
#include "log4cpp/Portability.hh"
#ifdef WIN32
//#include 
#endif
//#include 
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/SimpleConfigurator.hh"

// Application Name
#define APPNAME4LOG "APPLICATION_NAME"

//extern log4cpp::Category& logger = log4cpp::Category::getInstance(std::string(APPNAME4LOG));
log4cpp::Category& logger = log4cpp::Category::getInstance(std::string(APPNAME4LOG));

#endif /*LOG4CPPDEF_H_*/
