OBJ=build/main.o

CFLAGS=-Wall -Wextra

all: PomodoroTimer

PomodoroTimer: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $^
