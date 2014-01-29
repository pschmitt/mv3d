/*
 * Light.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: pschmitt
 */

#include "Light.h"

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
	//glEnable(mLightid);
}

void Light::disable() {
	mEnabled = false;
	// glDisable(mLightid);
}

void Light::lightUp() {
	if (mEnabled) {

	} else {

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
	this->mPos = pos;
}

} /* namespace schmitt_co */
