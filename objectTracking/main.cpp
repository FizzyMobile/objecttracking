#include <iostream>
#include <stdio.h>
#include "KheperaView.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	const string videoStreamAddress = "rtsp://192.168.0.106:554/live.sdp";
	KheperaView* kheperaView = new KheperaView(videoStreamAddress);
	if (kheperaView->showView() < 0) {
		printf("Camera is null\n");
	}

	waitKey(0);
	return 0;
}

