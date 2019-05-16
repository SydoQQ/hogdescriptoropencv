#ifndef HOGDESCRIPTORCLASS_H
#define HOGDESCRIPTORCLASS_H

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#define out std::cout
#define end std::endl

using namespace cv;

class hogdescriptorrecognotion
{	
	VideoCapture VideoCap;
	Mat mainFrame;
public:
	hogdescriptorrecognotion(); 
	bool incvideocapture(std::string); // Open video file name
	bool incvideocapture(int); // Open video with web camera id
	void showVideoCap();
	~hogdescriptorrecognotion();
};

#endif