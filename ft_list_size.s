%ifdef __LINUX__
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    %define ERRNO_SYM   ___error
    %define ERRNO_CALL  ___error
%endif

section .bss

struc t_list
    .data: resq 1
    .next: resq 1
endstruc


section .text
    global  ft_list_size
    global  _ft_list_size
    extern  ERRNO_SYM

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

;===============================================================================
; extern int ft_list_size(t_list *begin_list);
;===============================================================================

ft_list_size:
_ft_list_size:
    procedure_start

    xor     rax, rax

    .loop:
        test    rdi, rdi
        jz      .loop_end
        cmp     rax, 0x7fffffff
        je      .eoverflow

        mov     rdi, qword [rdi + t_list.next]
        inc     rax
        jmp     .loop
    .loop_end:

    procedure_end

    .eoverflow:
    call    ERRNO_CALL
    mov     [rax], byte 84 ; EOVERFLOW
    mov     rax, 0x7fffffff
    procedure_end
