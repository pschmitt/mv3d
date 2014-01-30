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
#include <string>
#include <sstream>

#include "constants/DefaultConstants.h"
#include "constants/MenuConstants.h"
#include "constants/WindowConstants.h"

#include "utils/Logger.h"
#include "utils/ColorPalette.h"
#include "objects/DrawableObject.h"
#include "objects/Camera.h"
#include "objects/Light.h"
#include "objects/Wind.h"
#include "objects/WindTurbine.h"

// debug mode
// #define DEBUG 1

using namespace schmitt_co;

/** Runtime options **/

int mLastX = -1;
int mLastY = -1;
int mCurrentX = -1;
int mCurrentY = -1;

bool mMousePressed = false;
bool mOptionLight = true;
bool mOptionAutoPilot = false;
bool mOptionAutoPilotReverse = false;
bool mPreserveOriginalWindMillColors = true;
bool mOptionShowHelp = true;

/** End of runtime options **/

/** Object initialization **/

Wind mWind = Wind();
// Default color (white)
Color mColor = ColorPalette::white();
Camera mCam = Camera(Position(0.0F, 0.0f, -0.2f), Position(0.0f, 0.0f, 0.0f));
std::list<WindTurbine> mWindTurbineList;
// Lights
Light light1 = Light(GL_LIGHT0, Position(1.0, 1.0, 1.0));
Light light2 = Light(GL_LIGHT1, Position(.6, 1.0, 1.0));

/** End of object initialization **/

/** Function declarations **/

void drawObject(DrawableObject& obj);
void display();
void idle();
void reshape(int width, int height);
void glutenPrint(float x, float y, void* font, std::string text);
void resetScene();
void resetZoom(WindTurbine& wt);
void zoomIn(WindTurbine& wt);
void zoomOut(WindTurbine& wt);
void zoom(bool zoomingIn);
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
void setupLightning();
void drawWindInfo();

/** End of function declaration **/

/** Display functions **/

void drawObject(DrawableObject& obj) {
#ifdef DEBUG
	std::cout << "Drawing object " << obj << std::endl;
#endif
	obj.draw();
}

void glutenPrint(float x, float y, void* font, std::string text) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	for (unsigned int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(font, text[i]);
	}
}

void drawHelp() {
	int xPos = -1;
	void* font = GLUT_BITMAP_9_BY_15;
	glColor4fv(ColorPalette::gray().color());
	// TODO Don't do character alignment
	glutenPrint(xPos, 0.95, font, " Cheat sheet");
	glutenPrint(xPos, 0.9, font, " ---");
	glColor4fv(ColorPalette::white().color());
	glutenPrint(xPos, 0.85, font, " Ctrl-0: Reload scene");
	glutenPrint(xPos, 0.8, font, " a     : Autopilot");
	glutenPrint(xPos, 0.75, font, " A     : Change autopilot rotation");
	glutenPrint(xPos, 0.7, font, " s     : Change wind strength");
	glutenPrint(xPos, 0.65, font, " d     : Change wind direction");
	glutenPrint(xPos, 0.6, font, " l     : Toggle light 1");
	glutenPrint(xPos, 0.55, font, " L     : Toggle light 2");
	glutenPrint(xPos, 0.5, font, " h     : Toggle display help");
	glutenPrint(xPos, 0.45, font, " q     : Quit");
}

void drawWindInfo() {
	// TODO Adjust position
	int xPos = 0.95;
	void* font = GLUT_BITMAP_9_BY_15;
	std::stringstream ss;
	ss << mWind;
	glutenPrint(xPos, 0.95, font, ss.str());
}

void drawLightInfo() {
	int xPos = 0.95;
	void* font = GLUT_BITMAP_9_BY_15;
	std::stringstream ss;
	ss << light1;
	glutenPrint(xPos, 0.9, font, ss.str());
	// Clear stream
	ss.clear();
	ss.str(std::string());
	ss << light2;
	glutenPrint(xPos, 0.85, font, ss.str());
}

void display() {
	// Clear
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Start from origin
	glLoadIdentity();

	// Lightning
	light1.lightUp();
	light2.lightUp();

	// Draw text
	glPushMatrix();
	{
		if (light1.enabled() || light2.enabled()) {
			// Temporarily disable lighting
			glDisable(GL_LIGHTING);
		}
		// Text should always be white
		glColor4fv(ColorPalette::white().color());
		// Draw help if desired
		if (mOptionShowHelp) {
			drawHelp();
		}
		drawWindInfo();
		drawLightInfo();
		if (light1.enabled() || light2.enabled()) {
			// Reenable lighting
			glEnable(GL_LIGHTING);
		}
	}
	glPopMatrix();

	// Draw objects
	glPushMatrix();
	{
		// Help text
		mCam.update();
#ifdef DEBUG
		Logger::log(mCam);
#endif
		mWind.draw();
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(), drawObject);
	}
	glPopMatrix();

	// http://www.delafond.org/traducmanfr/X11/man3/glFlush.3x.html
	glFlush(); // ?
	glutSwapBuffers(); // swap buffers, otherwise we won't see anything
}

void idle() {
	if (mOptionAutoPilot) {
		if (mOptionAutoPilotReverse) {
			mCam.decrease_angle();
		} else {
			mCam.increase_angle();
		}
	}
	glutPostRedisplay();
}

// Source: http://stackoverflow.com/a/15779607
void reshape(int windowWidth, int windowHeight) {
	const float aspectRatio = ((float) windowWidth) / windowHeight;
	double xSpan = 1.0; // Feel free to change this to any xSpan you need.
	double ySpan = 1.0; // Feel free to change this to any ySpan you need.

	if (aspectRatio > 1.0) {
		// Width > Height, so scale xSpan accordingly.
		xSpan *= aspectRatio;
	} else {
		// Height >= Width, so scale ySpan accordingly.
		ySpan = xSpan / aspectRatio;
	}

	gluOrtho2D(-1.0 * xSpan, xSpan, -1.0 * ySpan, ySpan);

	// Use the entire window for rendering.
	glViewport(0, 0, windowWidth, windowHeight);
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
 * Update all wind turbines in our list to reflect user choices
 */
void updateWindTurbines() {
	for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
			updateWindTurbine);
}

/** Mouse functions **/

void zoomIn(WindTurbine& wt) {
	wt.set_size(wt.size() + 0.1);
	glutPostRedisplay();
}

void zoomOut(WindTurbine& wt) {
	float current_size = wt.size();
	if (current_size - 0.1 > 0.1) {
		wt.set_size(wt.size() - 0.1);
		glutPostRedisplay();
	}
}

void resetZoom(WindTurbine& wt) {
	wt.set_size(0.1);
}

void resetScene() {
	for_each(mWindTurbineList.begin(), mWindTurbineList.end(), resetZoom);
	mWind.set_size(0.1f);
	mCam.set_angle(0.0f);
	// mCam.set_position(Position(0, 0, 0));
	mOptionAutoPilot = mOptionAutoPilotReverse = false;
	glutPostRedisplay();
}

/**
 * Zoom function
 * TODO Don't just increase object size (is gluLookAt a better solution?)
 * TODO Reset function
 */
void zoom(bool zoomingIn) {
	if (zoomingIn) {
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(), zoomIn);
		mWind.set_size(mWind.size() + 0.1);
	} else {
		for_each(mWindTurbineList.begin(), mWindTurbineList.end(), zoomOut);
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
		case 'a': // Toggle auto pilot
			mOptionAutoPilot = !mOptionAutoPilot;
			break;
		case 'A': // Change auto pilot direction
			mOptionAutoPilot = true;
			mOptionAutoPilotReverse = !mOptionAutoPilotReverse;
			break;
		case 's': // Change wind strength
			mWind.next_strength();
			updateWindTurbines();
			glutPostRedisplay();
			break;
		case 'd': // Change wind direction
			mWind.next_direction();
			updateWindTurbines();
			glutPostRedisplay();
			break;
		case 'l':
			light1.toggle();
			break;
		case 'L':
			light2.toggle();
			break;
		case 'h': // Toggle help display
			mOptionShowHelp = !mOptionShowHelp;
			break;
		case 32: // SPACE
			mOptionAutoPilot = !mOptionAutoPilot;
			break;
		case '0':
			// Ctrl - 0
			// Source: https://www.opengl.org/discussion_boards/showthread.php/137151-how-to-use-glutGetModifiers
			if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
				// Reset
				resetScene();
			}
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
		case MENU_LIGTH1_ENABLE_ID:
			light1.enable();
			break;
		case MENU_LIGTH1_DISABLE_ID:
			light1.disable();
			break;
		case MENU_LIGTH2_ENABLE_ID:
			light2.enable();
			break;
		case MENU_LIGTH2_DISABLE_ID:
			light2.disable();
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
// Lights
	int lightMenu = glutCreateMenu(menuSelect);
	glutAddMenuEntry(MENU_LIGTH1_ENABLE, MENU_LIGTH1_ENABLE_ID);
	glutAddMenuEntry(MENU_LIGTH1_DISABLE, MENU_LIGTH1_ENABLE_ID);
	glutAddMenuEntry(MENU_LIGTH2_ENABLE, MENU_LIGTH2_ENABLE_ID);
	glutAddMenuEntry(MENU_LIGTH2_DISABLE, MENU_LIGTH2_DISABLE_ID);
// Main menu
	glutCreateMenu(menuSelect);
	glutAddSubMenu(MENU_COLOR, colorMenu);
	glutAddSubMenu(MENU_WIND_STR, windStrMenu);
	glutAddSubMenu(MENU_WIND_DIR, windDirMenu);
	glutAddSubMenu(MENU_LIGHT, lightMenu);
// Auto pilot & quit
	glutAddMenuEntry(MENU_AUTO_PILOT, MENU_AUTO_PILOT_ID);
	glutAddMenuEntry(MENU_QUIT, MENU_QUIT_ID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/** End of menu functions **/

/** Lightning **/

void setupLightning() {

	// Don't touch this as it works!
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 75.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0); // Useless?
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

/** End of lightning **/

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
	// glEnable(GL_DEPTH_TEST); // Do I need this?
	// Enable blending (for transparency)
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_BLEND);
	//glEnable(GL_POLYGON_STIPPLE);

	// Enable this so that we don't loose colors when lightning on
	glEnable(GL_COLOR_MATERIAL);

	setupWindow();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	setupKeyboard();
	setupMouse();
	setupMenu();
	setupWorld();
	// setupLightning();

#ifdef DEBUG
	debugInfo();
#endif

	glutMainLoop();
	return 0;
}
