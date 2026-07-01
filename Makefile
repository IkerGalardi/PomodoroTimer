OBJ=build/main.o

CFLAGS=-Wall -Wextra -Ivendor/raylib/src
LDFLAGS=-Lbuild/ -lraylib -framework Cocoa -framework OpenGL -framework IOKit

all: PomodoroTimer

PomodoroTimer: $(OBJ) build/libraylib.a
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
