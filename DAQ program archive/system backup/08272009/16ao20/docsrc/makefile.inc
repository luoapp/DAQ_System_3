# $URL:$
# $Rev:$
# $Date:$
# Make include file for the 16AO20 document sources

DSL_TARGET	:= ${DSL_DIR}/16ao20_dsl.a
CC_FLAGS	:= ${CC_FLAGS} -I${DSL_DIR}
LIB_FILES	:= ${LIB_FILES} ${DSL_TARGET}
VPATH		:= ${VPATH} ${DSL_DIR}

DSL_FILES	:=					\
			${DSL_DIR}/close.o	\
			${DSL_DIR}/ioctl.o	\
			${DSL_DIR}/open.o	\
			${DSL_DIR}/write.o

REL_CLEAN	:= ${REL_CLEAN} ${DSL_DIR}/*.o

${DSL_TARGET}: ${DSL_FILES}
	@echo ==== Linking: $@
	@ld -r -o $@ ${DSL_FILES}

clean::
	@echo ==== Cleaning ${DSL_TARGET} ...
	@rm -f *.o ${DSL_TARGET} ${REL_CLEAN} ${LIB_FILES} ${DEP_FILE}
	@echo > ${DEP_FILE}

