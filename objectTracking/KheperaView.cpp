/*
 * KheperaView.cpp
 *
 *  Created on: 23-11-2012
 *      Author: Max
 */

#include "KheperaView.h"

KheperaView::KheperaView(string rtspAddress) {
	_pause = true;
	_stop = false;
	set_rtsp(rtspAddress);
	init_main_panel();
}

void KheperaView::init_main_panel() {
	_mainPanel.name = MAINPANELNAME;
	_mainPanel.pointingTarget = false;
	//TODO add buttons
}

int KheperaView::start() {
	if (!_vcap.open(_rtsp)) {
		printf("Error opening video stream\n");
		return -1;
	} else {
		printf("Opening video stream succeded\n");
		resume();
		return 1;
	}
}

void KheperaView::pause() {
	_pauseFrame = _frame.clone();
	_pause = true;
}

bool KheperaView::is_paused() {
	return _pause;
}

void KheperaView::resume() {
	_pause = false;
}

void KheperaView::stop() {
	pause();
	_stop = true;
}

bool KheperaView::is_stoped() {
	return _stop;
}

void KheperaView::capture() {
	if (!_vcap.read(_frame)) {
		printf("No frame to read\n");
	}
}

Mat* KheperaView::get_frame() {
	return &_frame;
}

struct panel_t* KheperaView::get_mainPanel() {
	return &_mainPanel;
}

int KheperaView::get_height(){
	return get_frame()->rows;
}

int KheperaView::get_width(){
	return get_frame()->cols;
}

bool KheperaView::is_target_set() {
	return _target.is_ready();
}

Point KheperaView::get_target_position(){
	return _target.get_center();
}

Target* point_target(Mat frame, CvRect targetBox) {
	printf("Finding target in box - size width:%d height:%d x0:%d y0:%d\n",
			targetBox.width, targetBox.height, targetBox.x, targetBox.y);

	Mat targetImg = frame(Range(targetBox.y, targetBox.y + targetBox.height),
			Range(targetBox.x, targetBox.x + targetBox.width));

	//imshow("Target", targetImg);
	return new Target(targetImg, targetBox);
}

void KheperaView::set_target(Target* target) {
	_target = *target;
	circle(_frame, _target.get_center(), 5, Scalar(0, 0, 255), 1, 8, 0);
	circle(_frame, _target.get_center(), 10, Scalar(0, 0, 255), 1, 8, 0);
	imshow("Target is here", _frame);
	moveWindow("Target is here", 660, 1);
}

void mouse_callback(int event, int x, int y, int flags, void* param) {
	KheperaView* kv = (KheperaView*) param;

	struct panel_t* mainPanel = kv->get_mainPanel();
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		if (mainPanel->pointingTarget) {
			mainPanel->targetBox.width = x - mainPanel->targetBox.x;
			mainPanel->targetBox.height = y - mainPanel->targetBox.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		if (flags & CV_EVENT_FLAG_CTRLKEY) {
			printf("Left button down with CTRL pressed x:%d y:%d\n", x, y);
			mainPanel->pointingTarget = true;
			mainPanel->targetBox = cvRect(x, y, 0, 0);
			break;
		} else {
			printf("Left button down x:%d y:%d\n", x, y);
			//TODO menu click?
			if (kv->is_paused()) {
				printf("Image resumed\n");
				kv->resume();
			} else {
				printf("Image paused\n");
				kv->pause();
			}
		}
		break;
	case CV_EVENT_LBUTTONUP:
		mainPanel->pointingTarget = false;
		if (flags & CV_EVENT_FLAG_CTRLKEY) {
			printf("Left button up with CTRL pressed x:%d y:%d\n", x, y);
			if (mainPanel->targetBox.width < 0) {
				mainPanel->targetBox.x += mainPanel->targetBox.width;
				mainPanel->targetBox.width *= -1;
			}
			if (mainPanel->targetBox.height < 0) {
				mainPanel->targetBox.y += mainPanel->targetBox.height;
				mainPanel->targetBox.height *= -1;
			}
			kv->set_target(point_target(*(kv->get_frame()), mainPanel->targetBox));
		} else {
			printf("Left button up x:%d y:%d\n", x, y);
		}
		break;
	}
}

void KheperaView::show_main_panel() {
	cvSetMouseCallback(_mainPanel.name, mouse_callback, (void*) this);
	if (!_pause) {
		imshow(_mainPanel.name, _frame);
		if (waitKey(1) >= 0) {
		};
	} else {
		imshow(_mainPanel.name, _pauseFrame);
		if (waitKey(1) >= 0) {
		};
	}

}

void KheperaView::show_gray_view() {
	if (!_pause) {
		Mat gray;
		cvtColor(_frame, gray, CV_RGB2GRAY);
		imshow("Khepera View - RGB 2 GRAY", gray);
		if (waitKey(1) >= 0) {
			this->stop();
		}
	}
}

void KheperaView::set_rtsp(const string rtsp) {
	_rtsp = rtsp;
}
