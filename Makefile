# Compiler
CC = gcc

# Output binary
TARGET = game

# Source files
SRC = main.c

# Compiler flags
CFLAGS = -Wall -Wextra -O2

# Raylib flags (adjust paths if raylib is installed elsewhere)
RAYLIB_FLAGS = -lraylib -lm -lpthread -ldl -lrt -lX11

# ─── Targets ────────────────────────────────────────────────────────────────

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(RAYLIB_FLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean