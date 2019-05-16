CC=g++
LFLAGS=-L /usr/local/lib/ `cat list`
CFLAGS=
INCLUDE=-I /usr/local/include/opencv4/
SOURCE=main.cpp hogdescriptorclass.cpp
OBJECT=$(SOURCE:.cpp=.o)
TAGET=hogdescriptor

all: $(TAGET) cleano

$(TAGET): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $@ $(LFLAGS)

$(OBJECT): $(SOURCE)
	$(CC)  $(CFLAGS) $(INCLUDE) $(SOURCE) -c

.PHONY: clean

cleano:
	rm -fr *.o

clean:
	rm -fr *.o
	rm -fr $(TAGET)