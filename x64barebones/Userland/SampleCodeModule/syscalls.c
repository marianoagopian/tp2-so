// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "./include/syscalls.h"

#define NULL 0

extern uint64_t syscaller(uint64_t syscallID, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4);

uint64_t sys_read(uint64_t fd, const char * buf, unsigned int length){
    return syscaller(SYS_READ, (uint64_t) fd, (uint64_t) buf, (uint64_t) length, NULL );      
}

uint64_t sys_write(const char * string, uint64_t length){
    return syscaller(SYS_WRITE, (uint64_t) string, length, NULL, NULL);      
}   

uint8_t sys_info_reg(uint64_t reg[15]){
    return syscaller(SYS_INFOREG, reg[15], NULL, NULL, NULL ); 
}

uint64_t sys_time(){
    return syscaller(SYS_TIME, NULL, NULL, NULL, NULL );      
}

void sys_clear_screen(){
    syscaller(SYS_CLEAR_SCREEN, NULL, NULL, NULL , NULL );      
}

void sys_beep(uint32_t frequency){
    syscaller(SYS_BEEP, (uint64_t)frequency, NULL, NULL , NULL );
}

uint64_t sys_printmem(uint64_t position, char * buffer){
    return syscaller(SYS_PRINT_MEM, position, (uint64_t)buffer, NULL , NULL );
}

void sys_holder(int time){
    syscaller(SYS_HOLDER, (uint64_t)time, NULL, NULL , NULL );      
}

void sys_clear_buffer(){
    syscaller(SYS_CLEAR_BUFFER, NULL, NULL, NULL , NULL );      
}

void sys_set_level(int num){
    syscaller(SYS_SET_LEVEL, (uint64_t)num, NULL, NULL , NULL );      
}

uint64_t sys_get_level(){
    return syscaller(SYS_GET_LEVEL, NULL, NULL, NULL , NULL );      
}

void sys_stop(){
    syscaller(SYS_STOP, NULL, NULL, NULL , NULL );      
}

uint64_t sys_alloc(uint64_t len){
    return syscaller(SYS_ALLOC, (uint64_t)len, NULL, NULL, NULL );
}

uint64_t sys_destroy_pipe(unsigned int pipe_id){
    return syscaller(SYS_DESTROY_PIPE, (uint64_t) pipe_id, NULL, NULL , NULL );
}

uint64_t sys_destroy_sem(unsigned int sem_id){
    return syscaller(SYS_DESTROY_SEM, (uint64_t) sem_id, NULL, NULL, NULL);
}

uint64_t sys_free(void * ptr){
    return syscaller(SYS_FREE, (uint64_t) ptr, NULL, NULL, NULL );
}

uint64_t  sys_get_pid(){
    return syscaller(SYS_GET_PID, NULL, NULL, NULL, NULL );
}

uint64_t  sys_kill_process(unsigned int pid){
    return syscaller(SYS_KILL_PROCESS,(uint64_t) pid, NULL,NULL, NULL );
}

uint64_t sys_mm_status(uint64_t * buffer){
    return syscaller(SYS_MM_STATUS, (uint64_t) buffer, NULL, NULL, NULL);
}

uint64_t  sys_nice(uint8_t pid, int delta){
    return syscaller(SYS_NICE, pid, delta, NULL, NULL );
}

uint64_t  sys_pause_process(unsigned int pid){
    return syscaller(SYS_PAUSE_PROCESS,(uint64_t) pid,NULL,NULL, NULL );
}

uint64_t sys_pipe_info(pipes_info * info){
     return syscaller(SYS_PIPE_INFO, (uint64_t) info, NULL, NULL , NULL );    
}

uint64_t sys_process_alive(unsigned int pid){
    return syscaller(SYS_PROCESS_ALIVE, (uint64_t) pid, NULL, NULL , NULL );    
}

uint64_t sys_process_info(process_info * info){
    return syscaller(SYS_PROCESS_INFO, (uint64_t) info, NULL, NULL , NULL );    
}

uint64_t sys_read_pipe(unsigned int pipe_id, char * dest, unsigned int count){
    return syscaller(SYS_READ_PIPE, (uint64_t) pipe_id, (uint64_t) dest, (uint64_t) count , NULL);
}

uint64_t sys_register_child_process(uint64_t entryPoint, uint8_t input, uint8_t output, uint64_t arg0){
    return syscaller(SYS_REGISTER_CHILD_PROCESS, (uint64_t) entryPoint, (uint64_t) input, (uint64_t) output, arg0);
}

uint64_t sys_register_pipe_available(){
    return syscaller(SYS_REGISTER_PIPE_AVAILABLE, NULL, NULL, NULL , NULL );
}

uint64_t sys_register_process(uint64_t entrypoint, uint8_t input, uint8_t output, uint64_t arg0){
    return syscaller(SYS_REGISTER_PROCESS, (uint64_t) entrypoint, (uint64_t) input, (uint64_t) output, arg0);
}

uint64_t  sys_register_sem(unsigned int sem_id, unsigned int value){
    return syscaller(SYS_REGISTER_SEM, (uint64_t) sem_id, (uint64_t) value, NULL , NULL );
}

uint64_t  sys_register_sem_available(unsigned int value){
    return syscaller(SYS_REGISTER_SEM_AVAILABLE, (uint64_t) value, NULL, NULL , NULL );
}

uint64_t  sys_renounce_cpu(){
    return syscaller(SYS_RENOUNCE_CPU, NULL, NULL, NULL, NULL );
}

uint64_t  sys_signal_sem(unsigned int sem_id){
    return syscaller(SYS_SIGNAL_SEM, (uint64_t) sem_id, NULL, NULL , NULL );
}

uint64_t  sys_wait_for_children(){
    return syscaller(SYS_WAIT_FOR_CHILDREN, NULL, NULL, NULL, NULL );
}

uint64_t  sys_wait_sem(unsigned int sem_id){
    return syscaller(SYS_WAIT_SEM, (uint64_t) sem_id, NULL, NULL, NULL );
}

uint64_t sys_write_pipe(unsigned int pipe_id, const char * src, unsigned int count){
    return syscaller(SYS_WRITE_PIPE, (uint64_t) pipe_id, (uint64_t) src, (uint64_t) count , NULL );
}

uint64_t sys_semaphore_info(semaphore_info * info){
    return syscaller(SYS_SEMAPHORE_INFO, (uint64_t) info, NULL, NULL , NULL );    
}

uint64_t sys_register_pipe(unsigned int pipe_id){
    return syscaller(SYS_REGISTER_PIPE, (uint64_t) pipe_id, NULL, NULL , NULL );
}

void sys_draw_white_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
    syscaller(SYS_DRAW_WHITE_RECT, (uint64_t) x, (uint64_t) y, (uint64_t) width, (uint64_t) height);
}

void sys_draw_green_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
    syscaller(SYS_DRAW_GREEN_RECT, (uint64_t) x, (uint64_t) y, (uint64_t) width, (uint64_t) height);
}

uint8_t sys_check_buffer(){
    return syscaller(SYS_CHECK_BUFFER, NULL, NULL, NULL , NULL );      
}