/*
 * Target.cpp
 *
 *  Created on: 05-12-2012
 *      Author: Max
 */

#include "Target.h"
#include <stdio.h>
#include <string.h>

using cv::circle;

Target::Target() {
	_ready = false;
}

int half_size(int size) {
	return (size - (size % 2)) / 2;
}

Target::Target(Mat targetImg, CvRect rectBounding) {
	_targetImg = targetImg.clone();
	this->extract_from(_targetImg); // _rectBoundingMask created
	if (this->adjust_size(rectBounding)) {
		_center.x = half_size(_rectBoundingMask.cols) + _rectBounding.x;
		_center.y = half_size(_rectBoundingMask.rows) + _rectBounding.y;
		_ready = true;
		//imshow("Mask adjusted to size", _rectBoundingMask);
		//moveWindow("Mask adjusted to size", 350, 500);
	} else {
		_ready = false;
	}
}

void Target::simulate(Mat targetImg, CvRect rectBounding) {
	_targetImg = targetImg.clone();
	this->extract_from(_targetImg); // _rectBoundingMask created
	if (this->adjust_size(rectBounding)) {
		_center.x = half_size(_rectBoundingMask.cols) + _rectBounding.x;
		_center.y = half_size(_rectBoundingMask.rows) + _rectBounding.y;
		_ready = true;
		//imshow("Mask adjusted to size", _rectBoundingMask);
		//moveWindow("Mask adjusted to size", 350, 500);
	} else {
		_ready = false;
	}
}

void Target::extract_from(Mat image) {
	const double CONTRAST = 1.2;
	const int BRIGHTNESS = 0;
	Mat tempImg;

	// Prepare for contour finding
	image.convertTo(image, -1, CONTRAST, BRIGHTNESS); // better contrast
	cvtColor(image, tempImg, CV_RGB2GRAY); // to gray scale
	Canny(tempImg, tempImg, 100, 200); // standard filter

	// Contour finding
	vector<vector<Point> > contours;
	findContours(tempImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); // for contour finding

	// Mask creation
	_rectBoundingMask = Mat::zeros(tempImg.rows, tempImg.cols, CV_8UC1);
	drawContours(_rectBoundingMask, contours, -1, Scalar(255), CV_FILLED); // fill component
	//imshow("Mask before picking the bigger one", _rectBoundingMask);
	if (contours.size() > 1)
		this->pick_bigger_object(contours, contours.size()); //only biggest element found is takken into account

	// Show results
	//imshow("Mask", _rectBoundingMask);
	//imshow("Image with contours only", tempImg);
}

void Target::pick_bigger_object(vector<vector<Point> > contours,
		int noObjectsFound) {
	vector<double> objects(noObjectsFound);
	double max;
	Point maxPosition;
	for (int i = 0; i < noObjectsFound; i++) {
		objects[i] = contourArea(Mat(contours[i]));
	}
	minMaxLoc(Mat(objects), 0, &max, 0, &maxPosition);
	Mat noneMask = Mat::zeros(_rectBoundingMask.rows, _rectBoundingMask.cols,
			CV_8UC1);
	_rectBoundingMask = noneMask.clone(); // clearing mask in order to draw only one object
	drawContours(_rectBoundingMask, contours, maxPosition.y, Scalar(255), CV_FILLED); //Scalar(0) -> black = background; 255->object
	vector<Point> newContours = contours.at(maxPosition.y);
	setContours(newContours);
}

void Target::setContours(vector<Point> newContours){
	_contours.reserve(newContours.size());
	copy(newContours.begin(),newContours.end(),back_inserter(_contours));
}

bool Target::adjust_size(CvRect oldRect) {
	_rectBounding.x = oldRect.x;
	_rectBounding.y = oldRect.y;
	_rectBounding.width = oldRect.width;
	_rectBounding.height = oldRect.height;

	bool found;
	// cols from left
	int empty = 0;
	found = false;
	int i = 0;
	while (!found && (i < _rectBoundingMask.cols)) {
		if (countNonZero(_rectBoundingMask.col(i)) > 0) {
			found = true;
		} else {
			empty++;
		}
		i++;
	}
	if (empty == _rectBoundingMask.cols) {
		return false;
	}
	if (empty != 0) {
		_rectBounding.x += empty;
		_rectBounding.width -= empty;
		_rectBoundingMask = _rectBoundingMask(Range(0, _rectBoundingMask.rows),
				Range(empty, _rectBoundingMask.cols));
	}
	// cols from right
	empty = 0;
	found = false;
	i = _rectBoundingMask.cols - 1;
	while (!found && (i >= 0)) {
		if (countNonZero(_rectBoundingMask.col(i)) > 0) {
			found = true;
		} else {
			empty++;
		}
		i--;
	}
	if (empty == _rectBoundingMask.cols)
		return false;
	if (empty != 0) {
		_rectBounding.width -= empty;
		_rectBoundingMask = _rectBoundingMask(Range(0, _rectBoundingMask.rows),
				Range(0, _rectBoundingMask.cols - empty - 1));
	}
	// rows from top
	empty = 0;
	found = false;
	i = 0;
	while (!found && (i < _rectBoundingMask.rows)) {
		if (countNonZero(_rectBoundingMask.row(i)) > 0) {
			found = true;
		} else {
			empty++;
		}
		i++;
	}
	if (empty == _rectBoundingMask.rows)
		return false;
	if (empty != 0) {
		_rectBounding.y += empty;
		_rectBounding.height -= empty;
		_rectBoundingMask = _rectBoundingMask(
				Range(empty, _rectBoundingMask.rows),
				Range(0, _rectBoundingMask.cols));
	}
	// rows from bottom
	empty = 0;
	found = false;
	i = _rectBoundingMask.rows - 1;
	while (!found && (i >= 0)) {
		if (countNonZero(_rectBoundingMask.row(i)) > 0) {
			found = true;
		} else {
			empty++;
		}
		i--;
	}

	if (empty == _rectBoundingMask.rows)
		return false;
	if (empty != 0) {
		_rectBounding.width -= empty;
		_rectBoundingMask = _rectBoundingMask(
				Range(0, _rectBoundingMask.rows - empty - 1),
				Range(0, _rectBoundingMask.cols));
	}

	return true;
}

bool Target::is_ready() {
	return _ready;
}

Point Target::get_center() {
	return _center;
}
