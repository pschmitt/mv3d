/*
 * Wind.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include "Wind.h"
#include <GL/glut.h>

namespace schmitt_co {

Wind::Wind(Strength strength, Direction direction) {
	mStrength = strength;
	mDirection = direction;
}

Wind::~Wind() {
	// TODO Auto-generated destructor stub
}

double Wind::glDirection() const {
	switch (mDirection) {
		case NORTH:
			return 0.0;
			break;
		case NORTH_EAST:
			return 45.0;
			break;
		case EAST:
			return 90.0;
			break;
		case SOUTH_EAST:
			return 135.0;
			break;
		case SOUTH:
			return 180.0;
			break;
		case SOUTH_WEST:
			return 225.0;
			break;
		case WEST:
			return 270.0;
			break;
		case NORTH_WEST:
			return 315.0;
			break;
	}
	return 0.0;
}

double Wind::glStrength() const {
	switch (mStrength) {
		case NONE:
			return 0.0;
			break;
		case WEAK:
			return 0.15;
			break;
		case NORMAL:
			return 0.5;
			break;
		case STRONG:
			return 1.0;
			break;
	}
	return 0.0;
}

void Wind::next_direction() {
	switch (mDirection) {
		case NORTH:
			mDirection = NORTH_EAST;
			break;
		case NORTH_EAST:
			mDirection = EAST;
			break;
		case EAST:
			mDirection = SOUTH_EAST;
			break;
		case SOUTH_EAST:
			mDirection = SOUTH;
			break;
		case SOUTH:
			mDirection = SOUTH_WEST;
			break;
		case SOUTH_WEST:
			mDirection = WEST;
			break;
		case WEST:
			mDirection = NORTH_WEST;
			break;
		case NORTH_WEST:
			mDirection = NORTH;
			break;
	}
}

void Wind::next_strength() {
	switch (mStrength) {
		case NONE:
			mStrength = WEAK;
			break;
		case WEAK:
			mStrength = NORMAL;
			break;
		case NORMAL:
			mStrength = STRONG;
			break;
		case STRONG:
			mStrength = NONE;
			break;
	}
}

void Wind::draw() {
	GLUquadric* quad = gluNewQuadric();
	glColor4fv(mColor.color());
	glPushMatrix();
	{
		// Let's start drawing at the wind's position
		glTranslated(mPostion.x(), mPostion.y(), mPostion.z());
		// Scale it properly
		glScalef(mSize, mSize, mSize);
		// TODO: Why isn't the direction working as expected?!
		glRotated(glDirection(), 0, 1, 0);

		switch (mStrength) {
			case NONE:
				glColor4fv(ColorPalette::white().color());
				break;
			case WEAK:
				glColor4fv(ColorPalette::green().color());
				break;
			case NORMAL:
				glColor4fv(ColorPalette::orange().color());
				break;
			case STRONG:
				glColor4fv(ColorPalette::red().color());
				break;
		}
		glPushMatrix();
		{
			gluCylinder(quad, 0.02, 0.02, 0.2, 25, 25);
		}
		glPopMatrix();
		glPushMatrix();
		{
			// Turn around so that we point in the right direction
			glRotated(180, 0, 1, 0);
			glutSolidCone(0.07, 0.15, 25, 25);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

std::ostream& Wind::print(std::ostream& out) const {
	out << "[Wind] ";
	out << "Direction: " << direction();
	out << " Strength: " << strength();
	return out;
}

} /* namespace schmitt_co */
