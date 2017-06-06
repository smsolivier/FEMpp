# compiler and flags 
CXX=g++
CFLAGS=-std=c++14
COMPILE = $(CXX) $(CFLAGS)

# main file with int main 
MAIN_SRC =
MAIN_OBJ = $(subst .cpp,.o,$(MAIN_SRC))

# source files 
SRCS=Solve.cc Mesh.cc Element.cc Polynomial.cc quad.cc
SRCS+=Transport.cc
OBJ=$(subst .cc,.o,$(SRCS))

# output exectuable name 
exe = x

all: $(exe)

# generate main executable 
$(exe) : $(MAIN_OBJ) $(OBJ)
	$(COMPILE) -o $(exe) $(OBJ) $(MAIN_OBJ)

# generate object from MAIN_SRC
$(MAIN_OBJ) : $(MAIN_SRC) 
	$(COMPILE) -c $<

# generate other objects 
%.o : %.cc 
	$(COMPILE) -c $< 

# clean up 
.PHONY : clean 
clean :
	rm -f $(OBJ) 
	rm -f $(MAIN_OBJ)
	rm -f $(exe) 