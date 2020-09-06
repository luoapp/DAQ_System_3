# $URL:$
# $Rev:$
# $Date:$

UTIL_TARGET	:= ${UTIL_DIR}/adadio_utils.a
CC_FLAGS	:= ${CC_FLAGS} -I${UTIL_DIR}
LIB_FILES	:= ${LIB_FILES} ${UTIL_TARGET}
VPATH		:= ${VPATH} ${UTIL_DIR}

UTIL_FILES	:=										\
			${UTIL_DIR}/util_ain_buf_clear.o		\
			${UTIL_DIR}/util_ain_buf_size.o			\
			${UTIL_DIR}/util_ain_buf_sts.o			\
			${UTIL_DIR}/util_ain_chan_last.o		\
			${UTIL_DIR}/util_ain_mode.o				\
			${UTIL_DIR}/util_ain_nrate.o			\
			${UTIL_DIR}/util_ain_trigger.o			\
			${UTIL_DIR}/util_aout_ch_x_write.o		\
			${UTIL_DIR}/util_aout_enable.o			\
			${UTIL_DIR}/util_aout_strobe.o			\
			${UTIL_DIR}/util_aout_strobe_enable.o	\
			${UTIL_DIR}/util_auto_calibrate.o		\
			${UTIL_DIR}/util_config.o				\
			${UTIL_DIR}/util_data_format.o			\
			${UTIL_DIR}/util_dio_pin_read.o			\
			${UTIL_DIR}/util_dio_pin_write.o		\
			${UTIL_DIR}/util_dio_port_dir.o			\
			${UTIL_DIR}/util_dio_port_read.o		\
			${UTIL_DIR}/util_dio_port_write.o		\
			${UTIL_DIR}/util_fsamp.o				\
			${UTIL_DIR}/util_id.o					\
			${UTIL_DIR}/util_initialize.o			\
			${UTIL_DIR}/util_irq_enable.o			\
			${UTIL_DIR}/util_irq_sel.o				\
			${UTIL_DIR}/util_irq_status.o			\
			${UTIL_DIR}/util_loopback_channel.o		\
			${UTIL_DIR}/util_query.o				\
			${UTIL_DIR}/util_reg.o					\
			${UTIL_DIR}/util_rx_io_mode.o			\
			${UTIL_DIR}/util_rx_io_timeout.o		\
													\
			${UTIL_DIR}/gsc_util_close.o			\
			${UTIL_DIR}/gsc_util_count.o			\
			${UTIL_DIR}/gsc_util_id.o				\
			${UTIL_DIR}/gsc_util_kbhit.o			\
			${UTIL_DIR}/gsc_util_label.o			\
			${UTIL_DIR}/gsc_util_open.o				\
			${UTIL_DIR}/gsc_util_select.o			\
			${UTIL_DIR}/gsc_util_reg.o				\
			${UTIL_DIR}/gsc_util_reg_plx9080.o



REL_CLEAN	:= ${REL_CLEAN} ${UTIL_DIR}/*.o

${UTIL_TARGET}: ${GSC_UTIL_SOURCES} ${UTIL_FILES}
	@echo ==== Linking: $@
	@ld -r -o $@ ${UTIL_FILES}

clean::
	@echo ==== Cleaning ${UTIL_TARGET} ...
	@rm -f *.o *.scc ${UTIL_TARGET} ${REL_CLEAN} ${LIB_FILES} ${DEP_FILE}
	@echo > ${DEP_FILE}

GSC_COMMON	:= $(shell ls -d ../../../gsc_common/linux/utils 2>/dev/null | wc -l )

ifeq ("${GSC_COMMON}","1")

GSC_DIR		:= ../../../gsc_common/linux/utils

${UTIL_DIR}/gsc_util_makefile.inc: ${UTIL_DIR}/${GSC_DIR}/gsc_util_makefile.inc
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

else

GSC_DIR		:= .

endif

include ${UTIL_DIR}/gsc_util_makefile.inc


