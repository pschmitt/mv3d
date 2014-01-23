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

#include "../objects/Camera.h"
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
		static void log(Camera cam);
		static void log(Wind wind);
		//static void logAll();
	private:
		Logger() {};
		Logger(Logger const&);
		static void printWindTurbine(WindTurbine);
};

} /* namespace schmitt_co */

#endif /* LOGGER_H_ */
