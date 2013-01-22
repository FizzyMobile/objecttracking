/*
 * GHT.h
 *
 *  Created on: 18-01-2013
 *      Author: Cezary-P
 */

#ifndef GHT_H_
#define GHT_H_

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "Target.h"

using namespace std;
using namespace cv;

class GHT {
private:
	float **_data;
	int _imageXsize;
	int _imageYsize;
	vector<vector<Point> > _inputContours;
	bool is_pixel_set(Mat image, int x, int y);
	void set_image_sizes(Mat image);
public:
	GHT();
	GHT(int height, int width);
	Point generalized_hough_transform(Mat image, vector<vector<Point> >contours, Point refPoint); // finding shape on image with GHT
};

#endif /* GHT_H_ */
