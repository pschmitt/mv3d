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

		glPushMatrix();
		{
			gluCylinder(params, 0.025, 0.025, 0.2, 25, 25);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glRotated(180, 0, 1, 0);
			glutSolidCone(0.05, 0.15, 50, 50);
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
