# makefile configuration
SRC	=  main.cc epuck.cc epuck_monitor.cc support.c spicomm.c utils.cc args.cc
SRC += capture.cc cmvision.cc v4l_helper.cc
SRC += ActionSequence.cc VisualMemory.cc
SRC += ActionSequence.hh VisualMemory.hh
SRC += crc16.c
SRC += bytequeue.c lolmsg.c ipc.cc

TARGET_PROG = ctrl

OBJDIR = build_$(TARGET_PROG)
TOBJECTS = $(SRC:%.cc=$(OBJDIR)/%.o)
OBJECTS = $(TOBJECTS:%.c=$(OBJDIR)/%.o)

BINDIR = .


IPATH = .
IPATH += ../
IPATH += ../utils
IPATH += ../cmvision

VPATH = .
VPATH += ../
VPATH += ../utils
VPATH += ../cmvision

CC = gcc
CXX = g++
CFLAGS  =  -Wall -g -D_GNU_SOURCE -Wno-write-strings
#CFLAGS += -DTEST
CFLAGS += -DLAPTOP
CFLAGS += ${patsubst %,-I%,${IPATH}}
CFLAGS += -ffast-math


LIBS = -lpthread

.Phony: clean

all: mkobjectsdir $(TARGET_PROG) 

mkobjectsdir:
	mkdir -p $(OBJDIR)

$(TARGET_PROG): ${OBJECTS}
	${CXX} ${CFLAGS} -o  ${BINDIR}/$@ $^ ${LIBS}

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cc
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	${RM} -rf $(OBJDIR) ${BINDIR}/$(TARGET_PROG)
