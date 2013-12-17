/*
 * Object.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: pschmitt
 */

#include "DrawableObject.h"
#include "../utils/ColorPalette.h"

namespace schmitt_co {

DrawableObject::DrawableObject() {
	// TODO Auto-generated constructor stub
}

DrawableObject::~DrawableObject() {
	// TODO Auto-generated destructor stub
}

Position DrawableObject::position() const {
	return mPostion;
}

void DrawableObject::set_position(Position pos) {
	mPostion = pos;
}


void DrawableObject::set_color(Color color) {
	mColor = color;
}

Color DrawableObject::color() const {
	return mColor;
}

} /* namespace schmitt_co */
