/*
 * GHT.cpp
 *
 *  Created on: 18-01-2013
 *      Author: Cezary-P
 */

#include "GHT.h"

GHT::GHT() {
	test = true;
}

Point GHT::generalized_hough_transform(Mat image, vector<vector<Point> > contours, Point refPoint) {
	if (test) {
		cvtColor(image, image, CV_RGB2GRAY); // to gray scale
		blur(image, image, Size(3, 3));
		Canny(image, image, 10, 30); // standard filter
		imshow("INPUT", image);

		Mat ref = Mat::zeros( image.size(), CV_8UC3 );
		drawContours(ref, contours, 0, Scalar(255), CV_FILLED);
		imshow("REF", ref);
		//test = false;
	}
	Point max;
	max.x = 0;
	max.y = 0;
	return max;
}
