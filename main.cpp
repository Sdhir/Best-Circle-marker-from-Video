/********************************************************************
* main.cpp
* Extract Best Circle Marker from a Video
* 
* Supporting files: 
*	- pixelValue.cpp
*	- pixelValue.h
*	- processVideo.cpp
*	- processVideo.h
*	- FitContour.cpp
*	- FitContour.h
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <limits>
#include <iostream>
#include <fstream>
#include "FitContour.h"
#include "pixelValue.h"
#include "processVideo.h"

using namespace std;
using namespace cv;


// Controls operation of the program.
int main(int argc, char **argv) {
	Mat frame;
	//OnMouse frames;
	// Command Line Parser
	CommandLineParser parser(argc, argv, "{help h||}{@video|./sample.mov|}");
	if (parser.has("help")) {
		cout <<
			"\nThis program is demonstration for finding one frame (image) which shows a \n"
			"perfect circle marker \n"
			"Call:\n"
			"FitCircleMarker [video_dir -- Default ./sample.mov]\n" << endl;
		return 0;
	}
	string filename = parser.get<string>("@video");

	// Create a VideoCapture object and open the input file
	VideoCapture cap(filename);
	double length = cap.get(CAP_PROP_FRAME_COUNT);
	cout << "Total number of frames in the video: " << length << endl;

	// Check if video is loaded successfully and read a frame from the object cap
	if (!cap.isOpened()) {
		cout << "Error opening video file" << endl;
		return -1;
	}

	// Window to display video frame by frame
	namedWindow("Frame with detected circle marker", CV_WINDOW_AUTOSIZE);
	// Set the callback function for mouse event
	// Click Left mouse button any where on the video (Frame Window) gives the coordinates of the point along with the pixel intensity
	//Mat *framePtr = &frame;
	setMouseCallback("Frame with detected circle marker", pixelValue,  &frame);

	// Perform computations on the captured frames of the video
	processVideo(cap, frame);

	// Wait for 30 seconds before existing
	waitKey(30000);
	return 0;
}