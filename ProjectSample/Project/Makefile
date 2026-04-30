
# Output executable name
TARGET = program.exe

#Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c11 -Iinc #Include directory for header files

#Source and object files
SRCS = $(wildcard src/*.c) #All .c files in src directory
OBJS = $(SRCS:Project/src/%.c=Project/obj/%.o) #Object files in obj directory

#Default target
all: $(TARGET)

#Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#Compilation
Project/obj/%.o: Project/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#Clean up
clean:
	rm -f $(TARGET) $(OBJS)	
