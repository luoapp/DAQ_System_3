# $URL:$
# $Rev:$
# $Date:$

UTIL_TARGET	:= ${UTIL_DIR}/16ao20_utils.a
CC_FLAGS	:= ${CC_FLAGS} -I${UTIL_DIR}
LIB_FILES	:= ${LIB_FILES} ${UTIL_TARGET}
VPATH		:= ${VPATH} ${UTIL_DIR}

UTIL_FILES	:=										\
			${UTIL_DIR}/util_auto_calibrate.o		\
			${UTIL_DIR}/util_buffer_clear.o			\
			${UTIL_DIR}/util_buffer_mode.o			\
			${UTIL_DIR}/util_buffer_over_data.o		\
			${UTIL_DIR}/util_buffer_over_frame.o	\
			${UTIL_DIR}/util_buffer_size.o			\
			${UTIL_DIR}/util_buffer_status.o		\
			${UTIL_DIR}/util_burst_ready.o			\
			${UTIL_DIR}/util_burst_trig_src.o		\
			${UTIL_DIR}/util_burst_trigger.o		\
			${UTIL_DIR}/util_channel_sel.o			\
			${UTIL_DIR}/util_clock_enable.o			\
			${UTIL_DIR}/util_clock_osc_src.o		\
			${UTIL_DIR}/util_clock_ready.o			\
			${UTIL_DIR}/util_clock_src.o			\
			${UTIL_DIR}/util_clock_sw.o				\
			${UTIL_DIR}/util_config.o				\
			${UTIL_DIR}/util_data_format.o			\
			${UTIL_DIR}/util_fref.o					\
			${UTIL_DIR}/util_fsamp.o				\
			${UTIL_DIR}/util_ground_sense.o			\
			${UTIL_DIR}/util_id.o					\
			${UTIL_DIR}/util_initialize.o			\
			${UTIL_DIR}/util_irq_enable.o			\
			${UTIL_DIR}/util_irq_sel.o				\
			${UTIL_DIR}/util_irq_state.o			\
			${UTIL_DIR}/util_load_ready.o			\
			${UTIL_DIR}/util_load_request.o			\
			${UTIL_DIR}/util_nclk.o					\
			${UTIL_DIR}/util_nrate.o				\
			${UTIL_DIR}/util_output_mode.o			\
			${UTIL_DIR}/util_query.o				\
			${UTIL_DIR}/util_reg.o					\
			${UTIL_DIR}/util_sample_mode.o			\
			${UTIL_DIR}/util_tx_io_mode.o			\
			${UTIL_DIR}/util_tx_io_over_data.o		\
			${UTIL_DIR}/util_tx_io_over_frame.o		\
			${UTIL_DIR}/util_tx_io_timeout.o		\
			${UTIL_DIR}/util_xcvr_type.o			\
													\
			${UTIL_DIR}/gsc_util_close.o			\
			${UTIL_DIR}/gsc_util_count.o			\
			${UTIL_DIR}/gsc_util_id.o				\
			${UTIL_DIR}/gsc_util_kbhit.o			\
			${UTIL_DIR}/gsc_util_label.o			\
			${UTIL_DIR}/gsc_util_open.o				\
			${UTIL_DIR}/gsc_util_reg.o				\
			${UTIL_DIR}/gsc_util_reg_plx9080.o		\
			${UTIL_DIR}/gsc_util_select.o



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
