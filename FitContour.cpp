/********************************************************************
* FitContour.cpp
* Implements methods of FitCountour class.
* Fits the contour to an ellipse and extracts features like
* eccentricity, radius and center.
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "FitContour.h"

using namespace std;
using namespace cv;

/*
* Method: FitContour
* ----------------------------
*   Constructor to calcuate length of major and minor axis of contour
*	Belongs to FitContour class
*
*   @param contour	Collection of points in a vector
*   @return			None
*/
FitContour::FitContour(vector<Point> &contour) {
	Mat(contour).convertTo(pointsf, CV_32F);
	ellipse = fitEllipse(pointsf);
	if (ellipse.size.height >= ellipse.size.width) {
		length_major = ellipse.size.height;
		length_minor = ellipse.size.width;
	}
	else {
		length_major = ellipse.size.width;
		length_minor = ellipse.size.height;
	}
}

/*
* Method: ~FitContour
* ----------------------------
*   Destructor
*	Belongs to FitContour class
*
*   @param		None 
*   @return		None
*/
FitContour::~FitContour() {
}

/*
* Method: getEccentricity
* ----------------------------
*   Computes eccentricity based on length of major and minor axis
*	Belongs to FitContour class
*
*   @param		None
*   @return	e	Eccentricity
*/
double FitContour::getEccentricity() {
	e = sqrt(1 - (pow(length_minor, 2) / pow(length_major, 2))); // e^2 = (1 - b^2/a^2)
	return e;
}

/*
* Method: getRadius
* ----------------------------
*   Computes diameter based on length of major and minor axis
*	Belongs to FitContour class
*
*   @param			None
*   @return	radius	diameter/2
*/
double FitContour::getRadius() {
	diameter = (length_minor + length_minor) / 2;
	return diameter / 2; // r = d/2
}

/*
* Method: getCenter
* ----------------------------
*   Computes the centriod of the elliptical contour
*	Belongs to FitContour class
*
*   @param			None
*   @return	center	Point of intersection of major and minor axis
*/
Point2f FitContour::getCenter() {
	center = ellipse.center;
	return center;
}