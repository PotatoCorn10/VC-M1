################################
# Makefile Gradients & Canny   #
################################

PROG = displayGradientMagnitudes cannyEdges

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g 

displayGradientMagnitudes : displayGradientMagnitudes.o Utils/Util.o Utils/filters.o TP4/gradients.o -lm
cannyEdges: cannyEdges.o Utils/Util.o Utils/filters.o TP4/gradients.o TP4/canny.o -lm


clean :
	@rm -f *.o Utils/*.o TP4/*.o $(PROG)
