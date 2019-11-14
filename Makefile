OBJS	= Build/main.o Build/XmlParser.o tinyxml2/libtinyxml2.a
SOURCE	= Src/main.cpp tinyxml2/tinyxml2.cpp
INCLUDE	= -I tinyxml2 -I cxxopts/include -I Src
OUT		= svd2cpp
CC 		= g++
FLAGS 	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Build/main.o: Src/main.cpp
	mkdir -p Build
	$(CC) $(FLAGS) Src/main.cpp $(INCLUDE) -o Build/main.o

Build/XmlParser.o: Src/XmlParser.cpp
	mkdir -p Build
	$(CC) $(FLAGS) Src/XmlParser.cpp $(INCLUDE) -o Build/XmlParser.o

tinyxml2/libtinyxml2.a:
	$(MAKE) -C tinyxml2/ staticlib


clean:
	rm -f $(OBJS) $(OUT)

