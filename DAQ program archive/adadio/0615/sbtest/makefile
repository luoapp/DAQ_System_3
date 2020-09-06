# $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/ADADIO/ADADIO_Linux_3.x.x.x_GSC_DN/sbtest/makefile $
# $Rev: 1620 $
# $Date: 2009-04-10 11:41:41 -0500 (Fri, 10 Apr 2009) $

CC			= gcc
CC_FLAGS	= -c -Wall
CC_FLAGS	+= -I.
CC_FLAGS	+= -I../driver
CC_FLAGS	+= -I../utils
CC_FLAGS	+= -I../docsrc
DEP_FILE	= makefile.dep
LIB_FILES	=
TARGET		= sbtest

default:	all
DSL_DIR		:= ../docsrc
include	${DSL_DIR}/makefile.inc
UTIL_DIR	:= ../utils
include	${UTIL_DIR}/makefile.inc

OBJ_FILES	=						\
			ain_buf_clear.o			\
			ain_buf_size.o			\
			ain_buf_sts.o			\
			ain_chan_last.o			\
			ain_mode.o				\
			ain_nrate.o				\
			ain_trigger.o			\
			aout_ch_x_write.o		\
			aout_enable.o			\
			aout_strobe.o			\
			aout_strobe_enable.o	\
			auto_calibrate.o		\
			data_format.o			\
			dio_pin_read.o			\
			dio_pin_write.o			\
			dio_port_dir.o			\
			dio_port_read.o			\
			dio_port_write.o		\
			initialize.o			\
			irq_enable.o			\
			irq_sel.o				\
			irq_status.o			\
			loopback_channel.o		\
			main.o					\
			query.o					\
			reg_mod.o				\
			reg_read.o				\
			reg_write.o				\
			rx_io_mode.o			\
			rx_io_timeout.o			\
			service.o



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
