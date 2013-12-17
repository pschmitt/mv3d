/*
 * Position.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#include "Position.h"

namespace schmitt_co {

Position::Position(GLdouble x, GLdouble y, GLdouble z) {
	xPos = x;
	yPos = y;
	zPos = z;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& out, const Position& pos) {
	out << "[Position] ";
	out << pos.x() << "-";
	out << pos.y() << "-";
	out << pos.z();
	return out;
}

} /* namespace schmitt_co */
