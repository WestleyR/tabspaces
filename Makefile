# Created by: WestleyR
# email: westleyr@nym.hush.com
# Date: Apr 1, 2019
# https://github.com/WestleyR/tabspaces
# version-1.0.0
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

MAN_PREFIX = /usr/share/man/man1

# your c compiler
CC = gcc

DEPFLAG = -I deps
CFLAG = -Wall
LDFLAGS =

TARGET = tabspaces
SRCDIR = src
DEPDIR = deps

SRC = $(wildcard $(SRCDIR)/*.c)
DEP = $(wildcard $(DEPDIR)/*/*.c)

ALLFILE = $(notdir $(SRC) $(DEP))
OBJS = $(ALLFILE:.c=.o)

MANPAGE = man/man1/tabspaces.1.gz

.PHONY:
all: $(TARGET)

.PHONY:
$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS) $(LDFLAGS)

.PHONY:
$(OBJS): $(SRC)
	$(foreach srcfile, $(SRC), $(CC) $(DEPFLAG) $(CFLAG) -c $(srcfile);)
	$(foreach depfile, $(DEP), $(CC) $(DEPFLAG) $(CFLAG) -c $(depfile);)

.PHONY:
clean:
	rm -f main-tabspaces.o tabs-spaces.o arglib.o logger.o spaces-tabs.o c-utils.o

.PHONY:
test: $(TARGET)
	./tests

.PHONY:
install: $(TARGET)
	cp -f $(TARGET) $(PREFIX)
	-cp -f $(MANPAGE) $(MAN_PREFIX)

.PHONY:
cleanall:
	-rm -f *.o
	-rm -f tabspaces

#
# End Makefile
#
