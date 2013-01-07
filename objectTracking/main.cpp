#include <iostream>
#include <stdio.h>
#include "MainMenu.h"
#include "MainMenuOptions.h"
#include "KheperaView.h"
#include "SimulationView.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	View* view;
	bool finish = false;

	/* Kolo Naukowe Robotyki's Camera */
	//string rtspAddress = "rtsp://192.168.0.106:554/live.sdp";
	/* Testing Camera */
	string rtspAddress = "rtsp://212.77.7.133:80/h264lan.sdp";

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

	while (!finish) {
		view->print_viewInfo();
		if (view->is_target_set()){
			view->print_targetInfo();
			/*
			 * int frame_height = view->get_height();
			 * int frame_width = view->get_width();
			 * Point target_center = view->get_target_position();
			 * printf("Target center: x:%d/%d y:%d/%d\n", target_center.x, frame_width, target_center.y, frame_height);
			 */
		}

		view->show_main_panel();

		view->capture();
		finish = view->is_stoped();
	}

	cvDestroyAllWindows();
	return 0;
}
