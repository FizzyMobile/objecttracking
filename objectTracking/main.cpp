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
char kheperaAddress[] = "192.168.0.104";
/* Kolo Naukowe Robotyki's Camera */
string rtspAddress = "rtsp://192.168.0.106:554/live.sdp";
/* Testing Camera */
//string rtspAddress = "rtsp://212.77.7.133:80/h264lan.sdp";

int main(int argc, char** argv) {

	TCPIP tcpip;
	bool isKheperaConnected = false;
	int triesLeft = 10;
	while (triesLeft > 0 && !(tcpip.init() && tcpip.connect_to_server(kheperaAddress, 3000))) { //!!!
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


	WheelController wc(view->get_width(), CAMERA_ANGLE, WHEEL_DIST/2, DIST, REF_HEIGHT, INIT_SPEED);
	pair<int,int> control;

	while (!finish) {
		view->print_viewInfo();
		if (view->is_target_set()){
			view->print_targetInfo();
			control = wc.getSpeeds(view->get_target_position().x, REF_HEIGHT/2);	// zmienic na wysokosc celu
//			cout << control.first << ", " << control.second << endl;
			if (isKheperaConnected){
				tcpip.send_speed(control.first, control.second);
			}
		}

		view->show_main_panel();
		view->capture();
		finish = view->is_stopped();
		if (!finish){
			view->track_target();
		}
	}

	tcpip.send_speed(0,0);
	cvDestroyAllWindows();
	waitKey(0);
	return 0;
}
