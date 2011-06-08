;
; lock_s.s -- contains compare and swap implementation
;             Written for JamesM's kernel development tutorials.

global compare_and_swap:function compare_and_swap.end-compare_and_swap

compare_and_swap:
      mov edx, [esp+4]      ; contains our locks address
      mov ecx, [esp+8]      ; contains the status we want our lock to have
      mov eax, [esp+12]     ; contains the opposite
      lock cmpxchg edx, eax ; if edx == ecx, swap edx and eax
    ret
.end: