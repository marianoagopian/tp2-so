include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
ASMSOURCES= $(wildcard ./asm/*.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
SOURCES=$(wildcard [^_]*.c)
COBJECTS=$(SOURCES:.c=.o)

all: $(MODULE)

$(MODULE): $(ASMOBJECTS) $(COBJECTS)
	$(LD) -T sampleCodeModule.ld _loader.o $(COBJECTS) $(ASMOBJECTS) -o ../$(MODULE)
	$(LD) -T sampleCodeModule.ld _loader.o $(COBJECTS) $(ASMOBJECTS) --oformat=elf64-x86-64 -o ../0000-sampleCodeModule.elf
#	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(ASMFLAGS) $(COBJECTS) -o ../0000-sampleCodeModule.elf

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c $(SOURCES) 
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o ./comandos/*.o ./libs/*.o ./asm/*.o

.PHONY: all clean print