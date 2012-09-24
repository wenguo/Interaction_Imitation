#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1019342997/e_acc.o ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o ${OBJECTDIR}/_ext/1019342997/e_agenda.o ${OBJECTDIR}/_ext/1019342997/e_batt.o ${OBJECTDIR}/_ext/1019342997/e_init_port.o ${OBJECTDIR}/_ext/1019342997/e_led.o ${OBJECTDIR}/_ext/1019342997/e_micro.o ${OBJECTDIR}/_ext/1019342997/e_motors.o ${OBJECTDIR}/_ext/1019342997/e_prox.o ${OBJECTDIR}/_ext/1019342997/filter.o ${OBJECTDIR}/_ext/1360937237/crc16.o ${OBJECTDIR}/_ext/1360937237/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH=/usr/lib/jvm/java-6-openjdk/jre/bin/
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=/opt/microchip/mplabc30/v3.30b/bin/pic30-gcc
# MP_BC is not defined
MP_AS=/opt/microchip/mplabc30/v3.30b/bin/pic30-as
MP_LD=/opt/microchip/mplabc30/v3.30b/bin/pic30-ld
MP_AR=/opt/microchip/mplabc30/v3.30b/bin/pic30-ar
# MP_BC is not defined
MP_CC_DIR=/opt/microchip/mplabc30/v3.30b/bin
# MP_BC_DIR is not defined
MP_AS_DIR=/opt/microchip/mplabc30/v3.30b/bin
MP_LD_DIR=/opt/microchip/mplabc30/v3.30b/bin
MP_AR_DIR=/opt/microchip/mplabc30/v3.30b/bin
# MP_BC_DIR is not defined

.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf

MP_PROCESSOR_OPTION=30F6014A
MP_LINKER_FILE_OPTION=,--script=/opt/microchip/mplabc30/v3.30b/support/dsPIC30F/gld/p30F6014A.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1019342997/e_led.o: ../src/epfl/e_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ${OBJECTDIR}/_ext/1019342997/e_led.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_led.o.d -o ${OBJECTDIR}/_ext/1019342997/e_led.o ../src/epfl/e_led.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_led.o.d -o ${OBJECTDIR}/_ext/1019342997/e_led.o ../src/epfl/e_led.c   > ${OBJECTDIR}/_ext/1019342997/e_led.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_led.o.d > ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_led.o.d > ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_led.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_led.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_micro.o: ../src/epfl/e_micro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ${OBJECTDIR}/_ext/1019342997/e_micro.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_micro.o.d -o ${OBJECTDIR}/_ext/1019342997/e_micro.o ../src/epfl/e_micro.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_micro.o.d -o ${OBJECTDIR}/_ext/1019342997/e_micro.o ../src/epfl/e_micro.c   > ${OBJECTDIR}/_ext/1019342997/e_micro.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_micro.o.d > ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_micro.o.d > ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_micro.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/filter.o: ../src/epfl/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.ok ${OBJECTDIR}/_ext/1019342997/filter.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/filter.o.d -o ${OBJECTDIR}/_ext/1019342997/filter.o ../src/epfl/filter.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/filter.o.d -o ${OBJECTDIR}/_ext/1019342997/filter.o ../src/epfl/filter.c   > ${OBJECTDIR}/_ext/1019342997/filter.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/filter.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/filter.o.d > ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/filter.o.d > ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/filter.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/filter.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/filter.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_batt.o: ../src/epfl/e_batt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ${OBJECTDIR}/_ext/1019342997/e_batt.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_batt.o.d -o ${OBJECTDIR}/_ext/1019342997/e_batt.o ../src/epfl/e_batt.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_batt.o.d -o ${OBJECTDIR}/_ext/1019342997/e_batt.o ../src/epfl/e_batt.c   > ${OBJECTDIR}/_ext/1019342997/e_batt.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_batt.o.d > ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_batt.o.d > ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_batt.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_init_port.o: ../src/epfl/e_init_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d -o ${OBJECTDIR}/_ext/1019342997/e_init_port.o ../src/epfl/e_init_port.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d -o ${OBJECTDIR}/_ext/1019342997/e_init_port.o ../src/epfl/e_init_port.c   > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1360937237/crc16.o: ../src/crc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ${OBJECTDIR}/_ext/1360937237/crc16.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/crc16.o.d -o ${OBJECTDIR}/_ext/1360937237/crc16.o ../src/crc16.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/crc16.o.d -o ${OBJECTDIR}/_ext/1360937237/crc16.o ../src/crc16.c   > ${OBJECTDIR}/_ext/1360937237/crc16.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360937237/crc16.o.d > ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360937237/crc16.o.d > ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1360937237/crc16.o.ok; else cat ${OBJECTDIR}/_ext/1360937237/crc16.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_ad_conv.o: ../src/epfl/e_ad_conv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d -o ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o ../src/epfl/e_ad_conv.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d -o ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o ../src/epfl/e_ad_conv.c   > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_motors.o: ../src/epfl/e_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ${OBJECTDIR}/_ext/1019342997/e_motors.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_motors.o.d -o ${OBJECTDIR}/_ext/1019342997/e_motors.o ../src/epfl/e_motors.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_motors.o.d -o ${OBJECTDIR}/_ext/1019342997/e_motors.o ../src/epfl/e_motors.c   > ${OBJECTDIR}/_ext/1019342997/e_motors.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_motors.o.d > ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_motors.o.d > ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_motors.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_acc.o: ../src/epfl/e_acc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ${OBJECTDIR}/_ext/1019342997/e_acc.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_acc.o.d -o ${OBJECTDIR}/_ext/1019342997/e_acc.o ../src/epfl/e_acc.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_acc.o.d -o ${OBJECTDIR}/_ext/1019342997/e_acc.o ../src/epfl/e_acc.c   > ${OBJECTDIR}/_ext/1019342997/e_acc.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_acc.o.d > ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_acc.o.d > ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_acc.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.ok ${OBJECTDIR}/_ext/1360937237/main.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/main.o.d -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/main.o.d -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   > ${OBJECTDIR}/_ext/1360937237/main.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1360937237/main.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360937237/main.o.d > ${OBJECTDIR}/_ext/1360937237/main.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/main.o.tmp ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360937237/main.o.d > ${OBJECTDIR}/_ext/1360937237/main.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/main.o.tmp ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1360937237/main.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1360937237/main.o.ok; else cat ${OBJECTDIR}/_ext/1360937237/main.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_agenda.o: ../src/epfl/e_agenda.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d -o ${OBJECTDIR}/_ext/1019342997/e_agenda.o ../src/epfl/e_agenda.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d -o ${OBJECTDIR}/_ext/1019342997/e_agenda.o ../src/epfl/e_agenda.c   > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_prox.o: ../src/epfl/e_prox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ${OBJECTDIR}/_ext/1019342997/e_prox.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_prox.o.d -o ${OBJECTDIR}/_ext/1019342997/e_prox.o ../src/epfl/e_prox.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_prox.o.d -o ${OBJECTDIR}/_ext/1019342997/e_prox.o ../src/epfl/e_prox.c   > ${OBJECTDIR}/_ext/1019342997/e_prox.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_prox.o.d > ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_prox.o.d > ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_prox.o.err; exit 1; fi
	
else
${OBJECTDIR}/_ext/1019342997/e_led.o: ../src/epfl/e_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ${OBJECTDIR}/_ext/1019342997/e_led.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_led.o.d -o ${OBJECTDIR}/_ext/1019342997/e_led.o ../src/epfl/e_led.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_led.o.d -o ${OBJECTDIR}/_ext/1019342997/e_led.o ../src/epfl/e_led.c   > ${OBJECTDIR}/_ext/1019342997/e_led.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_led.o.d > ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_led.o.d > ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp ${OBJECTDIR}/_ext/1019342997/e_led.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_led.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_led.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_led.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_led.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_micro.o: ../src/epfl/e_micro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ${OBJECTDIR}/_ext/1019342997/e_micro.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_micro.o.d -o ${OBJECTDIR}/_ext/1019342997/e_micro.o ../src/epfl/e_micro.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_micro.o.d -o ${OBJECTDIR}/_ext/1019342997/e_micro.o ../src/epfl/e_micro.c   > ${OBJECTDIR}/_ext/1019342997/e_micro.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_micro.o.d > ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_micro.o.d > ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp ${OBJECTDIR}/_ext/1019342997/e_micro.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_micro.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_micro.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_micro.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/filter.o: ../src/epfl/filter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.ok ${OBJECTDIR}/_ext/1019342997/filter.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/filter.o.d -o ${OBJECTDIR}/_ext/1019342997/filter.o ../src/epfl/filter.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/filter.o.d -o ${OBJECTDIR}/_ext/1019342997/filter.o ../src/epfl/filter.c   > ${OBJECTDIR}/_ext/1019342997/filter.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/filter.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/filter.o.d > ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/filter.o.d > ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp ${OBJECTDIR}/_ext/1019342997/filter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/filter.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/filter.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/filter.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/filter.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_batt.o: ../src/epfl/e_batt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ${OBJECTDIR}/_ext/1019342997/e_batt.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_batt.o.d -o ${OBJECTDIR}/_ext/1019342997/e_batt.o ../src/epfl/e_batt.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_batt.o.d -o ${OBJECTDIR}/_ext/1019342997/e_batt.o ../src/epfl/e_batt.c   > ${OBJECTDIR}/_ext/1019342997/e_batt.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_batt.o.d > ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_batt.o.d > ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp ${OBJECTDIR}/_ext/1019342997/e_batt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_batt.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_batt.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_batt.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_init_port.o: ../src/epfl/e_init_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d -o ${OBJECTDIR}/_ext/1019342997/e_init_port.o ../src/epfl/e_init_port.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d -o ${OBJECTDIR}/_ext/1019342997/e_init_port.o ../src/epfl/e_init_port.c   > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d > ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp ${OBJECTDIR}/_ext/1019342997/e_init_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_init_port.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_init_port.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_init_port.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1360937237/crc16.o: ../src/crc16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ${OBJECTDIR}/_ext/1360937237/crc16.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/crc16.o.d -o ${OBJECTDIR}/_ext/1360937237/crc16.o ../src/crc16.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/crc16.o.d -o ${OBJECTDIR}/_ext/1360937237/crc16.o ../src/crc16.c   > ${OBJECTDIR}/_ext/1360937237/crc16.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360937237/crc16.o.d > ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360937237/crc16.o.d > ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp ${OBJECTDIR}/_ext/1360937237/crc16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc16.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1360937237/crc16.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1360937237/crc16.o.ok; else cat ${OBJECTDIR}/_ext/1360937237/crc16.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_ad_conv.o: ../src/epfl/e_ad_conv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d -o ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o ../src/epfl/e_ad_conv.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d -o ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o ../src/epfl/e_ad_conv.c   > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d > ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_ad_conv.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_motors.o: ../src/epfl/e_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ${OBJECTDIR}/_ext/1019342997/e_motors.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_motors.o.d -o ${OBJECTDIR}/_ext/1019342997/e_motors.o ../src/epfl/e_motors.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_motors.o.d -o ${OBJECTDIR}/_ext/1019342997/e_motors.o ../src/epfl/e_motors.c   > ${OBJECTDIR}/_ext/1019342997/e_motors.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_motors.o.d > ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_motors.o.d > ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp ${OBJECTDIR}/_ext/1019342997/e_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_motors.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_motors.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_motors.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_acc.o: ../src/epfl/e_acc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ${OBJECTDIR}/_ext/1019342997/e_acc.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_acc.o.d -o ${OBJECTDIR}/_ext/1019342997/e_acc.o ../src/epfl/e_acc.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_acc.o.d -o ${OBJECTDIR}/_ext/1019342997/e_acc.o ../src/epfl/e_acc.c   > ${OBJECTDIR}/_ext/1019342997/e_acc.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_acc.o.d > ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_acc.o.d > ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp ${OBJECTDIR}/_ext/1019342997/e_acc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_acc.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_acc.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_acc.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.ok ${OBJECTDIR}/_ext/1360937237/main.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/main.o.d -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1360937237/main.o.d -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   > ${OBJECTDIR}/_ext/1360937237/main.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1360937237/main.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1360937237/main.o.d > ${OBJECTDIR}/_ext/1360937237/main.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/main.o.tmp ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1360937237/main.o.d > ${OBJECTDIR}/_ext/1360937237/main.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${CP} ${OBJECTDIR}/_ext/1360937237/main.o.tmp ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1360937237/main.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1360937237/main.o.ok; else cat ${OBJECTDIR}/_ext/1360937237/main.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_agenda.o: ../src/epfl/e_agenda.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d -o ${OBJECTDIR}/_ext/1019342997/e_agenda.o ../src/epfl/e_agenda.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d -o ${OBJECTDIR}/_ext/1019342997/e_agenda.o ../src/epfl/e_agenda.c   > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d > ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp ${OBJECTDIR}/_ext/1019342997/e_agenda.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_agenda.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_agenda.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_agenda.o.err; exit 1; fi
	
${OBJECTDIR}/_ext/1019342997/e_prox.o: ../src/epfl/e_prox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1019342997 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ${OBJECTDIR}/_ext/1019342997/e_prox.o.err 
	@echo ${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_prox.o.d -o ${OBJECTDIR}/_ext/1019342997/e_prox.o ../src/epfl/e_prox.c  
	@-${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF ${OBJECTDIR}/_ext/1019342997/e_prox.o.d -o ${OBJECTDIR}/_ext/1019342997/e_prox.o ../src/epfl/e_prox.c   > ${OBJECTDIR}/_ext/1019342997/e_prox.o.err 2>&1  ; if [ $$? -eq 0 ] ; then touch ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ; fi 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1019342997/e_prox.o.d > ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1019342997/e_prox.o.d > ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${CP} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp ${OBJECTDIR}/_ext/1019342997/e_prox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019342997/e_prox.o.tmp
endif
	@if [ -f ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok ] ; then rm -f ${OBJECTDIR}/_ext/1019342997/e_prox.o.ok; else cat ${OBJECTDIR}/_ext/1019342997/e_prox.o.err; exit 1; fi
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,--heap=512,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,--heap=512,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/epuck.X.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
