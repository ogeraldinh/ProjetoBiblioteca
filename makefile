CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude -MMD -MP

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

ifeq ($(OS),Windows_NT)

    TARGET = biblioteca.exe
    MKDIR = if not exist build mkdir build
    RM = del /Q
    RUN = .\biblioteca.exe

else

    TARGET = biblioteca
    MKDIR = mkdir -p build
    RM = rm -f
    RUN = ./biblioteca

endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build:
	$(MKDIR)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(RUN)

debug: $(TARGET)
	gdb $(TARGET)

clean:
ifeq ($(OS),Windows_NT)
	$(RM) build\*.o 2>nul
	$(RM) build\*.d 2>nul
	$(RM) $(TARGET) 2>nul
else
	rm -f build/*.o
	rm -f build/*.d
	rm -f $(TARGET)
endif

-include $(DEP)

.PHONY: all run debug clean