/*
 * KheperaView.h
 *
 *  Created on: 23-11-2012
 *      Author: Max
 */

#ifndef KHEPERAVIEW_H_
#define KHEPERAVIEW_H_

#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class KheperaView {
private:
	VideoCapture _vcap;
	Mat _image;
	string _rtsp;

public:
	KheperaView(string rtspAddres);
	int showView();
	void setRtsp(const string rtsp);
};

#endif /* KHEPERAVIEW_H_ */
