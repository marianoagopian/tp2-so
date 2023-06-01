include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_LIBS=$(wildcard libs/*.c)
SOURCES_MM=$(wildcard memoryManager/*.c)
SOURCES_PM=$(wildcard processManager/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBS=$(SOURCES_LIBS:.asm=.o)
OBJECTS_MM=$(SOURCES_MM:.asm=.o)
OBJECTS_PM=$(SOURCES_PM:.asm=.o)

LOADERSRC=loader.asm
MEMORY_MANAGER=

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_LIBS) $(OBJECTS_MM) $(OBJECTS_PM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(OBJECTS_LIBS) $(OBJECTS_MM) $(OBJECTS_PM)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@ $(MEMORY_MANAGER)

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o memoryManager/*.o processManager/*.o libs/*.o *.o *.bin *.elf

.PHONY: all clean
