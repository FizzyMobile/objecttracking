/*
 * KheperaView.cpp
 *
 *  Created on: 23-11-2012
 *      Author: Max
 */

#include "KheperaView.h"

KheperaView::KheperaView(string rtspAddress) {
	_mayDisplay = false;
	_finish = false;
	set_rtsp(rtspAddress);
}

int KheperaView::start() {
	if (!_vcap.open(_rtsp)) {
		printf("Error opening video stream\n");
		return -1;
	} else {
		printf("Opening video stream succeded\n");
		_mayDisplay = true;
		return 1;
	}
}

void KheperaView::pause() {
	_mayDisplay = false;
}

void KheperaView::resume() {
	// TODO not working
	_mayDisplay = true;
}

void KheperaView::stop() {
	_mayDisplay = false;
	_finish = true;
}

bool KheperaView::is_finish() {
	return _finish;
}

void KheperaView::capture() {
	if (!_vcap.read(_frame)) {
		printf("Oops: No frame\n");
	}
}

void mouse_callback(int event, int x, int y, int flags, void* param) {
	//KheperaView* kv = (KheperaView*) param;
	//Mat* frame = (Mat*) param;
	if (event == CV_EVENT_LBUTTONDOWN) {
		//TODO on-frame menu w. buttons
		printf("MOSUE LEFT BUTTON CLICK on x:%d y:%d\n", x, y);
		//e.g. imshow("test view", *frame);
	}
}

void KheperaView::show_main_view() {
	//TODO add buttons (new class Button?) to image
	cvSetMouseCallback("Khepera View - MAIN PANEL", mouse_callback,
					(void*) this);
					//(void*) &_frame);

	if (_mayDisplay) {
		imshow("Khepera View - MAIN PANEL", _frame);
		if (waitKey(1) >= 0) { //TODO delete this if
			this->stop();
		}
	}

}

void KheperaView::show_gray_view() {
	if (_mayDisplay) {
		Mat gray;
		cvtColor(_frame, gray, CV_RGB2GRAY);
		imshow("Khepera View - RGB 2 GRAY", gray);
		if (waitKey(1) >= 0) {
			this->stop();
		}
	}
}

bool KheperaView::get_mayDisplay(){
	return _mayDisplay;
}

void KheperaView::set_rtsp(const string rtsp) {
	_rtsp = rtsp;
}

