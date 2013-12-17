/*
 * Wind.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include "Wind.h"
#include <GL/glut.h>

namespace schmitt_co {

Wind::Wind() {
	mStrength = NONE;
	mDirection = NORTH;
}

Wind::~Wind() {
	// TODO Auto-generated destructor stub
}

void Wind::draw() {
	/* fond d'ecran blanc */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(0.0F, 0.0F, 1.0F, 0.0F);
	glRotatef(0.0F, 1.0F, 0.0F, 0.0F);
	/* la couleur du dessin */
	glColor3f(0.0F, 0.0F, 0.0F);
	glutSolidCube(0.4);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

std::ostream& Wind::print(std::ostream& out) const {
	out << "[Wind] ";
	out << "Direction: " << direction();
	out << " Strength: " << strength();
	return out;
}

} /* namespace schmitt_co */
