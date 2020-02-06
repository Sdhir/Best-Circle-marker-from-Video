/********************************************************************
* pixelValue.h
* Prints pixel value at particular point when left mouse button is 
* clicked.
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#ifndef PIXELVALUE_H
#define PIXELVALUE_H

#include <opencv2/opencv.hpp>

using namespace cv;

void pixelValue(int event, int x, int y, int flags, void* userdata);

#endif