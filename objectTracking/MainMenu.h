/*
 * MainMenu.h
 *
 *  Created on: 03-01-2013
 *      Author: Max
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "MainMenuOptions.h"

#define MAIN_MENU_NAME "OBJECT TRACKING - Main Menu"
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 360

using namespace cv;
using namespace std;

class MainMenu {
private:
	CvScalar _menuColor;
	int _width;
	int _height;
	Mat _blank;
	void init_main_menu();
public:
	void show();
	MainMenu();
	int userChoice(); // returning users choice
};

#endif /* MAINMENU_H_ */
