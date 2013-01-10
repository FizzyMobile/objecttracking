/*
 * View.h
 *
 *  Created on: 03-01-2013
 *      Author: Max
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv/cv.h"

using namespace cv;
using namespace std;

class View {
private:
	CvScalar _infoColor;
protected:
	virtual void print_viewInfo(Mat& frame, int height, int width);
	virtual void print_targetInfo(Mat& frame, int height, int width, Point targetCenter);
	CvScalar get_infoColor();
public:
	View();
	virtual ~View();
	/* STREAM MANAGEMENT */
	virtual int start() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void stop() = 0;
	virtual void capture() = 0;
	/* VIEWS */
	virtual void print_viewInfo() = 0;
	virtual void print_targetInfo() = 0;
	virtual void show_main_panel() = 0;
	/* GETTERS */
	virtual bool is_paused() = 0;
	virtual bool is_stoped() = 0;
	virtual bool is_target_set() = 0;
	virtual int get_height() = 0;
	virtual int get_width() = 0;
	virtual Point get_target_position() = 0;
};

#endif /* VIEW_H_ */
