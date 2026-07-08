OS=$(shell uname)

OBJ=build/main.o build/raygui.o
DEP=build/main.d build/raygui.d

CFLAGS=-Wall -Wextra -Ivendor/raylib/src -Ivendor/raygui/ -MMD -O2
LDFLAGS=-Lbuild/ -lraylib

ifeq ($(OS),Darwin)
	include macos.mk
endif

ifeq ($(OS),Linux)
	include linux.mk
endif

all: PomodoroTimer

PomodoroTimer: $(OBJ) build/libraylib.a
	$(CC) -o $@ $< $(LDFLAGS)

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

icon.icns: res/icon.png
	vendor/png_to_icns/png_to_icns.sh -i res/icon.png

install_macos: PomodoroTimer icon.icns
	rm -rf $(HOME)/Applications/PomodoroTimer.app
	mkdir -p $(HOME)/Applications/PomodoroTimer.app
	mkdir -p $(HOME)/Applications/PomodoroTimer.app/Contents
	mkdir -p $(HOME)/Applications/PomodoroTimer.app/Contents/MacOS
	mkdir -p $(HOME)/Applications/PomodoroTimer.app/Contents/Resources
	cp res/Info.plist $(HOME)/Applications/PomodoroTimer.app/Contents/
	cp PomodoroTimer $(HOME)/Applications/PomodoroTimer.app/Contents/MacOS
	cp res/ring.mp3 $(HOME)/Applications/PomodoroTimer.app/Contents/Resources
	cp res/noise.mp3 $(HOME)/Applications/PomodoroTimer.app/Contents/Resources
	cp icon.icns $(HOME)/Applications/PomodoroTimer.app/Contents/Resources

install_linux: PomodoroTimer
	rm -rf /opt/PomodoroTimer
	mkdir /opt/PomodoroTimer/
	cp PomodoroTimer /opt/PomodoroTimer/
	cp res/ring.mp3 /opt/PomodoroTimer/
	cp res/noise.mp3 /opt/PomodoroTimer/
	cp res/icon.png /opt/PomodoroTimer/
	cp res/PomodoroTimer.desktop /usr/share/applications/
