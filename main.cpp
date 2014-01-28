/*
 * main.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <list>
#include <algorithm>

#include "constants/DefaultConstants.h"
#include "constants/MenuConstants.h"
#include "constants/WindowConstants.h"

#include "utils/Logger.h"
#include "utils/ColorPalette.h"
#include "objects/DrawableObject.h"
#include "objects/Camera.h"
#include "objects/Wind.h"
#include "objects/WindTurbine.h"

// debug mode
#define DEBUG 1

using namespace schmitt_co;

bool mMousePressed = false;
int mLastX = -1;
int mLastY = -1;
int mCurrentX = -1;
int mCurrentY = -1;

/** Runtime options **/

bool mOptionAutoPilot = false;
bool mOptionAutoPilotReverse = false;
bool mPreserveOriginalWindMillColors = true;

/** End of runtime options **/

/** Object initialization **/

Wind mWind = Wind();
// Default color (white) // TODO: respect different object colors (windmills)
Color mColor = ColorPalette::white();
Camera mCam = Camera(Position(0.0F, 0.0f, -0.2f), Position(0.0f, 0.0f, 0.0f));
std::list<WindTurbine> mWindTurbineList;

/** End of object initialization **/


/** Function declarations **/

void draw_object(DrawableObject& obj);
void display();
void idle();
void reshape(int width, int height);
void zoomin(WindTurbine& wt);
void zoomout(WindTurbine& wt);
void zoom(bool zoomIn);
void mousePress(int button, int state, int x, int y);
void motionFunc(int x, int y);
void keyPress(unsigned char key, int x, int y);
void specialKeyPress(int key, int x, int y);
void updateWindTurbine(WindTurbine& wt);
void menuSelect(int selection);
void setupMouse();
void setupKeyboard();
void setupMenu();
void debugInfo();
void setupWindow();

/** End of function declaration **/

/** Display functions **/

void draw_object(DrawableObject& obj) {
	std::cout << "Drawing object " << obj << std::endl;
	obj.draw();
}

void display() {
	// Clear
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw
	glPushMatrix();
	{
		glLoadIdentity(); // Start from origin
		mCam.update();
		Logger::log(mCam);
		mWind.draw();
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(), draw_object);
	}
	glPopMatrix();

	// http://www.delafond.org/traducmanfr/X11/man3/glFlush.3x.html
	// glFlush(); // ?
	glutSwapBuffers(); // swap buffers, otherwise we won't see anything
}

void idle() {
	if (mOptionAutoPilot) {
		if (mOptionAutoPilotReverse) {
			mCam.decrease_angle();
		} else {
			mCam.increase_angle();
		}
		glutPostRedisplay();
	}
}

void reshape(int width, int height) {
	// TODO
}

/** End of display functions **/


/**
 * Updates a single wind turbine
 */
void updateWindTurbine(WindTurbine& wt) {
	wt.set_wind(mWind);
	if (!mPreserveOriginalWindMillColors) {
		wt.set_color(mColor);
	}
}

/**
 * Update all windturbines in our list to reflect user choices
 */
void updateWindTurbines() {
	for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
			updateWindTurbine);
}

/** Mouse functions **/

void zoomin(WindTurbine& wt) {
	wt.set_size(wt.size() + 0.1);
	glutPostRedisplay();
}

void zoomout(WindTurbine& wt) {
	float current_size = wt.size();
	if (current_size - 0.1 > 0.1) {
		wt.set_size(wt.size() - 0.1);
		glutPostRedisplay();
	}
}

/**
 * Zoom function
 * TODO Don't just increase object size (is gluLookAt a better solution?)
 * TODO Reset function
 */
void zoom(bool zoomIn) {
	if (zoomIn) {
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					zoomin);
		mWind.set_size(mWind.size() + 0.1);
	} else {
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
							zoomout);
		float current_size = mWind.size();
		if (current_size - 0.1 > 0.1) {
			mWind.set_size(mWind.size() - 0.1);
		}
	}
}

/*// FreeGLUT only
void mouseWheel(int wheel, int direction, int x, int y) {}
*/

void mousePress(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				mMousePressed = true;
				mLastX = x;
				mLastY = y;
			} else if (state == GLUT_UP) {
				mMousePressed = false;
				mLastX = mLastY = -1;
				// TODO update cam ?
				// mCam.set_angle(  * 0.01f)
			}
			break;
			// http://stackoverflow.com/a/7885789
		case 3:
		case 4:
			// Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
			if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
			// Scroll event
			zoom(button == 3);
			break;
	}
}

void motionFunc(int x, int y) {
// std::cout << "x: " << x << "y: " << y << std::endl;
	if (x < mLastX) {
		mCam.decrease_angle();
	} else {
		mCam.increase_angle();
	}
	mLastX = x;
	mLastY = y;
	glutPostRedisplay();
}
void setupMouse() {
	glutMouseFunc(mousePress);
	glutMotionFunc(motionFunc);
// FreeGLUT only...
// glutMouseWheelFunc(mouseWheel);
}

/** End of mouse functions **/

/** Keyboard functions **/

void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
			mOptionAutoPilot = !mOptionAutoPilot;
			break;
		case 'A':
			mOptionAutoPilot = true;
			mOptionAutoPilotReverse = !mOptionAutoPilotReverse;
			break;
		case 's':
			mWind.next_strength();
			updateWindTurbines();
			glutPostRedisplay();
			break;
		case 'd':
			mWind.next_direction();
			updateWindTurbines();
			glutPostRedisplay();
			break;
		case 32: // SPACE
			mOptionAutoPilot = !mOptionAutoPilot;
			break;
		case 'q':
		case 27: // ESC
			exit(0);
			break;
	}
}

void specialKeyPress(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			mCam.increase_angle();
			break;
		case GLUT_KEY_RIGHT:
			mCam.decrease_angle();
			break;
	}
	glutPostRedisplay();
}

void setupKeyboard() {
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
}

/** End of keyboard functions **/

/** Menu functions **/

void menuSelect(int selection) {
	switch (selection) {
		case MENU_QUIT_ID:
			exit(0);
			break;
		case MENU_WIND_NORTH_ID:
			mWind.set_direction(Wind::NORTH);
			break;
		case MENU_WIND_SOUTH_ID:
			mWind.set_direction(Wind::SOUTH);
			break;
		case MENU_WIND_WEST_ID:
			mWind.set_direction(Wind::WEST);
			break;
		case MENU_WIND_EAST_ID:
			mWind.set_direction(Wind::EAST);
			break;
		case MENU_WIND_NONE_ID:
			mWind.set_strength(Wind::NONE);
			break;
		case MENU_WIND_WEAK_ID:
			mWind.set_strength(Wind::WEAK);
			break;
		case MENU_WIND_NORMAL_ID:
			mWind.set_strength(Wind::NORMAL);
			break;
		case MENU_WIND_STRONG_ID:
			mWind.set_strength(Wind::STRONG);
			break;
		case MENU_COLOR_RED_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::red();
			break;
		case MENU_COLOR_GREEN_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::green();
			break;
		case MENU_COLOR_BLUE_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::blue();
			break;
		case MENU_COLOR_YELLOW_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::yellow();
			break;
		case MENU_COLOR_WHITE_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::white();
			break;
		case MENU_COLOR_BLACK_ID:
			mPreserveOriginalWindMillColors = false;
			mColor = ColorPalette::black();
			break;
		case MENU_AUTO_PILOT_ID:
			mOptionAutoPilot = !mOptionAutoPilot;
			break;

	}
	updateWindTurbines();
	glutPostRedisplay();
}

void setupMenu() {
// Wind direction
	int windDirMenu = glutCreateMenu(menuSelect);
	glutAddMenuEntry(MENU_WIND_NORTH, MENU_WIND_NORTH_ID);
	glutAddMenuEntry(MENU_WIND_NORTH_EAST, MENU_WIND_NORTH_EAST_ID);
	glutAddMenuEntry(MENU_WIND_EAST, MENU_WIND_EAST_ID);
	glutAddMenuEntry(MENU_WIND_SOUTH_EAST, MENU_WIND_SOUTH_EAST_ID);
	glutAddMenuEntry(MENU_WIND_SOUTH, MENU_WIND_SOUTH_ID);
	glutAddMenuEntry(MENU_WIND_SOUTH_WEST, MENU_WIND_SOUTH_WEST_ID);
	glutAddMenuEntry(MENU_WIND_WEST, MENU_WIND_WEST_ID);
	glutAddMenuEntry(MENU_WIND_NORTH_WEST, MENU_WIND_NORTH_WEST_ID);
	glutAddMenuEntry(MENU_WIND_WEST, MENU_WIND_WEST_ID);
// Wind strength
	int windStrMenu = glutCreateMenu(menuSelect);
	glutAddMenuEntry(MENU_WIND_NONE, MENU_WIND_NONE_ID);
	glutAddMenuEntry(MENU_WIND_WEAK, MENU_WIND_WEAK_ID);
	glutAddMenuEntry(MENU_WIND_NORMAL, MENU_WIND_NORMAL_ID);
	glutAddMenuEntry(MENU_WIND_STRONG, MENU_WIND_STRONG_ID);
// Colors
	int colorMenu = glutCreateMenu(menuSelect);
	glutAddMenuEntry(MENU_COLOR_RED, MENU_COLOR_RED_ID);
	glutAddMenuEntry(MENU_COLOR_GREEN, MENU_COLOR_GREEN_ID);
	glutAddMenuEntry(MENU_COLOR_BLUE, MENU_COLOR_BLUE_ID);
	glutAddMenuEntry(MENU_COLOR_YELLOW, MENU_COLOR_YELLOW_ID);
	glutAddMenuEntry(MENU_COLOR_WHITE, MENU_COLOR_WHITE_ID);
	glutAddMenuEntry(MENU_COLOR_BLACK, MENU_COLOR_BLACK_ID);
// Main menu
	glutCreateMenu(menuSelect);
	glutAddSubMenu(MENU_COLOR, colorMenu);
	glutAddSubMenu(MENU_WIND_STR, windStrMenu);
	glutAddSubMenu(MENU_WIND_DIR, windDirMenu);
// Auto pilot & quit
	glutAddMenuEntry(MENU_AUTO_PILOT, MENU_AUTO_PILOT_ID);
	glutAddMenuEntry(MENU_QUIT, MENU_QUIT_ID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/** End of menu functions **/

void setupWorld() {
// Let's create 5 wind turbines
	WindTurbine wt1 = WindTurbine(ColorPalette::red(),
			Position(0.0F, 0.0F, 0.0F), mWind);
	WindTurbine wt2 = WindTurbine(ColorPalette::blue(),
			Position(0.3f, 0.0f, 0.0f), mWind);
	WindTurbine wt3 = WindTurbine(ColorPalette::green(),
			Position(0.5f, 0.0f, 0.0f), mWind);
	WindTurbine wt4 = WindTurbine(ColorPalette::yellow(),
			Position(-0.3f, 0.0f, -0.0f), mWind);
	WindTurbine wt5 = WindTurbine(ColorPalette::white(),
			Position(-0.5f, 0.0f, -0.0f), mWind);
// Add them all to out windturbine list
	mWindTurbineList.push_back(wt1);
	mWindTurbineList.push_back(wt2);
	mWindTurbineList.push_back(wt3);
	mWindTurbineList.push_back(wt4);
	mWindTurbineList.push_back(wt5);

// Wind
	mWind.set_position(Position(0.0f, 0.3f, 0.0f));
	mWind.set_color(ColorPalette::yellow());
	mWind.set_size(1.0f);
}

void debugInfo() {
	Logger::screenInfo();
	std::cout << "---" << std::endl;
// print wind turbine list to stdout
	Logger::log(mWindTurbineList);
}

void setupWindow() {
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_TITLE);
	if (glutGet(GLUT_SCREEN_WIDTH) == 4920
			&& glutGet(GLUT_SCREEN_HEIGHT) == 1920) {
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
				(960 - WINDOW_HEIGHT) / 2);
	} else {
		// Center on screen (does NOT work with multiple displays!)
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
				(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
// http://www.opengl.org/documentation/specs/glut/spec3/node12.html
// GLUT_RGBA: RGBA mode window
// GLUT_DOUBLE: Double buffered window
// GLUT_DEPTH: Window with a depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
// GL_DEPTH_TEST: do depth comparisons and update the depth buffer
// http://www.opengl.org/sdk/docs/man/xhtml/glEnable.xml
	glEnable(GL_DEPTH_TEST); // Do I need this?
	setupWindow();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	setupKeyboard();
	setupMouse();
	setupMenu();
	setupWorld();

#ifdef DEBUG
	debugInfo();
#endif

	glutMainLoop();
	return 0;
}
