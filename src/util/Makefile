# Makefile for recursive recognition control

LD_OBJ     = ../../obj
BIN        = ./bin
OBJ        = ./obj
SRC        = ./src
HDR        = ./hdr

CC         =  gcc
DEFINES    =
OPT        = -O
DEBUG_OPT  = -DDEBUG
CFLAGS     = $(DEFINES) $(OPT)
LD_OPTS    =

INCLUDES   = -I$(HDR) -I../ -I../../hdr/ -I/util/include -I/util/X11/include -I/usr/include/mysql
LIBS       = -lm -lmysqlclient

SRCS       = $(SRC)/sensor_data.c \
						 $(SRC)/databases.c

OBJS       = $(OBJ)/sensor_data.o \
						 $(OBJ)/databases.o

all: $(OBJS) $(SRCS) Makefile
	ld $(LD_OPTS) -r -o $(LD_OBJ)/util.o $(OBJS)
	cp hdr/*.h ../../hdr/

$(OBJ)/%.o:$(SRC)/%.c
	${CC} ${CFLAGS} $(INCLUDES) -c $(SRC)/${*F}.c -o $(OBJ)/${*F}.o ${LIBS}

clean:
	-rm -f *.a core $(OBJS)

depend:
	makedepend -- $(CFLAGS) $(INCLUDES) -- $(SRCS)
