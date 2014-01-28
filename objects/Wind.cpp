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

void Wind::draw() {
	GLUquadric* params = gluNewQuadric();
	glColor4fv(mColor.color());
	glPushMatrix();
	{
		// Let's start drawing at the wind's position
		glTranslated(mPostion.x(), mPostion.y(), mPostion.z());
		// Scale it properly
		glScalef(mSize, mSize, mSize);
		// TODO: Why isn't the direction working as expected?!
		switch (mDirection) {
			case NORTH:
				glRotated(0, 0, 1, 0);
				break;
			case SOUTH:
				glRotated(180, 0, 1, 0);
				break;
			case WEST:
				glRotated(270, 0, 1, 0);
				break;
			case EAST:
				glRotated(360, 0, 1, 0);
				break;
		}

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
			gluCylinder(params, 0.025, 0.025, 0.2, 25, 25);
		}
		glPopMatrix();
		glPushMatrix();
		{
			// Turn around so that we point in the right direction
			glRotated(180, 0, 1, 0);
			glutSolidCone(0.075, 0.15, 30, 30);
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
