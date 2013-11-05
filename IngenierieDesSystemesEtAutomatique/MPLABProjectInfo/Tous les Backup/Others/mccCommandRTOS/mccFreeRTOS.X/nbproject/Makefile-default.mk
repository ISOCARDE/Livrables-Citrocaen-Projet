#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FreeRTOS/Source/croutine.c FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S FreeRTOS/Source/portable/MemMang/heap_1.c uart.c pwm.c ad7885.c UserInit.c regulateur.c timer1.c RTOSInit.c interfaceShell.c timerFunctions.c gpio.c canBoost.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/ad7885.o ${OBJECTDIR}/UserInit.o ${OBJECTDIR}/regulateur.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/RTOSInit.o ${OBJECTDIR}/interfaceShell.o ${OBJECTDIR}/timerFunctions.o ${OBJECTDIR}/gpio.o ${OBJECTDIR}/canBoost.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FreeRTOS/Source/croutine.o.d ${OBJECTDIR}/FreeRTOS/Source/list.o.d ${OBJECTDIR}/FreeRTOS/Source/queue.o.d ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d ${OBJECTDIR}/FreeRTOS/Source/timers.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d ${OBJECTDIR}/uart.o.d ${OBJECTDIR}/pwm.o.d ${OBJECTDIR}/ad7885.o.d ${OBJECTDIR}/UserInit.o.d ${OBJECTDIR}/regulateur.o.d ${OBJECTDIR}/timer1.o.d ${OBJECTDIR}/RTOSInit.o.d ${OBJECTDIR}/interfaceShell.o.d ${OBJECTDIR}/timerFunctions.o.d ${OBJECTDIR}/gpio.o.d ${OBJECTDIR}/canBoost.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o ${OBJECTDIR}/uart.o ${OBJECTDIR}/pwm.o ${OBJECTDIR}/ad7885.o ${OBJECTDIR}/UserInit.o ${OBJECTDIR}/regulateur.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/RTOSInit.o ${OBJECTDIR}/interfaceShell.o ${OBJECTDIR}/timerFunctions.o ${OBJECTDIR}/gpio.o ${OBJECTDIR}/canBoost.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=FreeRTOS/Source/croutine.c FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S FreeRTOS/Source/portable/MemMang/heap_1.c uart.c pwm.c ad7885.c UserInit.c regulateur.c timer1.c RTOSInit.c interfaceShell.c timerFunctions.c gpio.c canBoost.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
	
else
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c   
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/timers.o FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o: FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o FreeRTOS/Source/portable/MemMang/heap_1.c   
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c   
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/pwm.o.d" -o ${OBJECTDIR}/pwm.o pwm.c   
	
${OBJECTDIR}/ad7885.o: ad7885.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ad7885.o.d 
	@${RM} ${OBJECTDIR}/ad7885.o 
	@${FIXDEPS} "${OBJECTDIR}/ad7885.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/ad7885.o.d" -o ${OBJECTDIR}/ad7885.o ad7885.c   
	
${OBJECTDIR}/UserInit.o: UserInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UserInit.o.d 
	@${RM} ${OBJECTDIR}/UserInit.o 
	@${FIXDEPS} "${OBJECTDIR}/UserInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/UserInit.o.d" -o ${OBJECTDIR}/UserInit.o UserInit.c   
	
${OBJECTDIR}/regulateur.o: regulateur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/regulateur.o.d 
	@${RM} ${OBJECTDIR}/regulateur.o 
	@${FIXDEPS} "${OBJECTDIR}/regulateur.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/regulateur.o.d" -o ${OBJECTDIR}/regulateur.o regulateur.c   
	
${OBJECTDIR}/timer1.o: timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c   
	
${OBJECTDIR}/RTOSInit.o: RTOSInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RTOSInit.o.d 
	@${RM} ${OBJECTDIR}/RTOSInit.o 
	@${FIXDEPS} "${OBJECTDIR}/RTOSInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/RTOSInit.o.d" -o ${OBJECTDIR}/RTOSInit.o RTOSInit.c   
	
${OBJECTDIR}/interfaceShell.o: interfaceShell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interfaceShell.o.d 
	@${RM} ${OBJECTDIR}/interfaceShell.o 
	@${FIXDEPS} "${OBJECTDIR}/interfaceShell.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/interfaceShell.o.d" -o ${OBJECTDIR}/interfaceShell.o interfaceShell.c   
	
${OBJECTDIR}/timerFunctions.o: timerFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timerFunctions.o.d 
	@${RM} ${OBJECTDIR}/timerFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/timerFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/timerFunctions.o.d" -o ${OBJECTDIR}/timerFunctions.o timerFunctions.c   
	
${OBJECTDIR}/gpio.o: gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpio.o.d 
	@${RM} ${OBJECTDIR}/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/gpio.o.d" -o ${OBJECTDIR}/gpio.o gpio.c   
	
${OBJECTDIR}/canBoost.o: canBoost.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/canBoost.o.d 
	@${RM} ${OBJECTDIR}/canBoost.o 
	@${FIXDEPS} "${OBJECTDIR}/canBoost.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/canBoost.o.d" -o ${OBJECTDIR}/canBoost.o canBoost.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
else
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o FreeRTOS/Source/croutine.c   
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/list.o FreeRTOS/Source/list.c   
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/queue.o FreeRTOS/Source/queue.c   
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o FreeRTOS/Source/tasks.c   
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/timers.o FreeRTOS/Source/timers.c   
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o: FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.o FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c   
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o: FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o.d" -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_1.o FreeRTOS/Source/portable/MemMang/heap_1.c   
	
${OBJECTDIR}/uart.o: uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c   
	
${OBJECTDIR}/pwm.o: pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/pwm.o.d" -o ${OBJECTDIR}/pwm.o pwm.c   
	
${OBJECTDIR}/ad7885.o: ad7885.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/ad7885.o.d 
	@${RM} ${OBJECTDIR}/ad7885.o 
	@${FIXDEPS} "${OBJECTDIR}/ad7885.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/ad7885.o.d" -o ${OBJECTDIR}/ad7885.o ad7885.c   
	
${OBJECTDIR}/UserInit.o: UserInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/UserInit.o.d 
	@${RM} ${OBJECTDIR}/UserInit.o 
	@${FIXDEPS} "${OBJECTDIR}/UserInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/UserInit.o.d" -o ${OBJECTDIR}/UserInit.o UserInit.c   
	
${OBJECTDIR}/regulateur.o: regulateur.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/regulateur.o.d 
	@${RM} ${OBJECTDIR}/regulateur.o 
	@${FIXDEPS} "${OBJECTDIR}/regulateur.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/regulateur.o.d" -o ${OBJECTDIR}/regulateur.o regulateur.c   
	
${OBJECTDIR}/timer1.o: timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c   
	
${OBJECTDIR}/RTOSInit.o: RTOSInit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RTOSInit.o.d 
	@${RM} ${OBJECTDIR}/RTOSInit.o 
	@${FIXDEPS} "${OBJECTDIR}/RTOSInit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/RTOSInit.o.d" -o ${OBJECTDIR}/RTOSInit.o RTOSInit.c   
	
${OBJECTDIR}/interfaceShell.o: interfaceShell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interfaceShell.o.d 
	@${RM} ${OBJECTDIR}/interfaceShell.o 
	@${FIXDEPS} "${OBJECTDIR}/interfaceShell.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/interfaceShell.o.d" -o ${OBJECTDIR}/interfaceShell.o interfaceShell.c   
	
${OBJECTDIR}/timerFunctions.o: timerFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/timerFunctions.o.d 
	@${RM} ${OBJECTDIR}/timerFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/timerFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/timerFunctions.o.d" -o ${OBJECTDIR}/timerFunctions.o timerFunctions.c   
	
${OBJECTDIR}/gpio.o: gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpio.o.d 
	@${RM} ${OBJECTDIR}/gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/gpio.o.d" -o ${OBJECTDIR}/gpio.o gpio.c   
	
${OBJECTDIR}/canBoost.o: canBoost.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/canBoost.o.d 
	@${RM} ${OBJECTDIR}/canBoost.o 
	@${FIXDEPS} "${OBJECTDIR}/canBoost.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/canBoost.o.d" -o ${OBJECTDIR}/canBoost.o canBoost.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FreeRTOS/Source/include" -I"FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mccFreeRTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
