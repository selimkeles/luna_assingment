# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -I./libs -I./libs/3rdPartyLibs -Wall

# Libraries
LIBS = -L./libs/3rdPartyLibs -lmeter

# Source Files
SRCS = main.c $(wildcard ./src/*.c) $(wildcard ./libs/*.c) $(wildcard ./libs/3rdPartyLibs/*.c)

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable Name
EXEC = luna_assignment

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
