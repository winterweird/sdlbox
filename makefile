# generic crap makefile for C++ trash projects

CC = g++
CFLAGS = -g -Wall -std=c++11 -I$(INCDIR) -L$(LIBDIR)
LIBS = -lsdlbox -lSDL2 -lSDL2_ttf -lSDL2_image -lpthread

SRCDIR = src/
INCDIR = include/
BINDIR = bin/
OBJDIR = obj/
LIBDIR = lib/

SDLBOX_LIB = libsdlbox.a

OUTFILE = $(BINDIR)main
OUTSRCFILE = $(SRCDIR)tests/flappyBirdTestGame.cpp

OBJFILES_NODIR = sdlbox SDLBox Font Color GraphicsHelper Label Texture Component Panel Button EventListener TextureComponent UserEvents Textual VolatileLabel Room Rooms

OBJFILES = $(addprefix $(OBJDIR),$(OBJFILES_NODIR:=.o))

.PHONY: all clean init

all: $(OUTFILE)

$(OUTFILE): $(OUTSRCFILE) $(LIBDIR)$(SDLBOX_LIB)
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@

$(LIBDIR)$(SDLBOX_LIB): $(OBJFILES)
	ar cr $@ $(OBJFILES)

clean:
	-rm obj/* bin/*

init:
	-mkdir src bin include lib obj res
