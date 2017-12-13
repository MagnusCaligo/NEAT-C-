CC = g++
CFLAGS = -std=c++17 -I. 
OBJDIR = ./obj
SRCDIR = ./src
INCDIR = ./include
CXXFLAGS := -std=c++11

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY:  main 

#all: clean main

main : $(OBJ)
	$(CC) $^  -I $(INCDIR) -o $@ $(CFLAGS) 

$(OBJ) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(info value is $<)
	$(CC) $(SRCDIR)/$(basename $(notdir $@)).cpp -I $(INCDIR) -o $@  $(CFLAGS) -c

clean:
	rm $(OBJ) main

