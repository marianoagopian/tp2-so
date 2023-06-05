// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "./include/syscalls.h"

#define INVALID_SYS_CALL 255

//registros en asm:		rax		  rdi		 rsi	 rdx		r10		 r8			r9
//registros en c: 		rdi		  rsi		 rdx	 rcx		r8		 r9		   stack		// de derecha a izquierda se pasan a los registros
uint64_t irq80Dispatcher(uint64_t mode, uint64_t arg0, uint64_t arg1, 
	uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t ss, uint64_t rsp) {
	switch (mode) {
		case SYS_READ:
			return sysRead((unsigned int) arg0, (char *) arg1, (unsigned int) arg2);
		case SYS_WRITE:
			return sysWriteToScreen((const char *) arg0, (unsigned int) arg1);
		case SYS_INFOREG:
			return sysInfoReg((uint64_t *)arg0);
		case SYS_TIME:
			return sysTime();
		case SYS_CLEAR_SCREEN:
			sysClear();
			return 0;
		case SYS_BEEP:
			sysBeep((uint32_t) arg0);
			return 0;
		case SYS_PRINT_MEM:
			return sysPrintmem(arg0,(char*) arg1);
		case SYS_DRAW_WHITE_RECT:
			sysDrawWhiteRect((uint16_t) arg0, (uint16_t) arg1, (uint16_t) arg2, (uint16_t) arg3);
			return 0;
		case SYS_DRAW_GREEN_RECT:
			sysDrawGreenRect((uint16_t) arg0, (uint16_t) arg1, (uint16_t) arg2, (uint16_t) arg3);
			return 0;
		case SYS_HOLDER:
			sysHolder((int)arg0);
			return 0;
		case SYS_CLEAR_BUFFER:
			sysClearBuffer();
			return 0;
		case SYS_SET_LEVEL:
			sysSetLevel((int) arg0);
			return 0;
		case SYS_GET_LEVEL:
			return sysGetLevel();
		case SYS_STOP:
			sysStop();
			return 0;
		case SYS_ALLOC:
			return sysAlloc(arg0);
		case SYS_DESTROY_PIPE:
			return sysDestroyPipe((unsigned int) arg0);
		case SYS_DESTROY_SEM:
			return sysDestroySem((unsigned int) arg0);
		case SYS_FREE:
			return sysFree( (void*) arg0);
		case SYS_GET_PID:
			return sysGetPid();
		case SYS_KILL_PROCESS:
			return sysKillProcess((unsigned int) arg0);
		case SYS_MM_STATUS:
			return sysMmStatus((uint64_t *) arg0);
		case SYS_NICE:
			return sysNice(arg0, arg1);
		case SYS_PAUSE_PROCESS:
			return sysPauseProcess((unsigned int) arg0);
		case SYS_PIPE_INFO:
			return sysPipeInfo((pipes_info * )arg0);
		case SYS_PROCESS_ALIVE:
			return sysProcessAlive((unsigned int) arg0);
		case SYS_PROCESS_INFO:
			return sysProcessInfo((process_info *) arg0);
		case SYS_READ_PIPE:
			return sysReadPipe((unsigned int) arg0, (char *) arg1, (unsigned int) arg2);
		case SYS_REGISTER_CHILD_PROCESS:
			return sysRegisterChildProcess(arg0, (uint8_t) arg1, (uint8_t) arg2, (char **) arg3);
		case SYS_REGISTER_PIPE_AVAILABLE:
			return sysRegisterPipeAvailable();
		case SYS_REGISTER_PROCESS:
			return sysRegisterProcess(arg0, (uint8_t) arg1, (uint8_t) arg2, (char **) arg3);
		case SYS_REGISTER_SEM:
			return sysRegisterSem((unsigned int) arg0, (unsigned int) arg1);
		case SYS_REGISTER_SEM_AVAILABLE:
			return sysRegisterSemAvailable((unsigned int) arg0);
		case SYS_RENOUNCE_CPU:
			return sysRenounceCpu();
		case SYS_SIGNAL_SEM:
			return sysSignalSem((unsigned int) arg0);
		case SYS_WAIT_FOR_CHILDREN:
			return sysWaitForChildren();
		case SYS_WAIT_SEM:
			return sysWaitSem((unsigned int) arg0);
		case SYS_WRITE_PIPE:
			return sysWritePipe((unsigned int) arg0, (char *)arg1, (unsigned int) arg2);
		case SYS_CHECK_BUFFER:
			return sysCheckBuffer();
		default:
			return INVALID_SYS_CALL;
	}
}
