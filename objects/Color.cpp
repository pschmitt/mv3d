/*
 * Color.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#include "Color.h"
#include <iostream>
#include <cstdlib>

namespace schmitt_co {

Color::Color() {
	rValue = 1.0F;
	gValue = 1.0F;
	bValue = 1.0F;
}

Color::Color(std::string n, float r, float g, float b) {
	mName = n;
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
	color(1.0f);
}

const float* Color::color(float alpha) {
	// std::cout << rValue << " " << gValue << " " << bValue << std::endl;
	float *color = (float*) calloc(4, sizeof(float));
	color[0] = rValue;
	color[1] = gValue;
	color[2] = bValue;
	color[3] = alpha;
	return color;
}

std::ostream& operator<<(std::ostream& out, const Color& col) {
	out << "[Color] ";
	out << col.name() << " (";
	out << col.r() << "-" << col.g() << "-" << col.b() << ")";
	return out;
}

} /* namespace schmitt_co */
