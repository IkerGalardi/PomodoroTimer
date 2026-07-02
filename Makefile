OBJ=build/main.o build/raygui.o

CFLAGS=-Wall -Wextra -Ivendor/raylib/src -Ivendor/raygui/
LDFLAGS=-Lbuild/ -lraylib -framework Cocoa -framework OpenGL -framework IOKit

all: PomodoroTimer

PomodoroTimer: $(OBJ) build/libraylib.a
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

build/%.o: vendor/raygui/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

build/libraylib.a:
	sh scripts/prepare_raylib.sh

clean:
	rm build/*.o

cleanall:
	rm build/*.o build/libraylib.a
