# $URL:$
# $Rev:$
# $Date:$

# Make include file for the ADADIO document source code library.

CC_FLAGS		+= -I../docsrc
DOCSRC_TARGET	:= ../docsrc/adadio_dsl.a
LIB_FILES		:= ${LIB_FILES} ${DOCSRC_TARGET}

DOCSRC_FILES	:=					\
				../docsrc/close.o	\
				../docsrc/ioctl.o	\
				../docsrc/open.o	\
				../docsrc/read.o



${DOCSRC_TARGET}: ${DOCSRC_FILES}
	@echo ==== Linking: $@
	@ld -r -o $@ ${DOCSRC_FILES}

clean::
	@echo ==== Cleaning ${DOCSRC_TARGET} ...
	@rm -f *.scc *.o ${DOCSRC_TARGET} ${DOCSRC_FILES}
	@-chmod 666 ${DEP_FILE}
	@echo > ${DEP_FILE}

