.PHONY : all clean install

CPPFLAGS = -c -std=c++14 -O1 -fno-rtti

all: libbgi.a libconio2.a

install:
	copy /y *.a ..\..\lib
	copy /y coniow.h ..\..\include
	copy /y keys_n_colors.h ..\..\include
	copy /y winbgim.h ..\..\include
	copy /y graphics.h ..\..\include

clean:
	-del *.o  
	-del libbgi.a
	-del libconio2.a

libbgi.a: drawing.o misc.o mouse.o palette.o text.o winbgi.o winthread.o file.o dibutil.o image.o winbgim.h graphics.h
	ar -rv libbgi.a drawing.o misc.o mouse.o palette.o text.o winthread.o winbgi.o file.o image.o dibutil.o 
	ranlib libbgi.a

libconio2.a: coniow.o coniow.h
	ar -rv libconio2.a coniow.o
	ranlib libconio2.a

drawing.o: drawing.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) drawing.cpp

misc.o: misc.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) misc.cpp

coniow.o: coniow.c coniow.h
	gcc -O1 -c coniow.c

mouse.o: mouse.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) mouse.cpp

palette.o: palette.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) palette.cpp

text.o: text.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) text.cpp

winbgi.o: winbgi.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) winbgi.cpp

winthread.o: winthread.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) winthread.cpp

image.o: image.cpp winbgim.h winbgitypes.h
	g++ $(CPPFLAGS) image.cpp

dibutil.o: dibutil.cpp dibutil.h dibapi.h
	g++ $(CPPFLAGS) dibutil.cpp

file.o: file.cpp dibutil.h dibapi.h winbgitypes.h
	g++ $(CPPFLAGS) file.cpp

