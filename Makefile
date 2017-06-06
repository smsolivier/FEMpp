# compiler and flags 
CXX=g++
CFLAGS=-std=c++14
COMPILE = $(CXX) $(CFLAGS)

# main file with int main 
MAIN_SRC = testTransport.cpp
# MAIN_SRC = testSolve.cpp
MAIN_OBJ = $(subst .cpp,.o,$(MAIN_SRC))

# source files 
SRCS=Solve.cc Mesh.cc Element.cc Polynomial.cc LinearSolver.cc Transport.cc 
SRCS+=quad.cc helper.cc WriteCurve.cc 
OBJ=$(subst .cc,.o,$(SRCS))

# where to store object files 
OBJDIR = obj/

# add objdir to obj 
OBJ := $(addprefix $(OBJDIR), $(OBJ))
MAIN_OBJ := $(addprefix $(OBJDIR), $(MAIN_OBJ))

# where to store output 
DATADIR = data/

# output exectuable name 
exe = x

all: $(OBJDIR) $(exe) $(DATADIR)

$(OBJDIR) :
	mkdir $(OBJDIR)

$(DATADIR) :
	mkdir $(DATADIR)

# generate main executable 
$(exe) : $(MAIN_OBJ) $(OBJ)
	$(COMPILE) -o $(exe) $(OBJ) $(MAIN_OBJ)

# generate object from MAIN_SRC
$(MAIN_OBJ) : $(MAIN_SRC) 
	$(COMPILE) -c $< -o $@

# generate other objects 
$(OBJDIR)%.o : %.cc 
	$(COMPILE) -c $< -o $@

# clean up 
.PHONY : clean 
clean :
	rm -rf $(OBJDIR) # remove objects 
	rm -f $(exe) # remove executable 
	rm -rf $(DATADIR) # remove data directory 
	rm -rf rzzeus* # remove weird rzzeus things 