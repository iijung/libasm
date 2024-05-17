%include    "libasm.inc"

%ifdef __LINUX__
    SYS_WRITE   equ 1
%else
    SYS_WRITE   equ 0x2000001
%endif

section .text
    global  ft_strdup
    extern  ERRNO_LOCATION
    extern  malloc

;===============================================================================
; char *strdup(const char *s1);
;===============================================================================

ft_strdup:
    push    rbp
    mov     rbp, rsp

    push    rdi ; s
    push    rsi ;
    push    rbx
    push    rcx

    xor     rax, rax
    mov     rcx, -1
    repne   scasb
    mov     rbx, -1
    sub     rbx, rcx

    ; rax = malloc(rdi)
    mov     rdi, rbx
    symbol_call malloc
    test    rax, rax
    jz     .errno
    mov     rdi, rax
    mov     rsi, [rbp - 8]
    mov     rcx, rbx
    rep     movsb
    .copy_end:

    pop     rcx
    pop     rbx
    pop     rsi
    pop     rdi

    pop     rbp
    ret

    .errno:
    neg     rax
    mov     rdx, rax
    symbol_call ERRNO_LOCATION
    mov     [rax], rdx
    mov     rax, -1
    jmp     .copy_end
