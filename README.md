# Best-Circle-marker-from-Video
Extract best circle marker from video 

Purpose: Find one frame of the video which shows the best circle marker.
Program language: C++
IDE & Compiler: Visual Studio 2015
Third party library: OpenCV 3.4.0
[Note: The program is built with debug and release configurations on x64 platform.]
Program files:
- main.cpp
- pixelValue.cpp
- pixelValue.h
- processVideo.cpp
- processVideo.h
- FitContour.cpp
- FitContour.h
[FitCircleMarker.sln, FitCircleMarker.vcxproj, FitCircleMarker.vcxproj.filters and FitCircleMarker.vcxproj.user files are included to open the project in Visual Studio.]
Input file: sample.mov
Command arguments: Provide the location of the video file
[./sample.mov --default argument]
Output files: fitness_data.csv, best_frame<best_frame_index>.jpg
[Saves the output files in the same directory of program file]
Description:
▪ The program loads a video file from command line argument. A default argument is set assuming the video file (sample.mov) is in the same directory of program file.
▪ A mouse callback event is created. Click the left mouse button on video frame window to display the coordinates of the point along with the pixel intensity value. In order to analyze values, the program can be paused and resumed by pressing ‘P’ key.
▪ Each frame of the video is computed to find the best circle marker.
1. First, the color plane of the frame is converted to gray scale image.
2. Image is blurred to remove noise using Gaussian operator.
3. Binary threshold is applied with respect to brighter pixels (gray value > 200) to generate a binary mask containing the marker.
4. Flood fill operation is applied and the output image is complemented to detect the black disk with black circle in the frame as object.
5. The hole between the black circle and black disk is filled by again applying flood fill operation and then bit-wise OR operation on the complemented version of the flood filled mask and mask from previous step.
6. Contours around each object in the frame were found.
7. The index of contour with maximum area is found (contour around circle marker).
8. A green color contour is drawn around the circle marker.
9. The fitness of circle marker with ellipse features: eccentricity, radius and center were obtained.
10. Steps 1 - 9 were repeated on all the frames.
▪ Eccentricity is considered as the measure of fitting error. The closer it is to zero, the more circular the contour is.
▪ The data from all the frames were recorded in a csv file and the best frame with the best circle marker is saved and displayed as a jpg image. The program automatically exists after 30 seconds after the final image is displayed.
