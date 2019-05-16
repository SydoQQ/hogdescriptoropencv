#include <unistd.h>
#include <getopt.h>
#include "hogdescriptorclass.h"

struct initilizateParametr
{
	int isMode;
	std::string fileName;
	int idWebCam;
};

void printhelpmessege(){
	out<<end;
	out<<"Param program"<<end;
	out<<"-w [id], --webcam [id]         - capture video with webcamera id (default open id=0)"<<end;
	out<<"-v videofile, --video videfile - open videofile"<<end;
	out<<"-h, --help                     - print this help"<<end;
	out<<end;

}

void startInitialized(initilizateParametr* param,int argv,char** argc){
	int opt=0;
	int ID;
	const option long_opts[] = {
	            {"webcam", optional_argument, NULL, 'w'},
	            {"video", required_argument, NULL, 'v'},
	            {"help", no_argument, NULL, 'h'},
	};
	while((opt=getopt_long(argv,argc,"w::v:h",long_opts,NULL)) !=-1){ // Parse arg command line
		switch(opt){
			case 'w':
				if(argv==3)
					ID=atoi(argc[2]);
				else	// if not parametr, open web cam 0
					ID=0;
				out<<"Capture video with web camera "<<ID<<end;		
				param->isMode=0;
    			param->idWebCam=ID;
    			param->fileName="";
				break;
			case 'v':
				out<<"Open video file "<<optarg<<end;
				param->isMode=1;
    			param->idWebCam=-1;
    			param->fileName=optarg;
				break;
			case 'h':
				printhelpmessege();
				break;
		}
	}

}

int main(int argv,char **argc){
	initilizateParametr param;
	hogdescriptorrecognotion recognitionClass;
    if(argv<=1){
    	param.isMode=0;
    	param.idWebCam=0;
    	param.fileName="";
    }
    if(argv>3){
    	out<<"Many arg"<<end;
    	return -1;
    }
    startInitialized(&param,argv,argc);
    if(param.isMode==0){
    	if(!recognitionClass.incvideocapture(param.idWebCam)){
    			out<<"Faild capture video with web camera "<<param.idWebCam<<end;
    			return -1;
    	}
    }
    else if(!recognitionClass.incvideocapture(param.fileName)){
    	out<<"Faild open video file "<<param.fileName<<end;
    	return -1;
    }
	out<<"Show video"<<end;
	recognitionClass.showVideoCap();
	return 0;
}
