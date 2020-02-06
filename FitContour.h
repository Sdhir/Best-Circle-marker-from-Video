/********************************************************************
* FitContour.h
* Defines FitContour class.
* Fits the contour to an ellipse and extracts features like
* eccentricity, radius and center.
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#ifndef FITCIRCLEMARKER_H
#define FITCIRCLEMARKER_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


class FitContour
{
	Mat pointsf;
	double length_major, length_minor, e, diameter;
	Point2f center;
	RotatedRect ellipse;

public:
	FitContour(vector<Point> &contour);
	~FitContour(void);
	double getEccentricity();
	double getRadius();
	Point2f getCenter();
};

#endif