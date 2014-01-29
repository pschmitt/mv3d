/*
 * Light.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pschmitt
 */

#include "Light.h"

namespace schmitt_co {

Light::Light() {
	// TODO Auto-generated constructor stub
	
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::draw() {

}

std::ostream& Light::print(std::ostream& out) const {
	out << "[Light] ";
	return out;
}

} /* namespace schmitt_co */
