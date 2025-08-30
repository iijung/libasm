%include    "libasm.inc"

%ifdef __LINUX__
    SYS_READ    equ 0
%else
    SYS_READ    equ 0x2000003
%endif

section .text
    global  ft_read
    extern  ERRNO_LOCATION

;===============================================================================
; csize_t ft_read(int fildes, void *buf, size_t nbyte);
;===============================================================================

ft_read:
    push    rbp
    mov     rbp, rsp

    mov     rax, SYS_READ
    syscall
%ifdef __LINUX__
    test    rax, rax
    jl     .errno_linux
%else
    jc     .errno_macos
%endif
    pop     rbp
    ret

    .errno_linux:
    neg     rax
    .errno_macos:
    mov     rdx, rax
    symbol_call ERRNO_LOCATION
    mov     [rax], rdx
    mov     rax, -1
    pop     rbp
    ret
