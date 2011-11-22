# Makefile

SRCDIR = .
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

SHELL = /bin/sh
CC = g++
INSTALL = /usr/bin/install -c

CFLAGS = -Wall -O2
LDFLAGS = 
CDEBUG = -g -O0 -DDEBUG

.SUFFIXES:
.SUFFIXES: .cpp .o

SRCS = $(SRCDIR)/ADTList.cpp $(SRCDIR)/DoublyLinkedList.cpp \
       $(SRCDIR)/LongInt.cpp $(SRCDIR)/main.cpp \
       $(SRCDIR)/Node.cpp
OBJS = $(SRCS:.cpp=.o)
LIBS =
AUX =

.PHONY: all
all: bmoial

.PHONY: debug
debug: CFLAGS += $(CDEBUG)
debug: LDFLAGS += $(CDEBUG)
debug: all

bmoial: $(OBJS)
	$(CC) $(LDFLAGS) -o"$@" $(LIBS) $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) bmoial

.PHONY: install
install: all
	$(INSTALL) bmoial $(BINDIR)/bmoial
