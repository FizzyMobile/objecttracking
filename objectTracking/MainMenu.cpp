/*
 * MainMenu.cpp
 *
 *  Created on: 03-01-2013
 *      Author: Max
 */

#include "MainMenu.h"

using cv::putText;

MainMenu::MainMenu() {
	_menuColor = cvScalar(180, 130, 70);
	_width = WINDOW_WIDTH;
	_height = WINDOW_HEIGHT;
	_blank = Mat::zeros(_height, _width, CV_8UC3);
	init_main_menu();
}

void MainMenu::init_main_menu(){
	char title[128];
	sprintf(title, "OBJECT TRACKING");
	putText(_blank, title,
				cvPoint(_width/2 - 90, 50),
				FONT_HERSHEY_PLAIN,
				1.3,
				_menuColor,
				1,
				CV_AA);

	int noMenuOptions = 4;
	char menu[noMenuOptions][128];
	sprintf(menu[0], "[%d] %s", CAMERA, CAMERA_TEXT);
	sprintf(menu[1], "[%d] %s", SIMULATION, SIMULATION_TEXT);
	sprintf(menu[2], "[%d] %s", INFO, INFO_TEXT);
	sprintf(menu[3], "[%d] %s", QUIT, QUIT_TEXT);

	for (int i = 0; i < noMenuOptions; i++){
		putText(_blank, menu[i],
				cvPoint(50, 90 + i*20),
				FONT_HERSHEY_PLAIN,
				1,
				_menuColor,
				1,
				CV_AA);
	}
}

void MainMenu::show(){
	imshow(MAIN_MENU_NAME, _blank);
}

int MainMenu::userChoice(){
	char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char key;
	key = cvWaitKey(0);

	if (key == digits[QUIT]){
	    destroyWindow(MAIN_MENU_NAME);
		return QUIT;
	}
	if (key == digits[CAMERA]){
		destroyWindow(MAIN_MENU_NAME);
		return CAMERA;
	}
	if (key == digits[SIMULATION]){
		destroyWindow(MAIN_MENU_NAME);
		return SIMULATION;
	}
	if (key == digits[INFO]){
		return NONE; // NOT YET IMPLEMENTED
	}
	return NONE;
}
