#######################################
# Makefile Image conversion           #
#                                     #
#######################################

PROG = smoothimage medianfilter createhistogram histogramstretching histogramequalization

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

smoothimage : smoothimage.o Utils/Util.o TP3/filters.o
medianfilter : medianfilter.o Utils/Util.o TP3/filters.o
createhistogram : createhistogram.o Utils/Util.o TP3/histogram.o
histogramstretching : histogramstretching.o Utils/Util.o TP3/histogram.o
histogramequalization : histogramequalization.o Utils/Util.o TP3/histogram.o



clean :
	@rm -f *.o Utils/*.o TP3/*.o $(PROG)


