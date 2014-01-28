/*
 * WindTurbine.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include "WindTurbine.h"

namespace schmitt_co {

WindTurbine::WindTurbine(const Color& color, const Position& pos,
		const Wind& wind) {
	mColor = color;
	mPostion = pos;
	mWind = wind;
}

WindTurbine::~WindTurbine() {
	// TODO Auto-generated destructor stub
}

void WindTurbine::drawBase(GLUquadric*& params) {
	glPushMatrix();
	{
		// glScalef(100 * mSize, 100* mSize, 100*mSize);
		glRotated(90, 1, 0, 0);
		gluCylinder(params, 0.10, 0.15, 2.5, 50, 50);
		glTranslated(0, 0, 2.5);
		glutSolidCube(0.38);
	}
	glPopMatrix();
}

void WindTurbine::drawMotor(GLUquadric*& params) {
	// Rotate motor according to wind direction
	glRotated(mWind.direction(), 0, 1, 0);
	glPushMatrix();
	{
		glTranslated(0, 0, 0.19);
		glutSolidTorus(0.075, 0.075, 15, 15);
		glTranslated(0, 0, -0.53);
		gluCylinder(params, 0.15, 0.15, 0.55, 50, 50);
		glTranslated(0, 0, 0.035);
		glutSolidTorus(0.085, 0.085, 10, 10);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0, 0.28);
		// glutSolidCone(0.1, 0.2, 50, 50);
		glutSolidTorus(0.05, 0.05, 10, 10);
		glTranslated(0, 0, 0.05);
	}
	glPopMatrix();
}

void WindTurbine::drawRotors(GLUquadric*& params) {
	// TODO Move according to wind strength
	// First rotor
	glPushMatrix();
	{
		glRotated(50, 0, 1, 0);
		glTranslated(0.0, 1.5, 0.02);
		glRotated(90, 1, 0, 0);
		glScalef(0.4f, 0.1f, 0.5f);
		gluCylinder(params, 0.0, 0.2, 3, 50, 50);
	}
	glPopMatrix();
	// Second rotor
	glPushMatrix();
	{
		glTranslated(1.4, -0.527, 0.02);
		glRotated(90, 0, 1, 0);
		glRotated(-160, 1, 0, 0);
		glRotated(50, 0, 0, 1);
		glScalef(0.4f, 0.1f, 0.5f);
		gluCylinder(params, 0.0, 0.2, 3, 50, 50);
	}
	glPopMatrix();
	// Third rotor
	glPushMatrix();
	{
		glTranslated(-1.38, -0.62, 0.02);
		glRotated(90, 0, 1, 0);
		glRotated(-25, 1, 0, 0);
		glRotated(50, 0, 0, 1);
		glScalef(0.4f, 0.1f, 0.5f);
		gluCylinder(params, 0.0, 0.2, 3, 50, 50);
	}
	glPopMatrix();
}

void WindTurbine::draw() {
	// http://www.opengl.org/sdk/docs/man2/xhtml/gluNewQuadric.xml
	GLUquadric* params = gluNewQuadric();
	// gluQuadricDrawStyle(params, GLU_FILL);
	// Set drawing color
	glColor4fv(mColor.color());
	glPushMatrix();
	{
		// Let's start drawing at the windmill's position
		glTranslated(mPostion.x(), mPostion.y(), mPostion.z());
		// Scale it properly
		glScalef(mSize, mSize, mSize);
		// Start with the base, then the motor and the rotors
		drawBase(params);
		drawMotor(params);
		double xxx = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * mWind.strength();
				glRotated(xxx, 0, 0, 1);
		drawRotors(params);
	}
	glPopMatrix();
}

const Wind& WindTurbine::wind() const {
	return mWind;
}

void WindTurbine::set_wind(const Wind& wind) {
	mWind = wind;
}

std::ostream& WindTurbine::print(std::ostream& out) const {
	out << "[WindTurbine] ";
	out << "Color: ";
	out << color();
	out << " - " << position();
	out << " - " << wind();
	return out;
}

}/* namespace schmitt_co */

