#####################
# Makefile K Means  #
#####################

PROG = kmeans

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

kmeans : kmeans.o Utils/Util.o TP5/TP5_funcs.o

clean :
	@rm -f *.o Utils/*.o TP5/*.o $(PROG)


