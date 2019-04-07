#include "hogdescriptorclass.h"

hogdescriptorrecognotion::hogdescriptorrecognotion(){
	VideoCapture cap("video.mp4"); // get first cam
    while( cap.isOpened() )
    {
        Mat frame;
        if ( ! cap.read(frame) ) // cam might need some warmup
            continue;

        // your processing goes here

        imshow("lalala",frame);
        if ( waitKey(10)==27 )
            break;
    }
}
hogdescriptorrecognotion::~hogdescriptorrecognotion(){
}