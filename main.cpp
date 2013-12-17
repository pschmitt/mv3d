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
#include "objects/Wind.h"
#include "objects/WindTurbine.h"

// debug mode
#define DEBUG 1
// Window infos

using namespace schmitt_co;

Wind mWind;
std::list<WindTurbine> mWindTurbineList;

void drawObject(DrawableObject &obj) {
	//std::cout << "Drawing object " << obj << std::endl;
	obj.draw();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for_each(mWindTurbineList.begin(), mWindTurbineList.end(), drawObject);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSwapBuffers();
}

void reshape(int w, int h) {
	// TODO
}

void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
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
			break;
		case GLUT_KEY_RIGHT:
			break;
	}
	glutPostRedisplay();
}

void makeRed(WindTurbine& wt) {
	wt.set_color(Color(1.0F, 0.0F, 0.0F));
}

void makeBlue(WindTurbine& wt) {
	wt.set_color(Color(0.0F, 0.0F, 1.0F));
}

void makeGreen(WindTurbine& wt) {
	wt.set_color(Color(0.0F, 1.0F, 0.0F));
}

void makeYellow(WindTurbine& wt) {
	wt.set_color(Color(1.0F, 1.0F, 0.0F));
}

void makeWhite(WindTurbine& wt) {
	wt.set_color(Color(1.0F, 1.0F, 1.0F));
}

void makeBlack(WindTurbine& wt) {
	wt.set_color(Color(0.0F, 0.0F, 0.0F));
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
	Position pos = Position(0.0F, 0.0F, 0.0F);
	Color col = Color(1.0F, 0.0F, 0.0F);
	WindTurbine wt = WindTurbine(col, pos);
	wt.draw();
	mWindTurbineList.push_back(wt);
	/*for (int i = 0; i < 5; ++i) {
	 Position pos = Position(i, i + 2, i * 3);
	 WindTurbine wt = WindTurbine(WindTurbine::BLACK, pos);
	 mWindTurbineList.push_back(wt);
	 }*/
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
		// Center on screen (does NOT work whith multiples display!)
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
				(glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	setupWindow();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	setupKeyboard();
	setupMenu();
	setupWorld();

#ifdef DEBUG
	debugInfo();
#endif

	glutMainLoop();
	return (0);
}
