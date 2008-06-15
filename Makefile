# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=src/boot.o src/main.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -m32
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link update

update:
	bash scripts/update_image.sh

clean:
	-rm src/*.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
