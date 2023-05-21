
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq80Handler
GLOBAL _beep_start
GLOBAL _beep_stop
GLOBAL _inportb
GLOBAL _outportb

GLOBAL _exception0Handler
GLOBAL _exception6Handler
GLOBAL getKey

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysWrite
EXTERN sysRead
EXTERN sysClear
EXTERN sysScreenSize
EXTERN sysInfoReg
EXTERN sysTime
EXTERN sysPrintmem
EXTERN sysDrawRect
EXTERN sysClearBuffer
EXTERN sysCheckBuffer
EXTERN sysSetLevel
EXTERN sysHolder
EXTERN sysGetLevel
EXTERN sysBeep
EXTERN sysStop

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rsi
	push rdi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ; puntero a principio de dump de registros
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1
	pushState

  	mov rsi, rsp
	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
  mov rbp, rsp
  mov ax, di
  out	21h,al
  pop rbp
  retn

picSlaveMask:
	push    rbp
  mov     rbp, rsp
  mov     ax, di  ; ax = mascara de 16 bits
  out		0A1h, al
  pop     rbp
  retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;Syscall
_irq80Handler:
	push rbp
	mov rbp, rsp
	cmp rax, 0
	je sys_read
	cmp rax, 1
	je sys_write
	cmp rax, 2
	je sys_inforeg
	cmp rax, 3
	je sys_time
	cmp rax, 4
	je sys_clear_screan
  cmp rax, 5
  je sys_beep
	cmp rax, 6
	je sys_printmem
	cmp rax, 7
	je sys_draw_rect
	cmp rax, 8
	je sys_check_buffer
  cmp rax, 9
	je sys_holder
  cmp rax, 10
	je sys_clear_buffer
	cmp rax, 11
	je sys_set_level
  cmp rax, 12
	je sys_get_level
  cmp rax, 13
  je sys_stop
	jmp continue

continue:
	mov rsp, rbp
	pop rbp
	iretq

sys_read:
  call sysRead
  jmp continue

sys_write:
  call sysWrite
  jmp continue

sys_inforeg:
  call sysInfoReg
  jmp continue

sys_clear_screan:
  call sysClear
  jmp continue

sys_time:
  call sysTime
  jmp continue

sys_printmem:
  call sysPrintmem
  jmp continue

sys_draw_rect:
  call sysDrawRect
  jmp continue

sys_clear_buffer:
  call sysClearBuffer
  jmp continue

sys_check_buffer:
  call sysCheckBuffer
  jmp continue

sys_set_level:
  call sysSetLevel
  jmp continue

sys_holder:
  call sysHolder
  jmp continue

sys_get_level:
  call sysGetLevel
  jmp continue

sys_beep:
  call sysBeep
  jmp continue

sys_stop:
  call sysStop
  jmp continue

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

_exception6Handler:
	exceptionHandler 6

_beep_start:
    push rbp
    mov rbp, rsp

    mov al, 0xB6
    out 43h,al

    mov rbx, rdi
    mov rax, 0
    mov ax, bx

    out 42h,al
    mov al,ah
    out 42h,al

    in al, 61h 
    or al, 03h 
    out 61h,al

    mov rsp, rbp
    pop rbp
    ret

_beep_stop:
    push rbp
    mov rbp, rsp

    in al, 61h
    and al, 0xFC
    out 61h, al

    mov rsp, rbp
    pop rbp
    ret

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1
	reg resb 64
	regdump	resq 17