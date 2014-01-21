/*
 * Logger.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#include "Logger.h"

namespace schmitt_co {

void Logger::screenInfo() {
	std::cout << "Screen info";
	std::cout << "Window Size: " << glutGet(GLUT_SCREEN_WIDTH) << "x"
			<< glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
	std::cout << "Window Position: " << glutGet(GLUT_WINDOW_X) << "x"
			<< glutGet(GLUT_WINDOW_Y) << std::endl;
	std::cout << "Window ID: " << glutGetWindow() << std::endl;
}

void Logger::printWindTurbine(WindTurbine wt) {
	std::cout << wt << std::endl;
}

void Logger::log(std::list<WindTurbine> l) {
	for_each (l.begin(), l.end(), printWindTurbine);
}

void Logger::log(Camera cam) {
	std::cout << cam << std::endl;
}

} /* namespace schmitt_co */
