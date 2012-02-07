# ___________________________________________

# ___________________________________________

#
# Object files are listed here
#
OBJS = mp1.o

#
# EXE name goes here
#
EXENAME = mp1

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
mp1.o : mp1.cpp 
	$(CC) $(CCOPTS) mp1.cpp
	

clean : 
	rm -f *.o $(EXENAME) 2>/dev/null


