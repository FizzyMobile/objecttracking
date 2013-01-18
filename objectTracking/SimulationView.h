/*
 * SimulationView.h
 *
 *  Created on: 05-01-2013
 *      Author: Max
 */

#ifndef SIMULATIONVIEW_H_
#define SIMULATIONVIEW_H_

#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "View.h"
#include "Target.h"

#define SIMULATION_VIEW_NAME "Simulation View"
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 360

using namespace cv;
using namespace std;

struct Object_t {
	CvPoint objectTopLeft;
	CvPoint objectBottomRight;
	int size;
	int speed;
};

class SimulationView : public View {
private:
	int _width;
	int _height;
	int _margin;
	Mat _frame;
	Mat _pauseFrame;
	bool _pause;
	bool _stop;
	Object_t _object;
	Target _target;
	bool _pointingTarget;
	/* PANEL */
	void init_main_panel();
	void print_viewInfo();
	void print_targetInfo();
	bool simulation_key_listener(Object_t* object, int max_x, int max_y);

public:
	SimulationView();
	/* PSEUDO-STREAM MANAGEMENT */
	int start(); 	//open stream
	void pause(); 	//pause showing stream
	void resume();	//resume showing stream
	void stop(); 	//stop showing stream and finish
	void capture();	//update current frame
	/* TACKING */
	void track_target(); //tracking by getting biggest object
	/* VIEWS */
	void show_main_panel();
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

#endif /* SIMULATIONVIEW_H_ */
