/*
 * WheelController.cpp
 *
 *  Created on: 11-12-2012
 *      Author: arch
 */

#include "WheelController.h"
#include <iostream>
#include <cmath>
#include "defines.h"

#define _USE_MATH_DEFINES


using namespace std;

WheelController::WheelController(int _cw, float _ca, float _w, float _d, int _speed):cam_width(_cw), cam_angle(_ca), w(_w), prev_d(_d), speed(_speed) {
	// TODO Auto-generated constructor stub

}

WheelController::~WheelController() {
	// TODO Auto-generated destructor stub
}


std::pair<int, int> WheelController::getSpeeds(float angle, float d) {
	//const float d = 10;
	//const int speed = 10000;
	//const float w = 5; // distance between a wheel and the center of the robot

	bool to_right = angle > 0;

	angle = abs(angle);
	float alpha = (M_PI/2) - angle;
	float r = 0.5 * d / cos(alpha);
	float l_to_r = (r+w)/(r-w);
	//cout << "r=" << r << "; " << "ltor=" << l_to_r << endl;
	if(!to_right)
		l_to_r = 1./l_to_r;
	speed = getReferenceSpeed(d);
	prev_d = d; // !
	pair<int, int> speeds = make_pair(l_to_r * speed, (1./l_to_r) * speed);
	return speeds;
}

int WheelController::getReferenceSpeed(float d) const {
	float delta = d - prev_d;
	return speed + 2*delta/INTERVAL;
}

/*
int main() {
	WheelController wc;
	pair<int,int> sr, ml;
	sr = wc.getSpeeds(0);
	ml = wc.getSpeeds(-1);
	cout << sr.first << ", " << sr.second << endl;
	cout << ml.first << ", " << ml.second;
}
 */

std::pair<int, int> WheelController::getSpeeds(int a, float d) {
	int hw = cam_width/2;
	float angle = asin(1.*(a - hw)/(hw) * sin(cam_angle));
	return getSpeeds(angle, d);
}
