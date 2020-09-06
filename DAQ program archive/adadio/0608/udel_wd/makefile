
CC		= gcc
CC_FLAGS	= -c -Wall 
CC_FLAGS	+= -I.
CC_FLAGS	+= -I../udel_comm
LIB_FILES	:= -lm -lX11
TARGET		= udel_wd
OBJ_FILES	= ../udel_comm/udel_daq.o

all: kirk spock shmdemo dispdemo sw shmclear


.c.o:
	${CC} ${CC_FLAGS} $< -o $@

#dispdemo: dispdemo.o ../udel_comm/udel_daq.o
#	${CC} $^  ${LIB_FILES} -o $@

shmclear.o: shmclear.c
	${CC} ${CC_FLAGS} $< -o $@
%: %.o ../udel_comm/udel_daq.o
	${CC} $^ ${LIB_FILES} -o $@

../udel_comm/udel_daq.o: ../udel_comm/udel_daq.h

#${TARGET}: ${OBJ_FILES}
#	${CC} ${OBJ_FILES} ${LIB_FILES} -o $@
