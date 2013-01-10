/*
 * WheelController.cpp
 *
 *  Created on: 11-12-2012
 *      Author: arch
 */

#include "WheelController.h"
#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES


using namespace std;

WheelController::WheelController() {
	// TODO Auto-generated constructor stub

}

WheelController::~WheelController() {
	// TODO Auto-generated destructor stub
}


std::pair<int, int> WheelController::getSpeeds(float angle, float d) const {
	//const float d = 10;
	const int speed = 10000;
	const float w = 5; // distance between a wheel and the center of the robot

	bool to_right = angle > 0;

	angle = abs(angle);
	float alpha = (M_PI/2) - angle;
	float r = 0.5 * d / cos(alpha);
	float l_to_r = (r+w)/(r-w);
	//cout << "r=" << r << "; " << "ltor=" << l_to_r << endl;
	if(!to_right)
		l_to_r = 1./l_to_r;
	pair<int, int> speeds = make_pair(l_to_r * speed, (1./l_to_r) * speed);
	return speeds;
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
