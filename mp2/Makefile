# ___________________________________________

# ___________________________________________

#
# Object files are listed here
#
OBJS = mp2.o mountain.o plane.o

#
# EXE name goes here
#
EXENAME = mp2

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
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) -lglut

#
# Compiles object files.
#
mp2.o : mp2.cpp
	$(CC) $(CCOPTS) mp2.cpp
mountain.o : mountain.cpp 
	$(CC) $(CCOPTS) mountain.cpp
plane.o : plane.cpp
	$(CC) $(CCOPTS) plane.cpp
	

clean : 
	rm -f *.o $(EXENAME) 2>/dev/null


