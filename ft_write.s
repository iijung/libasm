%include    "libasm.inc"

%ifdef __LINUX__
    SYS_WRITE   equ 1
%else
    SYS_WRITE   equ 0x2000004
%endif

section .text
    global  ft_write
    extern  ERRNO_LOCATION

;===============================================================================
; ssize_t ft_write(int fildes, const void *buf, size_t nbytes);
;===============================================================================

ft_write:
    push    rbp
    mov     rbp, rsp

    mov     rax, SYS_WRITE
    syscall
%ifdef __LINUX__
    test   rax, rax
    jl     .errno_linux ; if rax < 0, error
%else
    jc     .errno_macos ; if CF=1, error
%endif
    pop    rbp
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
