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
	char info[50];
		sprintf(info, "Width:%d Height:%d", width, height);
		putText(frame, info,
				cvPoint(width-130, frame.rows-5),
				FONT_HERSHEY_PLAIN,
				0.7,
				_infoColor,
				1,
				CV_AA);
}

void View::print_targetInfo(Mat& frame, int height, int width, Point targetCenter){
	circle(frame, targetCenter, 5, Scalar(0, 0, 255), 1, 8, 0);
	circle(frame, targetCenter, 10, Scalar(0, 0, 255), 1, 8, 0);
}


