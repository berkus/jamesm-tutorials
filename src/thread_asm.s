%if CHAPTER >= 9
;;; 
;;; thread.s -- Declares functions for thread switching.
;;;             Written for JamesM's kernel development tutorials.
;;;

        [global switch_thread]
        [extern current_thread]
        
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
jmp $        
        ret
 %endif ; CHAPTER >= 9
