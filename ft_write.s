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
    mov     rax, SYS_WRITE
    syscall
    jc     .errno_macos
    cmp     rax, 0
    jl     .errno_linux
    ret

    .errno_linux:
    neg     rax
    .errno_macos:
    mov     rdx, rax
    safe_call ERRNO_LOCATION
    mov     [rax], rdx
    mov     rax, -1
    ret
