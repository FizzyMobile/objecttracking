/*
 * Entity.cpp
 *
 *  Created on: 04-02-2013
 *      Author: arch
 */

#include "Entity.h"
#include <iostream>

Entity::Entity():x(0),y(0),phi(0) {
	// TODO Auto-generated constructor stub

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

void Entity::printCoords() {
	std::cout << x << ", " << y << ", " << phi << std::endl;
}
