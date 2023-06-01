GLOBAL cpuVendor
GLOBAL _xadd
GLOBAL _xchg
section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

_xadd:
    mov rax, rdi
    lock xadd [rsi], eax
    ret

_xchg:
    mov rax, rsi
    xchg [rdi], eax
    ret