/*
 * KheperaView.cpp
 *
 *  Created on: 23-11-2012
 *      Author: Max
 */

#include "KheperaView.h"

using cv::line;
using cv::line;

KheperaView::KheperaView(string rtspAddress) {
	_pause = true;
	_stop = false;
	set_rtsp(rtspAddress);
	init_main_panel();
}

void KheperaView::init_main_panel() {
	_mainPanel.name = CAMERA_VIEW_NAME;
	_mainPanel.pointingTarget = false;
}

int KheperaView::start() {
	printf("Connecting to\n %s\n", _rtsp.c_str());
	if (!_vcap.open(_rtsp)) {
		printf("Error opening video stream\n");
		return -1;
	} else {
		printf("Opening video stream succeeded\n");
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

bool KheperaView::khepera_key_listener() {
	char key;
	key = cvWaitKey(1);
	if (key == 'q' || key == 'Q'){
		return true;
	}
	return false;
}

void KheperaView::capture() {
	_stop = khepera_key_listener();
	if (!_stop){
		if (!_vcap.read(_frame)) {
			printf("No frame to read\n");
		}
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
	//imshow("Target is here", _frame);
	//moveWindow("Target is here", 660, 1);
}

void KheperaView::print_viewInfo(){
	char info[50];
		sprintf(info, "Press: [Q] to quit");
		putText(_frame, info,
				cvPoint(10, get_height()-5),
				FONT_HERSHEY_PLAIN,
				0.7,
				View::get_infoColor(),
				1,
				CV_AA);
		View::print_viewInfo(_frame, get_height(), get_width());
}

void KheperaView::print_targetInfo(){
	if (is_target_set()){
		Point targetCenter = get_target_position();
		View::print_targetInfo(_frame, get_height(), get_width(), targetCenter);
	}
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
				if (kv->is_paused()) {
					printf("Image resumed\n");
					kv->resume();
				} else {
					printf("Image paused\n");
					kv->pause();
				}
		} else {
			printf("Left button down x:%d y:%d\n", x, y);
				mainPanel->pointingTarget = true;
				mainPanel->targetBox = cvRect(x, y, 0, 0);
				break;
		}
		break;
	case CV_EVENT_LBUTTONUP:
		mainPanel->pointingTarget = false;
		if (flags & CV_EVENT_FLAG_CTRLKEY) {
			printf("Left button up with CTRL pressed x:%d y:%d\n", x, y);
		} else {
			printf("Left button up x:%d y:%d\n", x, y);
			if (mainPanel->targetBox.width < 0) {
				mainPanel->targetBox.x += mainPanel->targetBox.width;
				mainPanel->targetBox.width *= -1;
			}
			if (mainPanel->targetBox.height < 0) {
				mainPanel->targetBox.y += mainPanel->targetBox.height;
				mainPanel->targetBox.height *= -1;
			}
			if (mainPanel->targetBox.height > 0 && mainPanel->targetBox.width > 0)
			kv->set_target(point_target(*(kv->get_frame()), mainPanel->targetBox));
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

void KheperaView::set_rtsp(const string rtsp) {
	_rtsp = rtsp;
}

void KheperaView::track_target(){
	printf("tracking\n");
}
