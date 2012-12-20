#include <iostream>
#include <stdio.h>
#include "KheperaView.h"

using namespace cv;
using namespace std;

//int main(int argc, char** argv) {
//	bool finish = false;
//
//	/* Kolo Naukowe Robotyki's Camera */
//	//string rtspAddress = "rtsp://192.168.0.106:554/live.sdp";
//	/* Testing Camera */
//	string rtspAddress = "rtsp://212.77.7.133:80/h264lan.sdp";
//
//	KheperaView* kheperaView = new KheperaView(rtspAddress);
//	if (kheperaView->start() < 0) {
//		printf("Camera is null\n");
//		finish = true;
//	}
//
//	while (!finish) {
//		kheperaView->capture();
//
//
//		//kheperaView->show_gray_view();
//		kheperaView->show_main_panel();
//
//
//		finish = kheperaView->is_stoped();
//	}
//
//	waitKey(0);
//	cvDestroyAllWindows();
//	return 0;
//}
