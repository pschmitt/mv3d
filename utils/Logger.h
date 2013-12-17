/*
 * Logger.h
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <GL/glut.h>
#include <algorithm>
#include <iostream>
#include <list>

#include "../objects/WindTurbine.h"

namespace schmitt_co {

class Logger {
	public:
		static Logger& getInstance() {
			static Logger instance;
			return instance;
		}
		virtual ~Logger();
		static void screenInfo();
		static void log(std::list<WindTurbine>);
		//static void logAll();
	private:
		Logger() {};
		Logger(Logger const&);
		void operator=(Logger const&);
		static void printWindTurbine(WindTurbine);
};

} /* namespace schmitt_co */

#endif /* LOGGER_H_ */
