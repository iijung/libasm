%include    "libasm.inc"

%ifdef __LINUX__
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    %define ERRNO_SYM   __error
    %define ERRNO_CALL  __error
%endif

section .text
    global  ft_list_size
    extern  ERRNO_SYM

;===============================================================================
; extern int ft_list_size(t_list *begin_list);
;===============================================================================

ft_list_size:
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
    safe_call ERRNO_CALL
    mov     [rax], byte 84 ; EOVERFLOW
    mov     rax, 0x7fffffff
    procedure_end
