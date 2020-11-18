# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: src/main.cpp 
			$(CC) $(OPTFLAGS) src/main_stable.cpp  -o bin/mps
# main.o 	   	: src/main.cpp 
# 			$(CC) $(CFLAGS) $< -o $@
# maxPlanarSubset.o	: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
# 			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# DEBUG Version
dbg : bin/mps_dbg
	@echo -n ""

bin/NTU_sort_dbg	: sort_tool_dbg.o main_dbg.o lib
			$(CC) $(DBGFLAGS) sort_tool_dbg.o main_dbg.o -ltm_usage -Llib -o bin/NTU_sort_dbg
main_dbg.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
sort_tool_dbg.o	: src/sort_tool.cpp src/sort_tool.h
			$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@


# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

