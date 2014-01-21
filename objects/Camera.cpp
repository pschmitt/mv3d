/*
 * Camera.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: pschmitt
 */

#include "Camera.h"
#include <math.h>

namespace schmitt_co {

Camera::Camera(Position pos, Position target) {
	mPosition = pos;
	mTarget = target;
	mAngle = 0.0f;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::increase_angle() {
	mAngle += ANGLE_STEPS;
	correct_angle();
	update_position();
	mPosition.set_z(mPosition.z() + 0.01);
}

void Camera::decrease_angle() {
	mAngle -= ANGLE_STEPS;
	correct_angle();
	update_position();
	mPosition.set_z(mPosition.z() - 0.01);
}

float Camera::angle() const {
	return mAngle;
}

void Camera::set_angle(float angle) {
	mAngle = angle;
}

const Position& Camera::position() const {
	return mPosition;
}

void Camera::set_position(const Position& position) {
	mPosition = position;
}

const Position& Camera::target() const {
	return mTarget;
}

void Camera::set_target(const Position& target) {
	mTarget = target;
}

void Camera::correct_angle() {
	// mAngle = fmod(mAngle, 360.0);
	if (mAngle > 360.0){
		mAngle -= 360.0;
	} else if (mAngle < 0.0) {
		mAngle += 360.0;
	}
}

inline double to_degrees(double radians) {
    return radians*(180.0/M_PI);
}

void Camera::update_position() {
	// http://stackoverflow.com/questions/14121377/opengl-rotate-camera-around-center-of-scene
	// x = radius * sin(angle) + zCenterOfScene*
	// z = radius * cos(angle) + zCenterOfScene*
	/*
	mPosition.set_x(10.0 * sin(mAngle) + 10.0);
	mPosition.set_z(-10.0 * cos(mAngle) - 10.0);
	*/
}

void Camera::update() {
	// RTFM: http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
	// Last 3 parameters: Specifies the direction of the up vector.

	gluLookAt(mPosition.x(), mPosition.y(), mPosition.z(), mTarget.x(),
			mTarget.y(), mTarget.z(), 0, 1, 0);
}

std::ostream& operator<<(std::ostream& out, const Camera& cam) {
	out << "[Camera] ";
	out << "Angle: ";
	out << cam.angle();
	out << " - " << cam.position();
	out << " - @" << cam.target();
	return out;
}

} /* namespace schmitt_co */
