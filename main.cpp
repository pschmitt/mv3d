/*
 * main.cpp
 *
 *  Created on: Dec 13, 2013
 *      Author: pschmitt
 */

#include <GL/freeglut_std.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "Wind.h"

#define DEBUG 1
#define WINDOW_TITLE "MV3D - Projet - schmitt.co"
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define MENU_WIND "Wind Strength"
#define MENU_WIND_NONE "None"
#define MENU_WIND_WEAK "Weak"
#define MENU_WIND_NORMAL "Normal"
#define MENU_WIND_STRONG "Strong"
#define MENU_COLOR "Color"
#define MENU_COLOR_RED "Red"
#define MENU_COLOR_GREEN "Green"
#define MENU_COLOR_BLUE "Blue"
#define MENU_QUIT "Quit"

enum menu_id {
    MENU_QUIT_ID = 0,
    MENU_WIND_ID,
    MENU_WIND_NONE_ID,
    MENU_WIND_WEAK_ID,
    MENU_WIND_NORMAL_ID,
    MENU_WIND_STRONG_ID,
    MENU_COLOR_RED_ID,
    MENU_COLOR_BLUE_ID,
    MENU_COLOR_GREEN_ID
};

using namespace schmitt_co;

Wind mWind;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSwapBuffers();
}

void myinit(void) {
}

void reshape(int w, int h) {
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

void menuSelect(int selection) {
    switch (selection) {
        case MENU_QUIT_ID:
            exit(0);
            break;
        case MENU_WIND_NONE_ID:
            mWind.setStrength(Wind::NONE);
            break;
        case MENU_WIND_WEAK_ID:
            mWind.setStrength(Wind::WEAK);
            break;
        case MENU_WIND_NORMAL_ID:
            mWind.setStrength(Wind::NORMAL);
            break;
        case MENU_WIND_STRONG_ID:
            mWind.setStrength(Wind::STRONG);
            break;
        case MENU_COLOR_RED_ID:
            break;
        case MENU_COLOR_GREEN_ID:
            break;
        case MENU_COLOR_BLUE_ID:
            break;
    }
    std::cout << "Wind strength: " << mWind.getStrength() << std::endl;
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
    // Main menu
    glutCreateMenu(menuSelect);
    glutAddSubMenu(MENU_COLOR, colorMenu);
    glutAddSubMenu(MENU_WIND, windMenu);
    glutAddMenuEntry(MENU_QUIT, MENU_QUIT_ID);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setupWorld() {
    //mWind = new Wind;
}

void screenInfo() {
    std::cout << "Size: " << glutGet(GLUT_SCREEN_WIDTH) << "x"
            << glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
    std::cout << "Position: " << glutGet((GLenum) GLUT_WINDOW_X) << "x"
            << glutGet((GLenum) GLUT_WINDOW_Y) << std::endl;
    std::cout << "window id: " << glutGetWindow() << std::endl;
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
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    setupWindow();
    myinit();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    setupKeyboard();
    setupMenu();
    setupWorld();

#ifdef DEBUG
    screenInfo();
#endif

    glutMainLoop();
    return (0);
}
