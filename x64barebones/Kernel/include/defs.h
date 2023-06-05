#ifndef DEFS_H
#define DEFS_H


// Flags for access rights in segments 
#define ACS_PRESENT     0x80            // memory segment 
#define ACS_CSEG        0x18            // code segment 
#define ACS_DSEG        0x10            // data segment
#define ACS_READ        0x02            // reading segment 
#define ACS_WRITE       0x02            // writing segment 
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E		// Interrupt GATE 32 bits 
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )


#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

/* COLORS USED */
#define BLACK 0	
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11	
#define LIGHT_RED 12	
#define LIGHT_PURPLE 13	
#define YELLOW 14	
#define WHITE 15
#define DEFAULT (BLACK*16 + GRAY)

/* File Descriptors */
#define STDOUT 1
#define STDERR 2

#endif