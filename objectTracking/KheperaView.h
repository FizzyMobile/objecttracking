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
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class KheperaView {
private:
	VideoCapture _vcap;
	Mat _frame;
	string _rtsp;
	bool _mayDisplay;
	bool _finish;
	/* SETTERS */
	void set_rtsp(const string rtsp);

public:
	KheperaView(string rtspAddres);
	/* STREAM MANAGEMENT */
	int start(); 	//open stream (video capture)
	void pause(); 	//pause showing stream
	void resume();	//resume showing stream
	void stop(); 	//stop showing stream and finish
	void capture();	//update current frame
	/* VIEWS */
	void show_main_view();	//default khepera view with main panel
	void show_gray_view(); //testing method cvtColor->rgb2gray
	/* GETTERS */
	bool is_finish(); // returnintg _finish
	bool get_mayDisplay();
};

#endif /* KHEPERAVIEW_H_ */
