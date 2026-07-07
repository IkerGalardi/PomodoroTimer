OBJ=build/main.o build/raygui.o
DEP=build/main.d build/raygui.d

CFLAGS=-Wall -Wextra -Ivendor/raylib/src -Ivendor/raygui/ -MMD
LDFLAGS=-Lbuild/ -lraylib -framework Cocoa -framework OpenGL -framework IOKit

all: PomodoroTimer

PomodoroTimer: $(OBJ) build/libraylib.a
	$(CC) $(LDFLAGS) -o $@ $<

build/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

build/%.o: vendor/raygui/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

build/libraylib.a:
	sh scripts/prepare_raylib.sh

run: PomodoroTimer
	./PomodoroTimer

clean:
	rm -f build/*.o build/*.d

cleanall:
	rm build/*.o build/*.d build/libraylib.a

-include $(DEP)
