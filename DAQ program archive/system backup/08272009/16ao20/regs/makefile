# $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/regs/makefile $
# $Rev: 2014 $
# $Date: 2009-05-19 12:39:09 -0500 (Tue, 19 May 2009) $

CC			= gcc
CC_FLAGS	= -c -Wall
CC_FLAGS	+= -I.
CC_FLAGS	+= -I../driver
CC_FLAGS	+= -I../utils
CC_FLAGS	+= -I../docsrc
DEP_FILE	= makefile.dep
LIB_FILES	:=
TARGET		= regs

default:	all
DSL_DIR		:= ../docsrc
include	${DSL_DIR}/makefile.inc
UTIL_DIR	:= ../utils
include	${UTIL_DIR}/makefile.inc

OBJ_FILES	=			\
			main.o		\
			main_menu.o	\
			menu.o		\
			reg.o



.c.o:
	@echo == Compiling: $<
	@-chmod +rw ${DEP_FILE}
	@# Get the dependency list for this module.
	@-${CC} -MM ${CC_FLAGS} $< > .tmp1
	@# Remove the trailing white space and backslash.
	@-sed -e "s/[ ]*[\\\\]//g" < .tmp1 > .tmp2
	@# Put everything on seperate lines.
	@-tr [:space:] \\n < .tmp2 > .tmp3
	@# Remove all of the system include files.
	@-grep -v "^[ ]*/" < .tmp3 > .tmp4
	@# Remove all empty lines.
	@-grep [[:alnum:]] < .tmp4 > .tmp5
	@# Put everything on the same line.
	@-tr '\n' '\040' < .tmp5 > .tmp6
	@-echo -e '\012' >> .tmp6
	@# Add all of the other dependencies to the end of this file.
	@-echo >> ${DEP_FILE}
	@-grep -v "^[ ]*$@" < ${DEP_FILE} >> .tmp6
	@# Remove blank lines from the list.
	@-grep "[[:alnum:]]" < .tmp6 > .tmp7
	@# Sort the list and put it in the dependency file.
	@-sort < .tmp7 > ${DEP_FILE}
	@# Cleanup.
	@rm -f ${DEP_FILE}.tmp* .tmp*
	@# Compile the module.
	@${CC} ${CC_FLAGS} $< -o $@



all: ${GSC_UTIL_SOURCES} ${TARGET}
	@echo ==== All Done

release: ${GSC_UTIL_SOURCES} ${TARGET}
	@rm -f *.a *.o ${REL_CLEAN}
	@echo ==== Release Done

${TARGET}: ${GSC_UTIL_SOURCES} ${LIB_FILES} ${OBJ_FILES}
	@echo ==== Linking: $@
	@${CC} ${OBJ_FILES} ${LIB_FILES} -o $@

clean::
	@echo ==== Cleaning ${TARGET} ...
	@rm -f *.a *.o *.scc ${TARGET} ${REL_CLEAN}
	@-chmod +rw ${DEP_FILE}
	@echo > ${DEP_FILE}

${DEP_FILE}:
	@echo ==== Creating: $@
	@echo > ${DEP_FILE}

include ${DEP_FILE}
