GLOBAL syscaller
GLOBAL sys_draw_rect

section .text

;ASM: rax - rdi - rsi - rdx - r10
;C:   rdi - rsi - rdx - rcx - r8

syscaller:
    push rbp
    mov rbp, rsp

    mov rax, rdi        ; no need to preserve registers
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov r10, r8


	int 80h

    mov rsp, rbp
    pop rbp
    ret

sys_draw_rect:
  mov rax, 7
  int 80h
  ret