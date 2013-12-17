/*
 * Colors.h
 *
 *  Created on: Dec 17, 2013
 *      Author: pschmitt
 */

#ifndef COLORS_H_
#define COLORS_H_

static GLfloat WHITE[]  = { 1.0F, 1.0F, 1.0F, 1.0F };
static GLfloat BLACK[]  = { 0.0F, 0.0F, 0.0F, 1.0F };
static GLfloat RED[]    = { 1.0F, 0.0F, 0.0F, 1.0F };
static GLfloat GREEN[]  = { 0.0F, 1.0F, 0.0F, 1.0F };
static GLfloat BLUE[]   = { 0.0F, 0.0F, 1.0F, 1.0F };
static GLfloat YELLOW[] = { 1.0F, 1.0F, 1.0F, 1.0F };

float *white() {
	return WHITE;
}

float *black() {
	return BLACK;
}

float *red() {
	return RED;
}

float *green() {
	return GREEN;
}

float *blue() {
	return BLUE;
}

float *yellow() {
	return YELLOW;
}


#endif /* COLORS_H_ */
