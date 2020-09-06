# $URL:$
# $Rev:$
# $Date:$

# Make include file for the udel common.

UDEL_COMM_TARGET	:= udel_daq.o
#LIB_FILES		:= ${LIB_FILES} ${DOCSRC_TARGET}



${UDEL_COMM_TARGET}: udel_daq.c udel_daq.h udel_drv.h
	@

clean::
	@echo ==== Cleaning ${DOCSRC_TARGET} ...
	@rm -f *.scc *.o ${DOCSRC_TARGET} ${DOCSRC_FILES}
	@-chmod 666 ${DEP_FILE}
	@echo > ${DEP_FILE}

