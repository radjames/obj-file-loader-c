
main: main.c modelview.o lists.o loadstuff.o
	gcc main.c modelview.o lists.o loadstuff.o -lglfw -lOpenGL -lGLEW -lm -lgl-matrix -o a -g 
	./a 

modelview: modelview.c modelview.h lists.o 
	gcc -c modelview.c -o modelview.o -g 

lists: lists.c lists.h 
	gcc lists.c -o lists.o -g 

loadstuff: loadstuff.c loadstuff.h
	gcc loadstuff.c -o loadstuff.o -lglfw -lOpenGL -lGLEW -lgl-matrix -g 
