include Makefile.inc

KERNEL=kernel.bin

SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_LIBS=$(wildcard libs/*.c)
SOURCES_MM=$(wildcard memoryManager/*.c)
SOURCES_PM=$(wildcard processManager/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBS=$(SOURCES_LIBS:.c=.o)
OBJECTS_MM=$(SOURCES_MM:.c=.o)
OBJECTS_PM=$(SOURCES_PM:.c=.o)

LOADERSRC=loader.asm
MEMORY_MANAGER= -D USE_BUDDY
#MEMORY_MANAGER=

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_LIBS) $(OBJECTS_MM) $(OBJECTS_PM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIBS) $(STATICLIBS) $(OBJECTS_MM) $(OBJECTS_PM)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIBS) $(OBJECTS_MM) $(OBJECTS_PM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@ $(MEMORY_MANAGER)

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o memoryManager/*.o processManager/*.o libs/*.o *.o *.bin *.elf

.PHONY: all clean
