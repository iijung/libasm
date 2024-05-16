%ifndef LIBASM_INC
%define LIBASM_INC

;===============================================================================
; struct
;===============================================================================

struc t_list
    .data: resq 1
    .next: resq 1
endstruc

;===============================================================================
; macro
;===============================================================================

%macro  procedure_start 0
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15
%endmacro

%macro  procedure_end 0
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    pop     rbp
    ret
%endmacro

%macro  safe_call 1
    push    rbp
    mov     rbp, rsp
    sub     rsp, 8
    and     rsp, -16
    call    %1
    leave
%endmacro


%endif ; LIBASM_INC
