#include <unistd.h>
#include <getopt.h>
#include "hogdescriptorclass.h"

void printhelpmessege(){
	out<<end;
	out<<"Param program"<<end;
	out<<"-w [id], --webcam [id]         - capture video with webcamera id (default open id=0)"<<end;
	out<<"-v videofile, --video videfile - open videofile"<<end;
	out<<"-h, --help                     - print this help"<<end;
	out<<end;

}

int main(int argv,char **argc){
	hogdescriptorrecognotion recognitionClass;
    if(argv<=1){
    	out<<"Open web cam  id 0"<<end;
    	if(recognitionClass.incvideocapture(0)) // if not parametr, open web cam 0
    		return 1;
    	else
    		return -1;
    }
    if(argv>3){
    	out<<"Many arg"<<end;
    	return -1;
    }
    bool videoIsOpen=false;
	int opt=0;
	const option long_opts[] = {
	            {"webcam", optional_argument, nullptr, 'w'},
	            {"video", required_argument, nullptr, 'v'},
	            {"help", no_argument, nullptr, 'h'},
	};
	int ID=0;
	while((opt=getopt_long(argv,argc,"w::v:h",long_opts,nullptr)) !=-1){ // Parse arg command line
		if(videoIsOpen){
			break;
		}
		switch(opt){
			case 'w':
				if(argv==3)
					ID=atoi(argc[2]);		
				out<<"Capture video with web camera "<<ID<<end;
				if(recognitionClass.incvideocapture(ID)){
						out<<"File open"<<end;
					    videoIsOpen=true;
				} // if not parametr, open web cam 0
				else
					return -1;
				break;
			case 'v':
				out<<"Open video file "<<optarg<<end;
				if(recognitionClass.incvideocapture(optarg)){
						out<<"File open"<<end;
					    videoIsOpen=true;
				} // if not parametr, open web cam 0
				else
					return -1;
				break;
			case 'h':
				printhelpmessege();
				break;
		}
	}
	out<<"Show video"<<end;
	recognitionClass.showVideoCap();
	return 0;
}
