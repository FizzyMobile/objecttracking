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
	WheelController();
	virtual ~WheelController();
	std::pair<int, int> getSpeeds(float angle) const;

};

#endif /* WHEELCONTROLLER_H_ */
