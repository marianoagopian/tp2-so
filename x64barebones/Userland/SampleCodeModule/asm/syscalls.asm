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
GLOBAL sys_alloc
GLOBAL sys_destroy_pipe
GLOBAL sys_destroy_sem
GLOBAL sys_free
GLOBAL sys_get_pid
GLOBAL sys_kill_process
GLOBAL sys_mm_status
GLOBAL sys_nais
GLOBAL sys_pause_process
GLOBAL sys_pipe_info
GLOBAL sys_process_alive
GLOBAL sys_process_info
GLOBAL sys_read_pipe
GLOBAL sys_register_child_process
GLOBAL sys_register_pipe_available
GLOBAL sys_register_process
GLOBAL sys_register_sem
GLOBAL sys_register_sem_available
GLOBAL sys_renounce_cpu
GLOBAL sys_signal_sem
GLOBAL sys_wait_for_children
GLOBAL sys_wait_sem
GLOBAL sys_write_pipe
GLOBAL sys_write_to_screen

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

sys_alloc:
  mov rax, 14
  int 80h
  ret
  
sys_destroy_pipe:
  mov rax, 15
  int 80h
  ret

sys_destroy_sem:
 mov rax, 16
 int 80h
 ret

sys_free:
 mov rax, 17
 int 80h
 ret

sys_get_pid:
 mov rax, 18
 int 80h
 ret

sys_kill_process:
 mov rax, 19
 int 80h
 ret

sys_mm_status:
 mov rax, 20
 int 80h
 ret

sys_nais:
 mov rax, 21
 int 80h
 ret

sys_pause_process:
 mov rax, 22
 int 80h
 ret

sys_pipe_info:
 mov rax, 23
 int 80h
 ret

sys_process_alive:
 mov rax, 24
 int 80h
 ret

sys_process_info:
 mov rax, 25
 int 80h
 ret

sys_read_pipe:
 mov rax, 26
 int 80h
 ret

sys_register_child_process:
 mov rax, 27
 int 80h
 ret

sys_register_pipe_available:
 mov rax, 28
 int 80h
 ret

sys_register_process:
 mov rax, 29
 int 80h
 ret

sys_register_sem:
 mov rax, 30
 int 80h
 ret

sys_register_sem_available:
 mov rax, 31
 int 80h
 ret

sys_renounce_cpu:
 mov rax, 32
 int 80h
 ret

sys_signal_sem:
 mov rax, 33
 int 80h
 ret

sys_wait_for_children:
 mov rax, 34
 int 80h
 ret

sys_wait_sem:
 mov rax, 35
 int 80h
 ret

sys_write_pipe:
 mov rax, 36
 int 80h
 ret

sys_write_to_screen:
 mov rax, 37
 int 80h
 ret