GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_clear_screen
GLOBAL sys_info_reg
GLOBAL sys_time
GLOBAL sys_printmem
GLOBAL sys_draw_rect
GLOBAL sys_check_buffer
GLOBAL sys_clear_buffer
GLOBAL sys_set_level
GLOBAL sys_holder
GLOBAL sys_get_level
GLOBAL sys_beep
GLOBAL sys_stop

section .text

sys_read:
  mov rax, 0
  int 80h
  ret

sys_write:
  mov rax, 1
  int 80h
  ret

sys_info_reg:
  mov rax, 2
  int 80h
  ret

sys_time:
  mov rax, 3
  int 80h
  ret

sys_clear_screen:
  mov rax, 4
  int 80h
  ret

sys_beep:
  mov rax, 5
  int 80h
  ret

sys_printmem:
  mov rax, 6
  int 80h
  ret

sys_draw_rect:
  mov rax, 7
  int 80h
  ret

sys_check_buffer:
  mov rax, 8
  int 80h
  ret

sys_holder:
  mov rax, 9
  int 80h
  ret

sys_clear_buffer:
  mov rax, 10
  int 80h
  ret

sys_set_level:
  mov rax, 11
  int 80h
  ret

sys_get_level:
  mov rax, 12
  int 80h
  ret

sys_stop:
  mov rax, 13
  int 80h
  ret
