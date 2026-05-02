CFLAGS := $(shell sdl2-config --cflags) -Iinclude
LIBS := $(shell sdl2-config --libs)

SRCS := src/main.c src/globals.c src/input.c src/player.c src/render.c

all: raycast

raycast: $(SRCS)
	gcc $(SRCS) -o program $(CFLAGS) $(LIBS) -lm

clean:
	rm -f program
