/*
 * WheelController.h
 *
 *  Created on: 11-12-2012
 *      Author: arch
 */

#ifndef WHEELCONTROLLER_H_
#define WHEELCONTROLLER_H_

#include <utility>

class WheelController {
public:
	WheelController(int _cw, float _ca, float _w, float _d, int _h, int _speed);

	virtual ~WheelController();
//	std::pair<int, int> getSpeeds(int a, float d);
	std::pair<int, int> getSpeeds(int a, int h);
	static int mmpsToKhep(float speed);

	float getR() const {
		return r;
	}

	float getSpeed() const {
		return speed;
	}

private:
	std::pair<int, int> getSpeeds(float angle, float d);
	float getReferenceSpeed(float d) const;
	float getDistance(float h) const;
	int cam_width;
	float cam_angle, w;
	float prev_d;
	const float D; // reference distance
	const int H;	// ref. size
	float speed;
	float r;
};

#endif /* WHEELCONTROLLER_H_ */
