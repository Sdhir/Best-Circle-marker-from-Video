/********************************************************************
* processVideo.h
* Processes video frame by frame to detect frame with best 
* circular mark
*
* @author Sudhir Sornapudi <ssbw5@mst.edu>
* @version 1.2
**********************************************************************/

#ifndef PROCESSVIDEO_H
#define PROCESSVIDEO_H

#include <opencv2/opencv.hpp>
using namespace cv;

void processVideo(VideoCapture cap, Mat &inputframe);

#endif