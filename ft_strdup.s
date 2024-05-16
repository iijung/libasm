%include    "libasm.inc"

%ifdef __LINUX__
    SYS_WRITE   equ 1
    %define MALLOC_SYM  malloc
    %define MALLOC_CALL malloc wrt ..plt
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    SYS_WRITE   equ 0x2000001
    %define MALLOC_SYM  malloc
    %define MALLOC_CALL malloc
    %define ERRNO_SYM   __error
    %define ERRNO_CALL  __error
%endif

section .text
    global  ft_strdup
    extern  ERRNO_SYM
    extern  MALLOC_SYM

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
    safe_call MALLOC_CALL
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
    safe_call ERRNO_CALL
    mov     [rax], rdx
    mov     rax, -1
    jmp     .copy_end
