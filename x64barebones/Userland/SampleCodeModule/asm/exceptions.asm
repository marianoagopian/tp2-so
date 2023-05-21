GLOBAL divByZero
GLOBAL invalidOperationCode

section .text

divByZero:
  mov rax, 0
  div rax
  ret

invalidOperationCode:
  ud2