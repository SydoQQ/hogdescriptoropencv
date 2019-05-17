#ifndef HOGDESCRIPTORCLASS_H
#define HOGDESCRIPTORCLASS_H

#include <iostream>
#include <vector>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#define out std::cout
#define end std::endl
#define COUNTFRAMESECONDS 25  // Количество кадров в секунду

using namespace cv;

class hogdescriptorrecognotion
{	
	VideoCapture VideoCap; 
	HOGDescriptor hog;
	int countFrame_;
	int currentFrame_;
	std::vector<Rect> detectPeople_;
public:
	hogdescriptorrecognotion(); 
	bool incvideocapture(std::string); // Open video file name
	bool incvideocapture(int); // Open video with web camera id
	int showVideoCap();  // Функция вывода видео
	void setCountFrame(int);  // Функция установки пропуска кадров
	int getCountFrame();
	void treameanImage(Mat*);  // Функция обработки
	void detectPeople(Mat*); // Функция детектирования количества людей
	void printLabel(Mat*);  // Функция вывода полученого количества
	void drawRect(Mat*,std::vector<Rect>);  // Функция вывода подстветки

	~hogdescriptorrecognotion();
};

#endif