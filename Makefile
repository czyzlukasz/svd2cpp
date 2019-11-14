OBJS	= Build/main.o tinyxml2/tinyxml2.o
SOURCE	= Src/main.cpp tinyxml2/tinyxml2.cpp
HEADER	= tinyxml2/tinyxml2.h
OUT		= svd2cpp
CC 		= g++
FLAGS 	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Build/main.o: Src/main.cpp
	mkdir -p Build
	$(CC) $(FLAGS) Src/main.cpp -o Build/main.o

tinyxml2/tinyxml2.o:
	$(MAKE) -C tinyxml2/make staticlib


clean:
	rm -f $(OBJS) $(OUT)

