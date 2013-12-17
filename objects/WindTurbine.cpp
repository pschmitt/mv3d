/*
 * WindTurbine.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include "WindTurbine.h"

#include <GL/glut.h>

namespace schmitt_co {

WindTurbine::WindTurbine(Color &color, Position &pos) {
	mColor = color;
	mPostion = pos;
}

WindTurbine::~WindTurbine() {
	// TODO Auto-generated destructor stub
}

void WindTurbine::draw() {
	/* fond d'ecran blanc */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(0.0F, 0.0F, 1.0F, 0.0F);
	glRotatef(0.0F, 1.0F, 0.0F, 0.0F);
	/* la couleur du dessin */
	glColor4fv(mColor.color());
	glutWireCube(0.4);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

std::ostream& WindTurbine::print(std::ostream& out) const {
	out << "[WindTurbine] ";
	out << "Color: ";
	out << color();
	out << " - " << position();
	return out;
}

}/* namespace schmitt_co */

