#include <unistd.h>
#include <getopt.h>
#include <sstream>
#include "hogdescriptorclass.h"

struct initilizateParametr // Структура для задания начальных параметров
{
	int isMode;
	std::string fileName;
	int idWebCam;
	int countFrame;
};

void printhelpmessege(){  // Вспомогательное сообщение
	out<<end;
	out<<"Param program"<<end;
	out<<"-w[id]        - capture video with webcamera id (default open id=0)"<<end;
	out<<"-v videofile, - open videofile"<<end;
	out<<"-c[n          - number frame detect in second (default 0, detect all frame)"<<end;
	out<<"-h,	        - print this help"<<end;
	out<<end;

}

void startInitialized(initilizateParametr* param,int argv,char** argc){  // Функция считывания стартовых параметров
	int opt=0;
	while((opt=getopt(argv,argc,"w::c::v:h")) !=-1){ // Обрабатываем параметры командной строки
		switch(opt){
			case 'w':
				try{
					param->idWebCam=std::stoi(optarg);
				}
				catch(...){
					param->idWebCam=0;
				}		
				out<<"Capture video with web camera "<<param->idWebCam<<end;		
				param->isMode=0;
    			param->fileName="";
				break;
			case 'v':
				out<<"Open video file "<<optarg<<end;
				param->isMode=1;
    			param->idWebCam=-1;
    			param->fileName=optarg;
				break;
			case 'c':
				try{
					param->countFrame=std::stoi(optarg);	
				}
				catch(...){
					param->countFrame=0;
				}
				out<<"Numb frame="<<param->countFrame<<end;			
				break;
			case 'h':
				printhelpmessege();
				break;
		}
	}

}

int main(int argv,char **argc){
	initilizateParametr param; // Стартовые параметры
	hogdescriptorrecognotion recognitionClass;  // Класс обработки
    param.isMode=0;  // Инициализация значениями по умолчани.
    param.idWebCam=0;
    param.fileName="";
    param.countFrame=0;
    startInitialized(&param,argv,argc);  // Считывание параметров консоли, при запуске
    if(param.isMode==0){  // Проверка режима работы (0-вебка, 1-видео)
    	if(!recognitionClass.incvideocapture(param.idWebCam)){ // Проверка на доступность выбраного источника
    			out<<"Faild capture video with web camera "<<param.idWebCam<<end;
    			return -1;
    	}
    }
    else if(!recognitionClass.incvideocapture(param.fileName)){
    	out<<"Faild open video file "<<param.fileName<<end;
    	return -1;
    }
	out<<"Show video"<<end;
	recognitionClass.setCountFrame(param.countFrame); //  Инициализация значения пропоска кадров
	return recognitionClass.showVideoCap();  // Запуск источника на воспроизведение
}
