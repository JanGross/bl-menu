SRCDIR = src
SRCS = $(shell find $(SRCDIR) -name '*.cpp')
NAME = start
CC = g++
C_FLAGS = -w
L_FLAGS = -lSDL2 -lSDL2_image

all: $(SRCS)
	$(CC) $(SRCS) $(C_FLAGS) $(L_FLAGS) -o bin/$(NAME)
