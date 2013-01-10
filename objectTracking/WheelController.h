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
	WheelController(int _cw, float _ca, float _w, float _d, int _speed);

	virtual ~WheelController();
	std::pair<int, int> getSpeeds(float angle, float d);
	std::pair<int, int> getSpeeds(int a, float d);
private:
	int getReferenceSpeed(float d) const;
	int cam_width;
	float cam_angle, w;
	float prev_d;
	int speed;
};

#endif /* WHEELCONTROLLER_H_ */
