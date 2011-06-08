%if CHAPTER >= 9
;;; 
;;; thread.s -- Declares functions for thread switching.
;;;             Written for JamesM's kernel development tutorials.
;;;

        [global switch_thread]
        [global _create_thread]
        [extern current_thread]
        [extern thread_exit]
        
switch_thread:
        mov eax, [current_thread]

        mov [eax+0],  esp
        mov [eax+4],  ebp
        mov [eax+8],  ebx
        mov [eax+12], esi
        mov [eax+16], edi

        mov eax, [esp+4]

        mov [current_thread], eax

        mov esp, [eax+0]
        mov ebp, [eax+4]
        mov ebx, [eax+8]
        mov esi, [eax+12]
        mov edi, [eax+16]

        ret

_create_thread:
        mov eax, [esp+4]        ; fn
        mov ecx, [esp+8]        ; arg
        mov edx, [esp+12]       ; stack
        mov edi, [esp+16]       ; thread

        mov ebx, [current_thread]
        mov [ebx+0],  esp
        mov [ebx+4],  ebp
        mov [ebx+8],  ebx
        mov [ebx+12], esi
        mov [ebx+16], edi

        mov [current_thread], edi

        mov esp, edx
        push ecx
        push thread_exit

        sti
        jmp eax
        
 %endif ; CHAPTER >= 9
