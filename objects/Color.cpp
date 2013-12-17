/*
 * Color.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#include "Color.h"
#include <iostream>

namespace schmitt_co {

Color::Color() {
	rValue = 1.0F;
	gValue = 1.0F;
	bValue = 1.0F;
}

Color::Color(float r, float g, float b) {
	rValue = r;
	gValue = g;
	bValue = b;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}

float Color::b() const {
	return bValue;
}

void Color::set_b(float b) {
	this->bValue = b;
}

float Color::g() const {
	return gValue;
}

void Color::set_g(float g) {
	this->gValue = g;
}

std::string Color::name() const {
	return mName;
}

void Color::set_name(std::string name) {
	mName = name;
}

float Color::r() const {
	return rValue;
}

void Color::set_r(float r) {
	this->rValue = r;
}

const float* Color::color() {
	const float c[] = { rValue, gValue, bValue, 1.0F };
	std::cout << rValue << " " << gValue << " " << bValue << std::endl;
	return c;
}

std::ostream& operator<<(std::ostream& out, const Color& col) {
	out << "[Color] ";
	out << col.r() << "-" << col.g() << "-" << col.b();
	return out;
}

} /* namespace schmitt_co */
