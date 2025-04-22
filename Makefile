CC = gcc
EXEC = calc
CFLAGS = -Wall -Wextra -MMD -MP -Isrc/include
LDFLAGS = -lm

ifeq ($(DEBUG),1)
    CFLAGS += -g -DDEBUG -Og
else
    CFLAGS += -O2
	LDFLAGS += -s
endif

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS) $(DEPENDS)

.PHONY: all clean

-include $(DEPENDS)
