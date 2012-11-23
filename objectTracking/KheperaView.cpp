/*
 * KheperaView.cpp
 *
 *  Created on: 23-11-2012
 *      Author: Max
 */

#include "KheperaView.h"

KheperaView::KheperaView(string rtspAddress) {
	setRtsp(rtspAddress);
}

int KheperaView::showView() {
	if (!_vcap.open(_rtsp)) {
		printf("Error opening video stream or file\n");
		return -1;
	}
	while (1) {
		if (!_vcap.read(_image)) {
			cout << "Oops: No frame" << endl;
			waitKey();
		}
		imshow("Khepera View", _image);
		if (waitKey(1) >= 0)
			break;
	}
	return 1;
}

void KheperaView::setRtsp(const string rtsp) {
	_rtsp = rtsp;
}
