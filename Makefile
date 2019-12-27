CXX_OBJS = \
	source/main.o \
    source/engine/engine.o \
	source/gl/buffer.o \
	source/gl/shader.o \
	source/gl/texture.o \
	source/gl/vertexarray.o \
	source/graphics/bgtexture.o \
	source/graphics/spritetexture.o \
	source/loader/bitmap.o \
    source/render/renderer.o \
    source/render/glcontext.o \
	source/system/window.o \

CXX=g++
INCLUDE += include/
CXXFLAGS += -DDEBUG
CXXFLAGS +=-std=c++14 -Wall -Wextra -Wold-style-cast -Wsign-compare -Wfloat-equal -g -ggdb
CXXFLAGS += -I$(INCLUDE)

ifeq ($(OS),Windows_NT)
    $(error Windows is currently not supported! You'll have to modify the Makefile yourself!)
else
    CXXFLAGS += -I/usr/include
endif

BINDIR=bin
BINARY=kiuta

all: $(BINARY)

$(BINARY): $(CXX_OBJS)
	@rm -rf $(BINDIR)
	@mkdir $(BINDIR)
	@echo "LINKING $@"; $(CXX) -o $(BINDIR)/$@ $(CXX_OBJS) -rdynamic -lGL -lSDL2 -lGLEW

.cpp.o:
	@echo "CXX $@"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "Cleaning Project..."; rm -rf $(BINDIR) $(CXX_OBJS)



