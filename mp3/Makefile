# ___________________________________________

# ___________________________________________

#
# Object files are listed here
#
OBJS = mp3.o teapot.o cube.o helpers.o obj_parser.o objLoader.o string_extra.o list.o

#
# EXE name goes here
#
EXENAME = mp3

#
# Macro assignments
#
CC = g++
CCOPTS = -c -g -O0 -Wall
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

#
# The main compiling step, using all macros.
#
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) -lglut -lGLEW

#
# Compiles object files.
#
mp3.o : mp3.cpp
	$(CC) $(CCOPTS) mp3.cpp
teapot.o : teapot.cpp 
	$(CC) $(CCOPTS) teapot.cpp
cube.o : cube.cpp
	$(CC) $(CCOPTS) cube.cpp
helpers.o : helpers.cpp 
	$(CC) $(CCOPTS) helpers.cpp
obj_parser.o : obj_parser.cpp 
	$(CC) $(CCOPTS) obj_parser.cpp
objLoader.o : objLoader.cpp 
	$(CC) $(CCOPTS) objLoader.cpp	
string_extra.o : string_extra.cpp 
	$(CC) $(CCOPTS) string_extra.cpp	
list.o : list.cpp 
	$(CC) $(CCOPTS) list.cpp	

clean : 
	rm -f *.o $(EXENAME) 2>/dev/null


