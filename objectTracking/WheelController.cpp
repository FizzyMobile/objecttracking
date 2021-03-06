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

WheelController::WheelController(int _cw, float _ca, float _w, float _d, int _h, int _speed):cam_width(_cw), cam_angle(_ca), w(_w), prev_d(_d), D(_d), H(_h), speed(_speed), r(0) {

}

WheelController::~WheelController() {
	// TODO Auto-generated destructor stub
}


std::pair<int, int> WheelController::getSpeeds(float angle, float d) {
	if (d <= DIST)
		return make_pair(0, 0);

	bool to_right = angle > 0;

	angle = abs(angle);
	float alpha = (M_PI/2) - angle;
	r = 0.5 * d / cos(alpha);	// ew. predykcja: (2*d - prev_d)
	//cout << "r=" << r << "; " << "ltor=" << l_to_r << endl;
	speed = getReferenceSpeed(d);	// ew. arcdist
	prev_d = d; // !
	pair<int, int> speeds;
	if(to_right) {
		speeds = make_pair(
			mmpsToKhep((r+w)/r * speed),
			mmpsToKhep((r-w)/r * speed));
	} else {
		speeds = make_pair(
					mmpsToKhep((r-w)/r * speed),
					mmpsToKhep((r+w)/r * speed));
	}
	return speeds;
}

float WheelController::getReferenceSpeed(float d) const {
	float delta = d - prev_d;
	return speed + 2*delta/INTERVAL;
}

int WheelController::mmpsToKhep(float speed) {
	return speed * COEF;
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

//std::pair<int, int> WheelController::getSpeeds(int a, float d) {
//	int hw = cam_width/2;
//	float angle = asin(1.*(a - hw)/(hw) * sin(cam_angle));
//	return getSpeeds(angle, d);
//}

std::pair<int, int> WheelController::getSpeeds(int a, int h) {
	int hw = cam_width/2;
		float angle = atan(1.*(a - hw)/(hw) * tan(cam_angle/2));	// mozliwosc buga
		float dist = (float)H/h * D;
//		cout << h << " " << H << " "<< dist << ", " << D << endl;	// tu jest zle
		return getSpeeds(angle, dist);
}
