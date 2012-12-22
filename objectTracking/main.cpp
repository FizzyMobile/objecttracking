#include <iostream>
#include <stdio.h>
#include "KheperaView.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	bool finish = false;

	/* Kolo Naukowe Robotyki's Camera */
	string rtspAddress = "rtsp://192.168.0.106:554/live.sdp";
	/* Testing Camera */
	//string rtspAddress = "rtsp://212.77.7.133:80/h264lan.sdp";

	KheperaView* kheperaView = new KheperaView(rtspAddress);
	if (kheperaView->start() < 0) {
		printf("Camera is null\n");
		finish = true;
	}

	kheperaView->capture();
	int frame_height = kheperaView->get_height();
	int frame_width = kheperaView->get_width();
	bool test = true;

	while (!finish) {
		kheperaView->show_main_panel();

		/* Example of output */
		if (kheperaView->is_target_set()){
			if (test){
			Point target_center = kheperaView->get_target_position();
			printf("Target center: x:%d/%d y:%d/%d\n", target_center.x, frame_width, target_center.y, frame_height);
			test = false;
			}
		}

		finish = kheperaView->is_stoped();
		kheperaView->capture();
	}

	waitKey(0);
	cvDestroyAllWindows();
	return 0;
}
