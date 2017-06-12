# generic crap makefile for C++ trash projects

CC = g++
CFLAGS = -g -Wall -std=c++11 -I$(INCDIR) -L$(LIBDIR)
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

SRCDIR = src/
INCDIR = include/
BINDIR = bin/
OBJDIR = obj/
LIBDIR = lib/

OUTFILE = $(BINDIR)main
OUTSRCFILE = $(SRCDIR)actualProgramTest.cpp

OBJFILES_NODIR = sdlbox SDLBox Font Color GraphicsHelper Label Texture Component Panel Button EventListener

OBJFILES = $(addprefix $(OBJDIR),$(OBJFILES_NODIR:=.o))

.PHONY: all clean init

all: $(OUTFILE)

$(OUTFILE): $(OUTSRCFILE) $(OBJFILES)
	$(CC) $(CFLAGS) $< $(OBJFILES) $(LIBS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

clean:
	rm obj/* bin/*

init:	mkdir src bin include lib obj
