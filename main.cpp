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

Wind mWind = Wind();
Camera mCam = Camera(Position(0.0F, 0.0f, -0.2f), Position(0.0f, 0.0f, 0.0f));
std::list<WindTurbine> mWindTurbineList;

void draw_object(DrawableObject &obj) {
	std::cout << "Drawing object " << obj << std::endl;
	obj.draw();
}

void display_camera() {
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	//glLoadIdentity ();

	for_each(mWindTurbineList.begin(), mWindTurbineList.end(), draw_object);
	Logger::log(mCam);
	mCam.update();

	// glPopMatrix();

	// http://www.delafond.org/traducmanfr/X11/man3/glFlush.3x.html
	// glFlush();
	glutSwapBuffers();
}

void idle() {
	//mCam.update();
	// glutPostRedisplay();
}

void reshape(int w, int h) {
	// TODO
}

void mousePress(int button, int state, int x, int y) {
	// TODO
}

void keyPress(unsigned char key, int x, int y) {
	switch (key) {
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

void makeRed(WindTurbine& wt) {
	wt.set_color(ColorPalette::red());
}

void makeBlue(WindTurbine& wt) {
	wt.set_color(ColorPalette::blue());
}

void makeGreen(WindTurbine& wt) {
	wt.set_color(ColorPalette::green());
}

void makeYellow(WindTurbine& wt) {
	wt.set_color(ColorPalette::yellow());
}

void makeWhite(WindTurbine& wt) {
	wt.set_color(ColorPalette::white());
}

void makeBlack(WindTurbine& wt) {
	wt.set_color(ColorPalette::black());
}

void menuSelect(int selection) {
	switch (selection) {
		case MENU_QUIT_ID:
			exit(0);
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
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(), makeRed);
			break;
		case MENU_COLOR_GREEN_ID:
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					makeGreen);
			break;
		case MENU_COLOR_BLUE_ID:
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					makeBlue);
			break;
		case MENU_COLOR_YELLOW_ID:
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					makeYellow);
			break;
		case MENU_COLOR_WHITE_ID:
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					makeWhite);
			break;
		case MENU_COLOR_BLACK_ID:
			for_each(mWindTurbineList.begin(), mWindTurbineList.end(),
					makeBlack);
			break;
	}
	glutPostRedisplay();
	// std::cout << "Wind strength: " << mWind.strength() << std::endl;
}

void setupMouse() {
	glutMouseFunc(mousePress);
}

void setupKeyboard() {
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
}

void setupMenu() {
	// Wind strength
	int windMenu = glutCreateMenu(menuSelect);
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
	glutAddSubMenu(MENU_WIND, windMenu);
	glutAddMenuEntry(MENU_QUIT, MENU_QUIT_ID);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setupWorld() {
	// Init camera
	// mCam = Camera(Position(0.0F, 0.0f, -0.2f), Position(0.0f, 0.0f, 0.0f));
	// Let's create 5 wind turbines
	WindTurbine wt1 = WindTurbine(ColorPalette::red(),
			Position(0.0F, 0.0F, 0.0F));
	WindTurbine wt2 = WindTurbine(ColorPalette::blue(),
			Position(0.3f, 0.0f, 0.0f));
	WindTurbine wt3 = WindTurbine(ColorPalette::green(),
			Position(0.5f, 0.0f, 0.0f));
	WindTurbine wt4 = WindTurbine(ColorPalette::yellow(),
			Position(-0.3f, 0.0f, -0.0f));
	WindTurbine wt5 = WindTurbine(ColorPalette::white(),
			Position(-0.5f, 0.0f, -0.0f));
	// Add them all to out windturbine list
	mWindTurbineList.push_back(wt1);
	mWindTurbineList.push_back(wt2);
	mWindTurbineList.push_back(wt3);
	mWindTurbineList.push_back(wt4);
	mWindTurbineList.push_back(wt5);
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
