#include <iostream>
#include <stdio.h>
#include "MainMenu.h"
#include "MainMenuOptions.h"
#include "KheperaView.h"
#include "SimulationView.h"
#include "TCPIP.h"
#include "WheelController.h"
#include "defines.h"

using namespace cv;
using namespace std;

/* Khepera's address*/
char kheperaAddress[] = "192.168.0.103";
/* Kolo Naukowe Robotyki's Camera */
string rtspAddress = "rtsp://192.168.0.106:554/live.sdp";
/* Testing Camera */
//string rtspAddress = "rtsp://212.77.7.133:80/h264lan.sdp";

int main(int argc, char** argv) {

	TCPIP tcpip;
	bool isKheperaConnected = false;
	int triesLeft = 2;
	while (!(tcpip.init() && tcpip.connect_to_server(kheperaAddress, 3000)) && triesLeft > 0) {
		tcpip = TCPIP();
		triesLeft--;
	}
	if (triesLeft > 0){
		isKheperaConnected = true;
	}
	if (!isKheperaConnected) {
		printf("Connection could not be established.\n");
	} else {
		printf("Connection has been established.\n");
	}

	View* view;
	bool finish = false;

	MainMenu* mainMenu = new MainMenu();
	mainMenu->show();
	int userChoice = NONE;
	while (userChoice == NONE){
		userChoice = mainMenu->userChoice();
	}
	switch (userChoice){
	case CAMERA:
		view = new KheperaView(rtspAddress);
		if (view->start() < 0) {
			printf("Camera is null\n");
			finish = true;
		} else {
			view->capture();
		}
		break;
	case SIMULATION:
		view = new SimulationView();
		if (view->start() < 0) {
			printf("Simulation could not be started\n");
			finish = true;
		} else {
			view->capture();
		}
		break;
	case QUIT:
		waitKey(0);
		cvDestroyAllWindows();
		return 0;
		break;
	}


	WheelController wc(view->get_width(), CAMERA_ANGLE, WHEEL_DIST, DIST, 10000);
	pair<int,int> control;

	while (!finish) {
		view->print_viewInfo();
		if (view->is_target_set()){
			view->print_targetInfo();
			if (isKheperaConnected){
				control = wc.getSpeeds(view->get_target_position().x, DIST);
				cout << control.first << ", " << control.second << endl;
				tcpip.send_speed(control.first, control.second);
			}
		}

		view->show_main_panel();
		view->capture();
		finish = view->is_stoped();
		if (!finish){
			view->track_target();
		}
	}

	tcpip.send_speed(0,0);
	cvDestroyAllWindows();
	waitKey(0);
	return 0;
}
