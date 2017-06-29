#include "Logmanager2.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>


namespace df
{
	 LogManager2 *LogManager2::log_manager = NULL;

	LogManager2::LogManager2()
	{
		//std::cout << "enter the LogManger2\n" << std::endl;
		
		//this-> log_manager = 0;

	}	


	LogManager2::~LogManager2()
	{
		//if the file is open ,close it.
	
	}

	LogManager2 &LogManager2::getInstance()   //without static? strange.
	{		
		
		if (!log_manager)
		{
			 log_manager = new LogManager2;
		}
		
		 return *log_manager;
	}
	int LogManager2::startUp( int id)
	{
		std::string file_name = "./logFile/" + std::to_string(id)+".txt";
		p_f = fopen(file_name.c_str(), "w");
		
		
		int user_id = id / 10;
		int session = id % 10;
		fprintf(p_f,"this begin the log manager with user_id:%d, session id:%d\n",user_id,session);
		
		return 1;
	}
	void LogManager2::shutDown()
	{
		
		fprintf(p_f,"this means shutdown the logmanager...\n");
		if (p_f)
			fclose(p_f);

	}
	void LogManager2::setFlush(bool do_flush)   // set the content from memory to disk.
	{
		if (do_flush == true)
		{
			
//			fflush(p_f);   // flush the content into the disk.
			this->do_flush = false;  // set false when it done.
		}

	}
	int LogManager2::writeLog(const char *fmt, ...) const  //means this method do not change the member of class.
	{
		
		fprintf(p_f,"Message:");
		va_list args;
		va_start(args, fmt);
		vfprintf(p_f, fmt, args);
		va_end(args);
		fprintf(p_f, "\n");
		return strlen(fmt);
	}
	int LogManager2::writeLog(int log_level, const char *fmt, ...) const  //almost the same as above
	{
		if (log_level >= LogManager2::log_level)
		{
			
			fprintf(p_f, "Message:");
			va_list args;
			va_start(args, fmt);
			vfprintf(p_f, fmt, args);
			va_end(args);
			//int count = writeLog(fmt);
			//return count;
			fprintf(p_f, "\n");
			return strlen(fmt);
		
		}
		else return -1;

	}
	void LogManager2::setLogLevel(int log_level)
	{
		LogManager2::log_level = log_level;
	}
	int LogManager2::getLogLevel() const
	{
		return LogManager2::log_level;
	}
	/*void LogManager2::setFlush(bool do_flush)
	{
		LogManager2::do_flush = do_flush;
	}*/
	void LogManager2::setLogTimeString(bool log_time_string )
	{
		LogManager2::log_time_string = log_time_string;
	}
	void LogManager2::setLogStepCount(bool log_step_count )
	{
		LogManager2::log_step_count = log_step_count;
	}
	char *LogManager2::getTimeString()
	{
		static char time_str[30];  //why 30?

		time_t now;
		time(&now);
		struct tm *p_time = localtime(&now);

		sprintf(time_str, "%2d:%2d:%2d",
			p_time -> tm_hour,
			p_time -> tm_min,
			p_time -> tm_sec);
		return time_str;
	}
	
}
