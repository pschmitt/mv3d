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

void WindTurbine::drawBase(GLUquadric*& quad) {
	glPushMatrix();
	{
		glRotated(90, 1, 0, 0);
		gluCylinder(quad, 0.10, 0.15, 2.5, 60, 60);
		glTranslated(0, 0, 2.5);
		glScalef(4.0 * mSize, 3.0 * mSize, 0.5 * mSize);
		glutSolidCube(0.4);
	}
	glPopMatrix();
}

void WindTurbine::drawMotor(GLUquadric*& quad) {
	// Rotate motor according to wind direction
	glRotated(mWind.glDirection(), 0, 1, 0);

	glPushMatrix();
	{
		glutSolidSphere(0.25, 40, 40);
		glTranslated(0, 0, -0.53);
		gluCylinder(quad, 0.15, 0.25, 0.55, 60, 60);
		glTranslated(0, 0, 0.035);
		// Back of the motor
		glutSolidSphere(0.155, 60, 60);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslated(0, 0, 0.20);
		glutSolidCone(0.12, 0.12, 20, 20);
		glTranslated(0, 0, 0.05);
	}
	glPopMatrix();
}

void WindTurbine::drawRotors(GLUquadric*& quad) {
	glTranslated(0, 0, 0.3);
	glRotated(glutGet(GLUT_ELAPSED_TIME) * mWind.glStrength(), 0, 0, 1);
	// First rotor
	glPushMatrix();
	{
		glRotated(50, 0, 1, 0);
		glTranslated(0, 1.5, 0.02);
		glRotated(90, 1, 0, 0);
		glScaled(0.7, 0.2, 0.5);
		gluCylinder(quad, 0.0, 0.2, 3.0, 75, 75);
	}
	glPopMatrix();
	// Second rotor
	glPushMatrix();
	{
		glTranslated(1.4, -0.6, 0.01);
		// TODO: simplify these 3 successive rotations
		glRotated(90, 0, 1, 0);
		glRotated(-160, 1, 0, 0);
		glRotated(50, 0, 0, 1);
		glScaled(0.7, 0.2, 0.5);
		gluCylinder(quad, 0.0, 0.2, 3.0, 75, 75);
	}
	glPopMatrix();
	// Third rotor
	glPushMatrix();
	{
		glTranslated(-1.4, -0.6, 0.01);
		// TODO: simplify these 3 successive rotations
		glRotated(90, 0, 1, 0);
		glRotated(-25, 1, 0, 0);
		glRotated(50, 0, 0, 1);
		glScaled(0.7, 0.2, 0.5);
		gluCylinder(quad, 0.0, 0.2, 3.0, 75, 75);
	}
	glPopMatrix();
}

void WindTurbine::draw() {
	// http://www.opengl.org/sdk/docs/man2/xhtml/gluNewQuadric.xml
	GLUquadric* quad = gluNewQuadric();
	// Set drawing style
	// gluQuadricDrawStyle(quad, GLU_FILL);
	glPushMatrix();
	{
		// Set drawing color
		glColor4fv(mColor.color());
		// Let's start drawing at the windmill's position
		glTranslated(mPostion.x(), mPostion.y(), mPostion.z());
		// Scale it properly
		glScalef(mSize, mSize, mSize);
		// Start with the base, then the motor and the rotors
		drawBase(quad);
		drawMotor(quad);
		drawRotors(quad);
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

