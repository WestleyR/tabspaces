# Created by: WestleyR
# email: westleyr@nym.hush.com
# Date: Apr 20, 2019
# https://github.com/WestleyR/tabspaces
# version-1.0.1
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

MAN_PREFIX = /usr/share/man/man1

DEP_FLAG = -I deps
CFLAGS = -Wall
LDFLAGS =

TARGET = tabspaces
SRCDIR = src
DEPDIR = deps

MANPAGE = man/man1/tabspaces.1.gz

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
	rm -f $(OBJS)

.PHONY:
cleanall:
	rm -f $(OBJS) $(TARGET)

.PHONY:
install: $(TARGET)
	cp -f $(TARGET) $(PREFIX)

#
# End Makefile
#