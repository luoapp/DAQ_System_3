# $URL: http://subversion:8080/svn/gsc/trunk/drivers/LINUX/16AO20/16AO20_Linux_2.x.x.x_GSC_DN/sbtest/makefile $
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
TARGET		= sbtest
VPATH		:= ../utils

default:	all
DSL_DIR		:= ../docsrc
include	${DSL_DIR}/makefile.inc
UTIL_DIR	:= ../utils
include	${UTIL_DIR}/makefile.inc

OBJ_FILES	=					\
			auto_calibrate.o	\
			buffer_clear.o		\
			buffer_mode.o		\
			buffer_over_data.o	\
			buffer_over_frame.o	\
			buffer_size.o		\
			buffer_status.o		\
			burst_ready.o		\
			burst_trg_src.o		\
			burst_trigger.o		\
			channel_sel.o		\
			clock_enable.o		\
			clock_osc_src.o		\
			clock_ready.o		\
			clock_src.o			\
			clock_sw.o			\
			data_format.o		\
			ground_sense.o		\
			initialize.o		\
			irq_enable.o		\
			irq_sel.o			\
			irq_state.o			\
			load_ready.o		\
			load_request.o		\
			main.o				\
			nclk.o				\
			nrate.o				\
			output_mode.o		\
			query.o				\
			reg_mod.o			\
			reg_read.o			\
			reg_write.o			\
			sample_mode.o		\
			service.o			\
			tx_io_mode.o		\
			tx_io_over_data.o	\
			tx_io_over_frame.o	\
			tx_io_timeout.o		\
			xcvr_type.o



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
