# CC and CFLAGS are varilables
CC = g++
# CFLAGS = -c
# AR = ar
# ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
# DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: src/main.cpp 
			$(CC) $(OPTFLAGS) src/main.cpp  -o bin/mps
# main.o 	   	: src/main.cpp 
# 			$(CC) $(CFLAGS) $< -o $@
# maxPlanarSubset.o	: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
# 			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@


# clean all the .o and executable files
clean:
		rm -rf *.o bin/*

