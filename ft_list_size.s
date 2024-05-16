%include    "libasm.inc"

section .text
    global  ft_list_size
    extern  ERRNO_LOCATION

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
    safe_call ERRNO_LOCATION
    mov     [rax], byte 84 ; EOVERFLOW
    mov     rax, 0x7fffffff
    procedure_end
