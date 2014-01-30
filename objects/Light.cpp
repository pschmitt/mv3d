/*
 * Light.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pschmitt
 */

#include "Light.h"

#include <iostream>

namespace schmitt_co {

Light::Light(unsigned int lightId, Position position) {
	mPos = position;
	mLightId = lightId;
	mEnabled = true;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::toggle() {
	mEnabled ? disable() : enable();
}

void Light::enable() {
	mEnabled = true;
}

void Light::disable() {
	mEnabled = false;
}

void Light::lightUp() {
	if (mEnabled) {
		// Don't touch this as it works!
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 65.0 };
		GLfloat light_position[] = { (float) mPos.x(), (float) mPos.y(),
				(float) mPos.z(), 0.0 }; // if last param = 0: directional source
		glClearColor(0.0, 0.0, 0.0, 0.0); // Useless?

		// Set specs
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(mLightId, GL_POSITION, light_position);

		// Enable light
		glEnable(GL_LIGHTING);
		glEnable(mLightId);
		glEnable(GL_DEPTH_TEST);
		// Don't lose colors
		glEnable(GL_COLOR_MATERIAL);
	} else {
		glDisable(GL_LIGHTING);
		glDisable(mLightId);
		glDisable(GL_COLOR_MATERIAL);
	}
}

bool Light::enabled() const {
	return mEnabled;
}

unsigned int Light::lightid() const {
	return mLightId;
}

void Light::set_lightid(unsigned int lightId) {
	mLightId = lightId;
}

const Position& Light::pos() const {
	return mPos;
}

void Light::set_pos(const Position& pos) {
	mPos = pos;
}

std::ostream& operator<<(std::ostream& out, const Light& obj) {
	out << "[Light] ";
	out << "id: ";
	switch (obj.lightid()) {
		case GL_LIGHT0:
			out << "GL_LIGHT0";
			break;
		case GL_LIGHT1:
			out << "GL_LIGHT1";
			break;
		case GL_LIGHT2:
			out << "GL_LIGHT2";
			break;
		case GL_LIGHT3:
			out << "GL_LIGHT3";
			break;
		case GL_LIGHT4:
			out << "GL_LIGHT4";
			break;
		case GL_LIGHT5:
			out << "GL_LIGHT5";
			break;
		case GL_LIGHT6:
			out << "GL_LIGHT6";
			break;
		case GL_LIGHT7:
			out << "GL_LIGHT7";
			break;
	}
	if (obj.enabled()) {
		out << " (on)";
	} else {
		out << " (off)";
	}
	out << " - " << obj.pos();
	return out;
}

} /* namespace schmitt_co */
