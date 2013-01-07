/*
 * Target.h
 *
 *  Created on: 05-12-2012
 *      Author: Max
 */

#ifndef TARGET_H_
#define TARGET_H_

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/core/types_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Target {
private:
	bool _ready;
	/* IMAGE */
	Mat _targetImg;
	/* REPRESENTATION */
	Mat _rectBoundingMask; //black for background; white for object
	Point _center;
	CvRect _rectBounding; 	//.x & .y are global for camera frame not _targetImg
	//TODO spatial color histogram
	/* IMAGE RECOGNITION */
	void extract_from(Mat image);
	void pick_bigger_object(vector<vector<Point> > contours,
			int noObjectsFound);
	bool adjust_size(CvRect oldRect);

public:
	Target();
	Target(Mat targetImg, CvRect rectBounding);
	/* GETTERS */
	bool is_ready();
	Point get_center();
	/* SIMULATION */
	void simulate(Mat targetImg, CvRect rectBounding); // is updating Point _center
};

#endif /* TARGET_H_ */
