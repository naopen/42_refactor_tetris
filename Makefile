# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 20:46:50 by nkannan           #+#    #+#              #
#    Updated: 2024/02/04 21:05:22 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g

# Header files directory
INCLUDES := -I./

# Source files
SOURCES := main.c game.c board.c shapes.c input.c render.c utils.c

# Object files
OBJECTS := $(SOURCES:.c=.o)

# Executable name
EXECUTABLE := tetris

# Default target
all: $(EXECUTABLE)

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -lncurses

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# .PHONY to indicate that 'clean' isn't a file
.PHONY: clean

# Clean up build artifacts
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
