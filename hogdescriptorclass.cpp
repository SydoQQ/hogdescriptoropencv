#include "hogdescriptorclass.h"

hogdescriptorrecognotion::hogdescriptorrecognotion(){
	countFrame_=0;
	currentFrame_=0;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

bool hogdescriptorrecognotion::incvideocapture(std::string filename){ // Open video file name
	VideoCap.open(filename);
	if(!VideoCap.isOpened()){
		out<<"Bad file name "<<filename<<end;
		return false;
	}
	return true;

}

bool hogdescriptorrecognotion::incvideocapture(int idwebcam){ // Open video with web camera id
	VideoCap.open(idwebcam);
	if(!VideoCap.isOpened()){
		out<<"Bad file name "<<idwebcam<<end;
		return false;
	}
	return true;
}

int hogdescriptorrecognotion::showVideoCap(){
	while(true){
		Mat frame;
		if ( ! VideoCap.read(frame) ) // cam might need some warmup
		    break;
		treameanImage(&frame);
		imshow("hog",frame);
		if ( waitKey(COUNTFRAMESECONDS)==27 )
		    break;
	}
	return 1;
}

hogdescriptorrecognotion::~hogdescriptorrecognotion(){
	VideoCap.~VideoCapture();
}

void hogdescriptorrecognotion::setCountFrame(int count){
	countFrame_=count;
}


int hogdescriptorrecognotion::getCountFrame(){
	return countFrame_;
}

void hogdescriptorrecognotion::treameanImage(Mat* frame){
	if(currentFrame_<=0){
		detectPeople(frame);
		drawRect(frame,detectPeople_);
		printLabel(frame);
		currentFrame_=countFrame_;
		return;
	}
	drawRect(frame,detectPeople_);
	printLabel(frame);
	--currentFrame_;
	return;
}

void hogdescriptorrecognotion::detectPeople(Mat* frame){
	std::vector<Rect> found;
    hog.detectMultiScale(*frame, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);  // Обрабока кадра хог дескриптором
    int size=found.size();
    size_t i,j;
    detectPeople_.clear();
    for (i = 0; i<size; ++i)
    {
        Rect r = found[i];
        for (j = 0; j<size; ++j)
            if (j != i && (r & found[j]) == r)
                break;
        if (j == size)
            detectPeople_.push_back(r);
    }
}

void hogdescriptorrecognotion::printLabel(Mat* frame){
	int size=detectPeople_.size();
	std::string str="People detect ";
	str.append(std::to_string(size));
	putText(*frame, str, Point(20,30), FONT_HERSHEY_DUPLEX, 1, Scalar(255,255,0), 2);
}

void hogdescriptorrecognotion::drawRect(Mat* frame,std::vector<Rect> detectPeople){
	int size=detectPeople.size();
    for (size_t i = 0; i<size; ++i)
    {
        Rect r = detectPeople[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.06);
        r.height = cvRound(r.height*0.9);
        rectangle(*frame, r.tl(), r.br(), cv::Scalar(0, 0, 255), 2);
    }
}