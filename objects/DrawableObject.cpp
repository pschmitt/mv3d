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
	// Default size
	 mSize = 0.1f;
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

float DrawableObject::size() const {
	return mSize;
}

void DrawableObject::set_size(float size) {
	mSize = size;
}

} /* namespace schmitt_co */
