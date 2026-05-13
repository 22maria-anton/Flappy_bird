# Compiler și flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lraylib -lm

# Fișiere sursă și obiecte
SOURCES = main.c game.c graphics.c ui.c score.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = flappy_bird

# Target implicit
all: $(EXECUTABLE)

# Link
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compilare
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Curățare
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Rebuild
rebuild: clean all

# Rulare
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean rebuild run
