CC = g++
CFLAGS = -std=c++11 -I. 
OBJDIR = ./obj
SRCDIR = ./src
INCDIR = ./include
CXXFLAGS := -std=c++11

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: main $(OBJ)

main : $(OBJ)
	$(CC) $^  -I $(INCDIR) -o $@ $(CFLAGS) 

$(OBJ) : 
	$(CC) $(SRCDIR)/$(basename $(notdir $@)).cpp -I $(INCDIR) -o $@ $< $(CFLAGS) -c

clean:
	rm $(OBJ) main

