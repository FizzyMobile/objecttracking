/*
 * Entity.h
 *
 *  Created on: 04-02-2013
 *      Author: arch
 */

#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {
public:
	Entity();
	virtual ~Entity();
	double x,y;
	float phi;

	void printCoords();

};

#endif /* ENTITY_H_ */
