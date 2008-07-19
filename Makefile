# Makefile for JamesM's kernel tutorials.

CSOURCES=$(shell find -name *.c)
COBJECTS=$(patsubst %.c, %.o, $(CSOURCES))
SSOURCES=$(shell find -name *.s)
SOBJECTS=$(patsubst %.s, %.o, $(SSOURCES))

CC=gcc
LD=ld
CFLAGS=-nostdlib -nostdinc -fno-builtin -m32
LDFLAGS=-melf_i386 -Tlink.ld
ASFLAGS=-felf

all: $(COBJECTS) $(SOBJECTS) link update

bochs:
	bash scripts/run_bochs.sh

update:
	@echo Updating floppy image
	@bash scripts/update_image.sh

clean:
	@echo Removing object files
	@-rm $(COBJECTS) $(SOBJECTS) kernel

link:
	@echo Linking
	@$(LD) $(LDFLAGS) -o kernel $(COBJECTS) $(SOBJECTS)

.s.o:
	@echo Assembling $<
	@nasm $(ASFLAGS) $<

.c.o:
	@echo Compiling $<
	@$(CC) $(CFLAGS) -o $@ -c $<
