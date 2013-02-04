/*
 * Simulation.cpp
 *
 *  Created on: 03-02-2013
 *      Author: arch
 */

#include "Simulation.h"
#include "defines.h"
#include <iostream>
using namespace std;

Simulation::Simulation(float dist, float height) {
	init(dist, height);
}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::moveRobot(float r, float dist, bool toRight) {
	float beta = dist/r;
//	float alpha = 0.5 * (M_PI - beta);
	float dy = r * sin(beta);
	float dx = r * (1 - cos(beta));
	if (!toRight)
		dx = -dx;
	// rotacja o -phi
	float phi = - robot.phi;
	float px = cos(phi) * dx - sin(phi) * dy;
	float py = sin(phi) * dx + cos(phi) * dy;
	robot.x += px;
	robot.y += py;
	robot.phi += toRight ? beta : -beta;
}

void Simulation::moveTracked(float angle, float dist) {
	tracked.phi = fmod(tracked.phi + angle, 2*(float)M_PI);
	tracked.x += sin(tracked.phi)*dist;
	tracked.y += cos(tracked.phi)*dist;
	tracked.printCoords();
}

float Simulation::getAngle() {
	return 0.5 * M_PI - robot.phi - atan2(tracked.y - robot.y, tracked.x - robot.x);
}


//int inny_main() {
//	Simulation sim, sim1, sim2;
//	sim.moveRobot(100, 40, 1);
//	sim.robot.printCoords();
//	sim.moveRobot(100, 40, 0);
//	sim.robot.printCoords();
//	cout << "---\n";
//	sim1.tracked.printCoords();
//	sim1.moveTracked(M_PI/4, 100);
//	sim1.tracked.printCoords();
//	cout << sim1.getAngle() << endl;
//	return 0;
//}

void Simulation::init(float dist, float height) {
	refDist = dist;
	refHeight = height;
	moveTracked(0,dist);
}

float Simulation::getHeight() {
	float currentDist =	// Euclidean distance
			sqrt(pow(tracked.x - robot.x, 2) + pow(tracked.y - robot.y, 2));
	return refDist * refHeight / currentDist;
}
