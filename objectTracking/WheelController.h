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
	WheelController(int _cw, float _ca, float _w);

	virtual ~WheelController();
	std::pair<int, int> getSpeeds(float angle, float d) const;
	std::pair<int, int> getSpeeds(int a, float d) const;
private:
	int cam_width;
	float cam_angle, w;
};

#endif /* WHEELCONTROLLER_H_ */
