#include "hogdescriptorclass.h"

hogdescriptorrecognotion::hogdescriptorrecognotion(){
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

void hogdescriptorrecognotion::showVideoCap(){
	while(true){
		if ( ! VideoCap.read(mainFrame) ) // cam might need some warmup
		    break;
		imshow("mainFrame",mainFrame);
		if ( waitKey(10)==27 )
		    break;
	}
}

hogdescriptorrecognotion::~hogdescriptorrecognotion(){
	VideoCap.~VideoCapture();
	mainFrame.~Mat();
}