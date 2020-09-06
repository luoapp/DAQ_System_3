# $URL: http://subversion:8080/svn/gsc/trunk/drivers/gsc_common/linux/utils/gsc_util_makefile.inc $
# $Rev: 1592 $
# $Date: 2009-03-29 12:48:28 -0500 (Sun, 29 Mar 2009) $

GSC_UTIL_SOURCES	:=									\
					${UTIL_DIR}/gsc_util_close.c		\
					${UTIL_DIR}/gsc_util_count.c		\
					${UTIL_DIR}/gsc_util_id.c			\
					${UTIL_DIR}/gsc_util_kbhit.c		\
					${UTIL_DIR}/gsc_util_label.c		\
					${UTIL_DIR}/gsc_util_open.c			\
					${UTIL_DIR}/gsc_util_reg.c			\
					${UTIL_DIR}/gsc_util_reg_plx9056.c	\
					${UTIL_DIR}/gsc_util_reg_plx9080.c	\
					${UTIL_DIR}/gsc_util_select.c		\
					${UTIL_DIR}/gsc_utils.h



ifeq ("${GSC_COMMON}","1")

${UTIL_DIR}/gsc_util_close.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_close.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< ${UTIL_DIR}/
	@chmod 444 $@

${UTIL_DIR}/gsc_util_count.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_count.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< ${UTIL_DIR}/
	@chmod 444 $@

${UTIL_DIR}/gsc_util_id.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_id.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< ${UTIL_DIR}/
	@chmod 444 $@

${UTIL_DIR}/gsc_util_kbhit.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_kbhit.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_label.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_label.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_open.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_open.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_reg.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_reg.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_reg_plx9056.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_reg_plx9056.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_reg_plx9080.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_reg_plx9080.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_util_select.c: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_util_select.c
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

${UTIL_DIR}/gsc_utils.h: ${UTIL_DIR}/../../../gsc_common/linux/utils/gsc_utils.h
	@echo == Getting: $@
	@rm -f $@
	@cp $< $@
	@chmod 444 $@

endif
