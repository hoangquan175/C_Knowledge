
# Output executable name
TARGET = program.exe

#Compiler and flags
CC = gcc
CFLAGS = -Wall -g -std=c11 -Iinc #Include directory for header files

#Source and object files		
SRCS = $(wildcard src/timer_interval.c) #All .c files in src directory
OBJS = $(SRCS:src/%.c=obj/%.o) #Object files in obj directory

#Default target
all: obj $(TARGET)

#Create obj directory
obj:
	mkdir -p obj

#Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#Compilation
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#Clean up
clean:
	rm -f $(TARGET) $(OBJS)
	rmdir obj 2>/dev/null || true	