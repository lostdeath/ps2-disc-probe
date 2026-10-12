CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
all: disc-probe
disc-probe: src/disc_probe.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f disc-probe
.PHONY: all clean
