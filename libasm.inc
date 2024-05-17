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
; errno
;===============================================================================

%ifdef __LINUX__
    %define ERRNO_LOCATION __errno_location
%else
    %define ERRNO_LOCATION __error
%endif

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

%macro  symbol_call 1
  %ifdef __LINUX__
    safe_call %1 wrt ..plt
  %else
    safe_call %1
  %endif
%endmacro

%endif ; LIBASM_INC
