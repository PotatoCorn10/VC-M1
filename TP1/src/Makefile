#######################################
# Makefile Image conversion           #
#                                     #
#######################################

PROG = pgmtopgm ppmtorgb ppmtopgm

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

pgmtopgm : pgmtopgm.o Utils/Util.o
ppmtorgb : ppmtorgb.o Utils/Util.o TP1/TP1_funcs.o
ppmtopgm : ppmtopgm.o Utils/Util.o TP1/TP1_funcs.o

clean :
	@rm -f *.o Utils/*.o TP1/*.o $(PROG)


