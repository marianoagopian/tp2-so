GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL forceCurrentTask
GLOBAL forceTimerTick
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

EXTERN getRSP
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN irq80Dispatcher

EXTERN has_or_decrease_time
EXTERN next_task

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


enable_multitasking:
  mov BYTE [multitasking_enabled], 1
  jmp tickHandle

;8254 Timer (Timer Tick)
_irq00Handler:
	;irqHandlerMaster 0
  pushState
  cmp BYTE [multitasking_enabled], 1
  jne enable_multitasking

  call has_or_decrease_time
  cmp rax, 1
  je tickHandle

  switchTask:
    mov rdi, rsp
    mov rsi, ss
    call next_task
    mov rsp,rax

  tickHandle:
    mov rdi, 0
    call irqDispatcher

  mov al, 20h
  out 20h, al

  popState
  iretq

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
  pushState

	push rsp

  mov rax, 0         ; xor rax, rax
  mov rax, ss
  push rax
  mov rax, [rsp + 8 * 16]        ; restauro rax

  push r9
  mov r9, r8
  mov r8, r10
  mov rcx, rdx
  mov rdx, rsi
  mov rsi, rdi
  mov rdi, rax 

  call irq80Dispatcher
  pop r8

  mov [rsp + 8 * 16], rax  ; valor de retorno

  pop r8
  pop r8

  popState
  iretq

continue:
	mov rsp, rbp
	pop rbp
	iretq

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

forceCurrentTask:
  call getRSP
  mov rsp,rax
  popState
  iretq

forceTimerTick:
  int 20h
  ret

SECTION .bss
	aux resq 1
	reg resb 64
	regdump	resq 17

SECTION .data
  multitasking_enabled db 0