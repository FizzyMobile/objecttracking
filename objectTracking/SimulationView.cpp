/*
 * SimulationView.cpp
 *
 *  Created on: 05-01-2013
 *      Author: Max
 */

#include "SimulationView.h"
#include "defines.h"
#include <cmath>
#include <iostream>
using namespace std;

SimulationView::SimulationView():trackedSpeed(INIT_SPEED),sim(DIST, REF_HEIGHT) { // initial distance
	//sim.init();
	_pause = true;
	_stop = false;
	init_main_panel();
}

void SimulationView::init_main_panel() {
	_width = WINDOW_WIDTH;
	_height = WINDOW_HEIGHT;
	_margin = 20;
	_object.size = REF_HEIGHT; //!
	_object.speed = 3;
	_object.objectTopLeft = cvPoint((_width-_object.size)/2, (_height-_object.size)/2);
	_object.objectBottomRight = cvPoint((_width+_object.size)/2, (_height+_object.size)/2);
	_pointingTarget = false;
}

Target* point_new_target(Mat targetImg, CvRect targetBox) {
	return new Target(targetImg, targetBox);
}

int SimulationView::start() {
	_frame = Mat::zeros(_height, _width, CV_8UC3);
	return 1;
}

void SimulationView::pause() {
	_pauseFrame = _frame.clone();
	_pause = true;
}

bool SimulationView::is_paused() {
	return _pause;
}

void SimulationView::resume() {
	_pause = false;
}

void SimulationView::stop() {
	pause();
	_stop = true;
}

bool SimulationView::is_stopped() {
	return _stop;
}

void SimulationView::updateObjectRepresentation() {
	_object.size = sim.getHeight();
	int frameCenter = _width/2;
	int objCenter = sin(sim.getAngle())/sin(CAMERA_ANGLE/2) * frameCenter  + frameCenter;
	(_object.objectTopLeft).x = objCenter - _object.size/2;
	(_object.objectBottomRight).x = objCenter + _object.size/2;

	(_object.objectTopLeft).y = _height/2 - _object.size/2;
	(_object.objectBottomRight).y = _height/2 + _object.size/2;

//	cout << _object.size << endl;


}

void SimulationView::set_target(Target* target) {
	_target = *target;
}

bool SimulationView::simulation_key_listener(Object_t* object, int max_x, int max_y) {
	char key;
	key = cvWaitKey(0);	// keypress wait time
	switch (key){
	case 'S':
	case 's':
		if((object->objectBottomRight).y + (object->speed) < max_y){
			(object->objectTopLeft).y += object->speed;
			(object->objectBottomRight).y += object->speed;
		} else {
			(object->objectTopLeft).y = max_y - object->size -1;
			(object->objectBottomRight).y = max_y -1;
		}
		break;
	case 'D':
	case 'd':
		sim.moveTracked(ROTATION_STEP, trackedSpeed * INTERVAL );
		break;
	case 'W':
	case 'w':
		sim.moveTracked(0, trackedSpeed * INTERVAL );
		break;
	case 'A':
	case 'a':
		sim.moveTracked(-ROTATION_STEP, trackedSpeed * INTERVAL );
		break;
	case 43: // '+'
		if ((object->speed) < 10){
			object->speed = object->speed + 1;
			printf("Object speed set to value: %d\n", object->speed);
		}
		break;
	case 45: // '-'
		if ((object->speed) > 1){
			object->speed = object->speed - 1;
			printf("Object speed set to value: %d\n", object->speed);
		}
		break;

	case 'Q':
	case 'q':
		return true;
		break;
	}
	return false;
}

void SimulationView::capture() {
	_stop = simulation_key_listener(&_object, _width, _height-_margin);
	if (!_stop){
		//simulation operations
		updateObjectRepresentation();


		_frame = Mat::zeros(_height, _width, CV_8UC3);
		rectangle(_frame,
				_object.objectTopLeft,
				_object.objectBottomRight,
				cvScalar(255,255,255),
				1,
				8,
				0);
	}
}

void SimulationView::track_target(){
	if (!_stop){
		Mat targetImg = _frame(Range(0, 0 + _height-_margin), Range(0, 0 + _width));
		CvRect targetBox = cvRect(0, 0, _height-_margin, _width);

		if (!is_target_set()){
			set_target(point_new_target(targetImg, targetBox));
		} else {
			_target.simulate(targetImg, targetBox);
		}
	}
}

Mat* SimulationView::get_frame() {
	return &_frame;
}

int SimulationView::get_height() {
	return get_frame()->rows-_margin;
}

int SimulationView::get_width() {
	return get_frame()->cols;
}

bool SimulationView::is_target_set() {
	return _target.is_ready();
}

Point SimulationView::get_target_position() {
	return _target.get_center();
}

void SimulationView::print_viewInfo() {
	line(_frame, cvPoint(0, _height-_margin), cvPoint(_width, _height-_margin), View::get_infoColor(), 1, 8, 0);
			char info[50];
			sprintf(info, "W:forward	A,D:rotate and move	S:wait	Q:quit");
			putText(_frame, info,
					cvPoint(10, _height-5),
					FONT_HERSHEY_PLAIN,
					0.7,
					View::get_infoColor(),
					1,
					CV_AA);
			View::print_viewInfo(_frame, get_height(), get_width());
}

void SimulationView::print_targetInfo() {
	if (is_target_set()){
			Point targetCenter = get_target_position();
			View::print_targetInfo(_frame, get_height(), get_width(), targetCenter);
		}
}

void SimulationView::show_main_panel() {
	imshow(SIMULATION_VIEW_NAME, _frame);
	if (waitKey(1) >= 0) {
	};
}
