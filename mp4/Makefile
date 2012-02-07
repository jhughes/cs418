# ___________________________________________

# ___________________________________________

#
# Object files are listed here
#
OBJS = mp4.o I.o particle.o helpers.o

#
# EXE name goes here
#
EXENAME = mp4

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
mp4.o : mp4.cpp
	$(CC) $(CCOPTS) mp4.cpp
I.o : I.cpp
	$(CC) $(CCOPTS) I.cpp
particle.o : particle.cpp
	$(CC) $(CCOPTS) particle.cpp
helpers.o : helpers.cpp 
	$(CC) $(CCOPTS) helpers.cpp

clean : 
	rm -f *.o $(EXENAME) 2>/dev/null


