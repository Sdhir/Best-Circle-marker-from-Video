/********************************************************************
* pixelValue.cpp
* Prints pixel value at particular point when left mouse button is 
* clicked.
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include "pixelValue.h"

using namespace std;
using namespace cv;

/*
* Function: pixelValue
* ----------------------------
*   Prints pixel value at particular point when left mouse button is clicked
*
*   @param event	mouse click event
*   @param x		x-coordinate
*   @param y		y-coordinate
*   @param userdata	frame
*
*   @return			None
*/
void pixelValue(int event, int x, int y, int , void* userdata) {
	Mat* framePtr = (Mat*)userdata;
	Mat &frame = *framePtr;
	Mat frame_gray;// = frames->frame_gray;
	// Action to be taken when left mouse button is pressed
	if (event == EVENT_LBUTTONDOWN) {
		// Mark the center
		Point center = Point(x, y);
		// BGR intensity
		Vec3b intensity = frame.at<Vec3b>(center);
		uchar blue = intensity.val[0];
		uchar green = intensity.val[1];
		uchar red = intensity.val[2];
		// Gray value
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY); // Convert BGR to gray scale frame
		Scalar gray = frame_gray.at<uchar>(center);
		cout << "at (x,y): " << center << " BGR value is: (" << (int)blue << "," << (int)green << "," << (int)red << ") and Gray value is: " << gray.val[0] << endl;
	}
}
