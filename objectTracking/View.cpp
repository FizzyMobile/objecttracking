/*
 * View.cpp
 *
 *  Created on: 03-01-2013
 *      Author: Max
 */

#include "View.h"

View::View() {
	_infoColor = cvScalar(118,238,0);
}

View::~View() {
}

CvScalar View::get_infoColor() {
	return _infoColor;
}

void View::print_viewInfo(Mat& frame, int height, int width){

}

void View::print_targetInfo(Mat& frame, int height, int width, Point targetCenter){

}


