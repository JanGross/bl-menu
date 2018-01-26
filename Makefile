OBJS = main.cpp menu_entry.cpp
NAME = start
CC = g++
C_FLAGS = -w
L_FLAGS = -lSDL2 -lSDL2_image

all: $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) $(L_FLAGS) -o $(NAME)
