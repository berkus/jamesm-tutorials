# Makefile for JamesM's kernel tutorials.

CSOURCES=$(shell find -maxdepth 2 -name *.c)
COBJECTS=$(patsubst %.c, %.o, $(CSOURCES))
SSOURCES=$(shell find -maxdepth 2 -name *.s)
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

INSTALL_DIR=build/chapter_$(CHAPTER)

.PHONY : docs

all: $(COBJECTS) $(SOBJECTS) link update

bochs:
	bash scripts/run_bochs.sh

update:
	@echo Updating floppy image
	@bash scripts/update_image.sh

clean:
	@echo Removing object files
	@-rm $(COBJECTS) $(SOBJECTS) kernel 2>/dev/null

link:
	@echo Linking
	@$(LD) $(LDFLAGS) -o kernel $(SOBJECTS) $(COBJECTS)

docs:
	cd doc; make html

full:
	for c in 2 3 4 5 6 7; do echo "*** Chapter: $$c"; make clean; make CHAPTER=$$c; make install CHAPTER=$$c; done

install:
	@echo Installing chapter $(CHAPTER)
	@-rm -r $(INSTALL_DIR)
	@mkdir -p $(INSTALL_DIR)/src
	@python scripts/install.py $(CHAPTER) src $(INSTALL_DIR)/src
	@cp floppy.img kernel link.ld Makefile $(INSTALL_DIR)
	@mkdir $(INSTALL_DIR)/scripts
	@cp scripts/update_image.sh scripts/run_bochs.sh $(INSTALL_DIR)/scripts

check-install:
	@echo Building in $(INSTALL_DIR)
	@cd $(INSTALL_DIR); make

.s.o:
	@echo Assembling $<
	@nasm $(ASFLAGS) -DCHAPTER=$(CHAPTER) $<

.c.o:
	@echo Compiling $<
	@$(CC) $(CFLAGS) -DCHAPTER=$(CHAPTER) -o $@ -c $<
