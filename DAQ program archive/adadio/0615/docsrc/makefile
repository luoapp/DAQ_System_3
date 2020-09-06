# $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/docsrc/makefile $
# $Rev: 1620 $
# $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

# Makefile for the ADADIO documentation sources

default: all

include makefile.inc

CC			= gcc
CC_FLAGS	= -c -Wall -I. -I../driver
DEP_FILE	= makefile.dep
TARGET		= ${DOCSRC_TARGET}



.c.o:
	@echo == Compiling: $<
	@-chmod +rw ${DEP_FILE}
	@# Get the dependency list for this module.
	@-${CC} -MM ${CC_FLAGS} $< >  .tmp1
	@# Remove trailing white space and backslash, if present.
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
	@# Add all the other dependencies to the end of this file.
	@-echo >> ${DEP_FILE}
	@-grep -v "^[ ]*$@" < ${DEP_FILE} >> .tmp6
	@# Remove blank lines from the list.
	@-grep "[[:alnum:]]" < .tmp6 > .tmp7
	@# Sort the list and put it in the dependency file.
	@-sort < .tmp7 > ${DEP_FILE}
	@# Cleanup.
	@rm -f .tmp*
	@# Compile the module.
	@${CC} ${CC_FLAGS} $< -o $@



all: ${TARGET}
	@echo ==== All Done

release: ${TARGET}
	@rm -f *.o
	@echo ==== Release Done

${DEP_FILE}:
	@echo ==== Creating: $@
	@echo > ${DEP_FILE}

include ${DEP_FILE}

