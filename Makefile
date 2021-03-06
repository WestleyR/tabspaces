# Created by: WestleyR
# email: westleyr@nym.hush.com
# Date: Apr 26, 2019
# https://github.com/WestleyR/tabspaces
# version-1.0.2
#
# The Clear BSD License
#
# Copyright (c) 2019 WestleyR
# All rights reserved.
#
# This software is licensed under a Clear BSD License.
#

# where to install
PREFIX = /usr/local/bin

# your c compiler
CC = gcc

# Pass the 'make STATIC=1' to use the '-static' flag
STATIC = 0
STATIC_FLAG = -static

MAN_PREFIX = /usr/share/man/man1

DEP_FLAG = -I deps
CFLAGS = -Wall
LDFLAGS =

TARGET = tabspaces
SRCDIR = src
DEPDIR = deps

MANPAGE = man/man1/tabspaces.1.gz

# Check if user passed the STATIC=1 flag
ifeq ($(STATIC),1)
	CFLAGS += $(STATIC_FLAG)
endif

SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)

OBJS = $(SRC:.c=.o)

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

.PHONY:
%.o: %.c
	$(CC) $(DEP_FLAG) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY:
clean:
	-git clean -e $(TARGET) -fx
	rm -f $(OBJS)

.PHONY:
cleanall:
	-git clean -fx
	rm -f $(TARGET) $(OBJS)

.PHONY:
install: $(TARGET)
	cp -f $(TARGET) $(PREFIX)

.PHONY:
test: $(TARGET)
	./tests/tests-sh

.PHONY:
uninstall: $(PREFIX)/$(TARGET)
	rm -f $(PREFIX)/$(TARGET)

#
# End Makefile
#