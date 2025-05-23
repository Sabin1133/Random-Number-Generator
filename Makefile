CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

INCLUDEDIR = include
SRCDIR = src
LIBDIR = lib
BUILDDIR = build

TARGETSOURCE := $(SRCDIR)/main.c
TARGETELF    := $(TARGETSOURCE:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
TARGETHEX    := $(TARGETSOURCE:$(SRCDIR)/%.c=$(BUILDDIR)/%)

SOURCES := $(filter-out $(TARGETSOURCE), $(shell find $(SRCDIR) -name '*.c'))
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

LIBSOURCES := $(shell find $(LIBDIR) -name '*.c')
LIBOBJECTS := $(patsubst $(LIBDIR)/%.c, $(BUILDDIR)/%.o, $(LIBSOURCES))

PORT ?= /dev/ttyUSB0


all: $(TARGETHEX)

upload: $(TARGETHEX)
	avrdude -c arduino -P $(PORT) -b 115200 -p atmega328p -D -U flash:w:$<:a
	rm $(TARGETHEX)

$(TARGETHEX): $(TARGETELF)
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $(TARGETELF)
	rm $(TARGETELF)

$(TARGETELF): $(TARGETSOURCE) $(SOURCES)
	avr-gcc -mmcu=atmega328p -DF_CPU=12000000 -Os -Wall -o $@ $^

$(LIBOBJECTS): $(BUILDDIR)/%.o: $(LIBDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c -o $@ $^

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c -o $@ $^

clean:
	rm -rf $(BUILDDIR)

.PHONY: all upload
