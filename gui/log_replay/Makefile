# makefile configuration
SRC	=  log_replay.cc canvas.cc imagebox.cc utils.cc

TARGET_PROG = log_replay

OBJDIR = build_$(TARGET_PROG)
OBJECTS = $(SRC:%.cc=$(OBJDIR)/%.o)

BINDIR = .

IPATH = .
IPATH += ../../

VPATH = .

CC = g++
CFLAGS  = -O2 -Wall -g -D_GNU_SOURCE 
#CFLAGS +=-DLAPTOP
#CFLAGS  = -O2 -Wall -g -D_GNU_SOURCE -DLAPTOP
#CFLAGS += -DTRANSFER_RGB
CFLAGS += ${patsubst %,-I%,${IPATH}}
CFLAGS +=`fltk-config --cflags`

LIBS = 
LIBS += `fltk-config --ldflags --libs`

#FFMPEG_LIBS=libavdevice libavformat libavfilter libavcodec libswscale libavutil
#CFLAGS+=$(shell pkg-config  --cflags $(FFMPEG_LIBS))
#LIBS+=$(shell pkg-config --libs $(FFMPEG_LIBS))


.Phony: clean

all: mkobjectsdir $(TARGET_PROG) 

mkobjectsdir:
	mkdir -p $(OBJDIR)

$(TARGET_PROG): ${OBJECTS}
	${CC} ${CFLAGS} -o  ${BINDIR}/$@ $^ ${LIBS}



$(OBJDIR)/%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} -rf $(OBJDIR) ${BINDIR}/$(TARGET_PROG)
