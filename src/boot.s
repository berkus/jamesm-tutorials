;
; boot.s -- Kernel start location. Also defines multiboot header.
;           Based on Bran's kernel development tutorial file start.asm
;

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table. GRUB will also require our kernel be in elf32 format.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

bits 32                         ; All instructions should be 32-bit.

section .text

global mboot                    ; Make 'mboot' accessible from C.
extern code
extern bss
extern end

mboot:
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                                ; 4-byte boundary in the first 8KB of your kernel file.
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct
    dd mboot
          dd  code              ; Start of kernel '.text' (code) section.
          dd  bss               ; End of kernel '.data' section.
          dd  end               ; End of kernel.
          dd  start             ; Kernel entry point (initial EIP).

        
global start:function start.end-start ; Kernel entry point.
extern kernel_main                    ; This is the entry point of our C code

start:
    cli                         ; Disable interrupts.
    mov esp, stack              ; Set up our own stack.
    push ebx                  	; Push a pointer to the multiboot info structure.
    mov ebp, 0                  ; Initialise the base pointer to zero so we can 
                                ; terminate stack traces here.
    call kernel_main            ; call our main() function.
    jmp $                       ; Enter an infinite loop, to stop the processor
.end:                           ; from executing whatever rubbish is in the memory
                                ; after our kernel!

section .bss
    resb 32768
stack:
