/*
 * GHT.cpp
 *
 *  Created on: 18-01-2013
 *      Author: Cezary-P
 */

#include "GHT.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using cv::findContours;


GHT::GHT() {
	_data = new float*[1];
	_data[0] = new float[1];
	_imageYsize = 0;
	_imageXsize = 0;
}

bool GHT::is_pixel_set(Mat image, int x, int y){
	if (image.at<float>(y,x) == -1.0f){
		return true;
	} else {
		return false;
	}
}

void GHT::set_image_sizes(Mat image){
	_imageYsize = image.size().height;
	_imageXsize = image.size().width;
}

Point GHT::generalized_hough_transform(Mat image, vector<vector<Point> > contours, Point refPoint) {
	Point max;
	max.x = 0;
	max.y = 0;
	cvtColor(image, image, CV_RGB2GRAY);
	blur(image, image, Size(3, 3));
	Canny(image, image, 30, 70);
	//imshow("INPUT", image);

/*
	Mat ref = Mat::zeros( image.size(), CV_32FC3 );
	drawContours(ref, contours, 0, Scalar(255), CV_FILLED);
	imshow("REF", ref);
//*/
	if (_imageYsize == 0){
		set_image_sizes(image.clone());
		_data = new float*[_imageYsize];
		for (int i = 0; i < _imageYsize; i++){
			_data[i] = new float[_imageXsize];
		}

		for (int i = 0; i < _imageYsize; i++){
			for (int j = 0; j < _imageXsize; j++){
				_data[i][j] = 0.0f;
			}
		}
	}

	int voteX, voteY, imageX, imageY;
	findContours(image, _inputContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); // for contour finding

	for (int i = 0; (unsigned)i < _inputContours.size(); i++){
		for (int j = 0; (unsigned)j < _inputContours.at(i).size(); j++){
			imageX = _inputContours.at(i).at(j).x;
			imageY = _inputContours.at(i).at(j).y;
			for (int c = 0; (unsigned) c < contours.at(0).size(); c++){
				voteX = refPoint.x - contours.at(0).at(c).x;
				voteY = refPoint.y - contours.at(0).at(c).y;
				if (
					(imageX + voteX) >= 0
							&&
					(imageX + voteX) < _imageXsize
							&&
					(imageY + voteY) >= 0
							&&
					(imageY + voteY) < _imageYsize) {

					if (_data[imageY + voteY][imageX + voteX] < 1.0f){
						_data[imageY + voteY][imageX + voteX] = 1.0f;
					} else {
						_data[imageY + voteY][imageX + voteX] += 1.0f;
						if ((refPoint.x - imageX + voteX)*(refPoint.x - imageX + voteX) < 400){
							_data[imageY + voteY][imageX + voteX] += 2.0f;
						}
						if ((refPoint.y - imageY + voteY)*(refPoint.y - imageY + voteY) < 400){
							_data[imageY + voteY][imageX + voteX] += 2.0f;
						}
					}
				}
			}
		}
	}
	float maxVal = -1;

	for (int i = 0; i < _imageYsize; i++){
		for (int j = 0; j < _imageXsize; j++){
			if (_data[i][j] > 5.0f){
				if (maxVal < _data[i][j]){
					maxVal = _data[i][j];
					max.y = i;
					max.x = j;
				}
			}
			_data[i][j] = 0.0f;
		}
	}

	return max;
}
