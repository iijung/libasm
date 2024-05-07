%ifdef __LINUX__
    %define MALLOC_SYM  malloc
    %define MALLOC_CALL malloc wrt ..plt
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    %define MALLOC_SYM  _malloc
    %define MALLOC_CALL _malloc
    %define ERRNO_SYM   ___error
    %define ERRNO_CALL  ___error
%endif

section .bss

struc t_list
    .data: resq 1
    .next: resq 1
endstruc


section .text
    global  ft_list_push_front
    global  _ft_list_push_front
    extern  ERRNO_SYM
    extern  MALLOC_SYM

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
; extern t_list *ft_create_elem(void *data);
;===============================================================================

ft_create_elem:
    procedure_start
    push    rdi
    mov     rdi, t_list_size
    call    MALLOC_CALL
    pop     rdi
    test    rax, rax
    jz      .enomem
    mov     qword [rax + t_list.data], rdi
    mov     qword [rax + t_list.next], 0
    procedure_end

    .enomem:
    call    ERRNO_CALL
    mov     [rax], byte 12 ; ENOMEM
    xor     rax, rax
    procedure_end

;===============================================================================
; extern void ft_list_push_front(t_list **begin_list, void *data);
;===============================================================================

ft_list_push_front:
_ft_list_push_front:
    procedure_start

    ; if begin_list == NULL, return
    test    rdi, rdi
    jnz     .create_elem
    procedure_end

    ; if ft_create_elem is fail, return
    .create_elem:
    push    rdi
    mov     rdi, rsi
    call    ft_create_elem
    pop     rdi
    test    rax, rax
    jnz     .initial
    procedure_end

    .initial:
    mov     rsi, [rdi]
    mov     qword [rax + t_list.next], rsi
    mov     qword [rdi], rax
    procedure_end
