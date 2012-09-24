# makefile configuration
SRC	=  main.cc bytequeue.c bytequeue.h lolmsg.c lolmsg.h

BINDIR = .

TARGET_PROG = test

OBJDIR = build_${TARGET_PROG}
TOBJECTS = $(SRC:%.cc=$(OBJDIR)/%.o)
OBJECTS += $(TOBJECTS:%.c=$(OBJDIR)/%.o)


IPATH = .

VPATH = .

CC = gcc
CXX = g++
CFLAGS  = -Wall -g -D_GNU_SOURCE
#CFLAGS += -arch i386
CFLAGS += ${patsubst %,-I%,${IPATH}}
CFLAGS += -ffast-math
LDFLAGS = 
#LDFLAGS = -arch i386


LIBS = 

.Phony: clean

all: mkobjectsdir $(TARGET_PROG) 

mkobjectsdir:
	mkdir -p $(OBJDIR)

$(TARGET_PROG): ${OBJECTS}
	${CXX} ${LDFLAGS} $^ -o $@

$(OBJDIR)/%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} -rf $(OBJDIR) $(TARGET_PROG)
