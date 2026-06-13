CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude -MMD -MP

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

DEP = $(OBJ:.o=.d)

TARGET = biblioteca.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build:
	if not exist build mkdir build

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	.\$(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

clean:
	del /Q build\*.o 2>nul
	del /Q build\*.d 2>nul
	del /Q $(TARGET) 2>nul

-include $(DEP)

.PHONY: all run debug clean