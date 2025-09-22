#######################################
# Makefile Project Points             #
#                                     #
#######################################

PROG = project_points

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

project_points : project_points.o Utils/Util.o Utils/imageFormationUtils.o -lm

clean :
	@rm -f *.o Utils/*.o $(PROG)
