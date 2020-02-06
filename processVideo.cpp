/********************************************************************
* processVideo.cpp
* Processes video frame by frame to detect frame with best 
* circular mark
*
* Supporting files: 
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
#include <fstream>
#include "FitContour.h"

using namespace std;
using namespace cv;

Mat processFrame(Mat &);

/*
* Function: processVideo
* ----------------------------
*   Video is processed frame by frame to detect the best circle marker
*	Outputs "fitness_data.csv" and "best_framexxx.jpg"
*
*   @param cap			Captures video as frames
*   @param inputframe	frames from the video defined in main.cpp
*
*   @return				None
*/
void processVideo(VideoCapture cap, Mat &inputframe) {
	Mat best_frame;
	Mat frame = inputframe;
	bool playVideo = true;
	vector<vector<Point> > contour;
	vector<Vec4i> hierarchy;
	double best_radius;
	Point2f best_center;
	int count = 0;
	int best_frame_idx = 0;
	double best_e = std::numeric_limits<float>::infinity();

	ofstream outdata;
	String csv_filename = "fitness_data.csv";
	outdata.open(csv_filename);
	// write the file headers
	outdata << "frame_num" << "," << "fitting_error" << "," << "radius" << "," << "center [x_cor; y_cor]" << endl;

	//Read and display video frames until video is completed or 
	//user quits by pressing ESC
	while ((char)waitKey(25) != 27) {

		// Capture frame-by-frame
		if (playVideo) {
			cap >> inputframe;// frame;
			count++;
		}

		// If the frame is empty, break immediately
		if (inputframe.empty())
			break;

		// Preprocess the frame and generate binary mask of circle marker
		Mat object = processFrame(inputframe);

		// Find all contours
		findContours(object, contour, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		// Get the index of maximum area contour, i.e., circle marker
		int marker_idx = 0;
		double max_area = 0;
		for (int i = 0; i < contour.size(); i++) {
			double cnt_area = contourArea(contour[i]);
			if (cnt_area > max_area) {
				max_area = cnt_area;
				marker_idx = i;
			}
		}

		// Draw the contour on circle marker
		Mat drawing = inputframe.clone();
		drawContours(drawing, contour, marker_idx, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());

		// Calculate the fitness of circle marker with ellipse features
		FitContour marker(contour[marker_idx]); // Call the constructor of fitContour class

		// eccentricity: measure of deviation of a curve from being circular
		// eccentricity of circle = 0; eccentricity of ellipse = (0,1) [ranges from zero to one]
		// eccentricity is considered as the measure of fitting error
		double eccentricity = marker.getEccentricity(); // deviation of contour from being circle
		double radius = marker.getRadius(); // radius assuming contour to be circle
		Point2f center = marker.getCenter(); // center assuming contour to be circle

		if (playVideo) {
			cout << "Frame index: " << count << " --> Fitting_error: " << eccentricity << ", radius: " << radius << ", center [x,y]: " << center << endl; // print data
			outdata << count << "," << eccentricity << "," << radius << "," << "[" << center.x << "; " << center.y << "]" << endl; // write to csv file
		}

		// Get the best circle marker
		if (eccentricity <= best_e) {
			best_e = eccentricity;
			best_radius = radius;
			best_center = center;
			best_frame_idx = count;
			best_frame = drawing;
		}

		// Show in a window
		// Display the resulting frame
		imshow("Frame with detected circle marker", drawing);
		//imshow("Gray Frame", frame_gray);
		//imshow("Object Detection", frame_threshold);
		//imshow("Object", object);
		//imshow("Contours", contour);

		// Pause/Play video by pressing "p" 
		char key = waitKey(25);
		if (key == 'p')
			playVideo = !playVideo;

	}

	// When everything done, release the video capture object
	cap.release();
	// Close all the frames
	destroyAllWindows();
	// Close File
	outdata.close();

	// save and display frame with best circle marker
	String output_name = "best_frame" + to_string(best_frame_idx) + ".jpg";
	imwrite(output_name, best_frame);
	namedWindow(output_name, CV_WINDOW_AUTOSIZE);
	imshow(output_name, best_frame);
	// close the output file

	// print information of best circle marker detected
	cout << "\nOutput:" << endl;
	cout << "Best Frame index: " << best_frame_idx << " --> Fitting_error: " << best_e << ", radius: " << best_radius << ", center [x,y]: " << best_center << endl;

}

/*
* Function: processFrame
* ----------------------------
*   Video is processed frame by frame to detect the best circle marker
*	Outputs "fitness_data.csv" and "best_framexxx.jpg"
*
*   @param frame	frames from the video defined in main.cpp
*
*   @return	object		Binary mask with the circle marker detected
*/

Mat processFrame(Mat &frame) {

	Mat frame_gray, frame_threshold, frame_gauss;

	cvtColor((Mat &)frame, (Mat &)frame_gray, COLOR_BGR2GRAY); // Convert BGR to gray scale frame
	GaussianBlur((Mat &)frame_gray, frame_gauss, Size(3, 3), 0); // Remove noise by smoothing image
	threshold(frame_gauss, frame_threshold, 200, 255, THRESH_BINARY); // Binary threshold w.r.t. brighter pixels (gray value > 200)
	Mat frame_floodfill = frame_threshold.clone();
	floodFill(frame_floodfill, Point(0, 0), Scalar(255));
	Mat frame_floodfill_inv = Mat::zeros(frame.rows, frame.cols, CV_8U);
	bitwise_not(frame_floodfill, frame_floodfill_inv);

	// Fill holes with in the maker circle
	Mat frame_fillhole = frame_floodfill_inv.clone();
	floodFill(frame_fillhole, Point(0, 0), Scalar(255));
	Mat frame_fillhole_inv = Mat::zeros(frame.rows, frame.cols, CV_8U);
	bitwise_not(frame_fillhole, frame_fillhole_inv);
	Mat object = (frame_floodfill_inv | frame_fillhole_inv);

	/*/// Apply the closing morphology operation to fill hole
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(11, 11), Point(-1, -1));
	morphologyEx(frame_floodfill_inv, object, MORPH_CLOSE, element);*/

	return object;
}