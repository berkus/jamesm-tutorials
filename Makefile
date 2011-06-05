# Makefile for JamesM's kernel tutorials.

CSOURCES=$(shell find -name *.c)
COBJECTS=$(patsubst %.c, %.o, $(CSOURCES))
SSOURCES=$(shell find -name *.s)
SOBJECTS=$(patsubst %.s, %.o, $(SSOURCES))

CC=gcc
ifeq ($(shell ls /usr/bin/ld.bfd 2>/dev/null),/usr/bin/ld.bfd)
LD:=/usr/bin/ld.bfd
else
LD:=ld
endif

CFLAGS=-nostdlib -fno-builtin -m32
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
	@$(LD) $(LDFLAGS) -o kernel $(SOBJECTS) $(COBJECTS)

docs:
	cd doc; make html

.s.o:
	@echo Assembling $<
	@nasm $(ASFLAGS) -DCHAPTER=$(CHAPTER) $<

.c.o:
	@echo Compiling $<
	@$(CC) $(CFLAGS) -DCHAPTER=$(CHAPTER) -o $@ -c $<
