/*
 * Simulation.h
 *
 *  Created on: 03-02-2013
 *      Author: arch
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <cmath>
#include "Entity.h"

class Simulation {
public:
	Simulation(float dist, float height);
	virtual ~Simulation();
	Entity robot, tracked;
	void init(float dist, float height); // set reference height/dist, MOVE tracked
	void moveRobot(float r, float speed, bool toRight);
	void moveTracked(float angle, float dist);
	float getAngle();	// returns the angle of tracked from robot's axis
	float getHeight();	// returns the angle of tracked from robot's axis
	void printCoords();
private:
	float refHeight, refDist;
};

#endif /* SIMULATION_H_ */
