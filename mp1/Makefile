# ___________________________________________

# ___________________________________________

#
# Object files are listed here
#
OBJS = plotter.o

#
# EXE name goes here
#
EXENAME = plotter

#
# Macro assignments
#
CC = gcc
CCOPTS = -c -g -O0 -Wall 
LINK = gcc
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
plotter.o : plotter.c
	$(CC) $(CCOPTS) plotter.c
	

clean : 
	rm -f *.o $(EXENAME) 2>/dev/null


