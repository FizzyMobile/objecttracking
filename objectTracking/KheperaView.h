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

#define MAINPANELNAME "Khepera View - MAIN PANEL"
struct panel_t {
	const char* name;
	CvRect targetBox;
	bool pointingTarget;
};

using namespace cv;
using namespace std;

class KheperaView {
private:
	VideoCapture _vcap;
	Mat _frame;
	Mat _pauseFrame;
	string _rtsp;
	bool _pause;
	bool _stop;
	struct panel_t _mainPanel;
	/* PANEL */
	void init_main_panel();
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
	void show_main_panel();	//default khepera view with main panel
	void show_gray_view(); //testing method cvtColor->rgb2gray
	/* GETTERS */
	bool is_paused(); // returning _pause
	bool is_stoped(); // returning _stop
	struct panel_t* get_mainPanel();
	Mat* get_frame();
};

#endif /* KHEPERAVIEW_H_ */
