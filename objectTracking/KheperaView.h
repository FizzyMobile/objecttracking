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
#include "opencv2/core/core.hpp"
#include "View.h"
#include "Target.h"
#include "GHT.h"

#define CAMERA_VIEW_NAME "Camera View"
struct panel_t {
	const char* name;
	CvRect targetBox;
	bool pointingTarget;
};

using namespace cv;
using namespace std;

class KheperaView : public View {
private:
	VideoCapture _vcap;
	Mat _frame;
	Mat _pauseFrame;
	string _rtsp;
	bool _pause;
	bool _stop;
	struct panel_t _mainPanel;
	Target _target;
	GHT _ght;
	/* PANEL */
	void init_main_panel();
	void print_viewInfo();
	void print_targetInfo();
	bool khepera_key_listener();
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
	/* TACKING */
	void track_target(); //tracking with GHT
	/* VIEWS */
	void show_main_panel();	//default khepera view with main panel
	/* GETTERS */
	bool is_paused(); // returning _pause
	bool is_stoped(); // returning _stop
	bool is_target_set();
	struct panel_t* get_mainPanel();
	Mat* get_frame();
	int get_height();
	int get_width();
	Point get_target_position();
	/* SETTERS */
	void set_target(Target* target);
};

#endif /* KHEPERAVIEW_H_ */
